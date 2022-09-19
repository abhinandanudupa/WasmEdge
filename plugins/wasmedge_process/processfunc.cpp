// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "processfunc.h"

#include "common/defines.h"

#if WASMEDGE_OS_LINUX || WASMEDGE_OS_MACOS

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#elif WASMEDGE_OS_WINDOWS

#include <Windows.h>
#include <stdio.h>
#include <strsafe.h>
#include <tchar.h>
#include <ProcessEnv.h> 

#define BUFSIZE 4096

#endif





namespace WasmEdge {
namespace Host {

Expect<void>
WasmEdgeProcessSetProgName::body(const Runtime::CallingFrame &Frame,
                                 uint32_t NamePtr, uint32_t NameLen) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  char *Buf = MemInst->getPointer<char *>(NamePtr);
  std::copy_n(Buf, NameLen, std::back_inserter(Env.Name));
  return {};
}

Expect<void> WasmEdgeProcessAddArg::body(const Runtime::CallingFrame &Frame,
                                         uint32_t ArgPtr, uint32_t ArgLen) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  char *Buf = MemInst->getPointer<char *>(ArgPtr);
  std::string NewArg;
  std::copy_n(Buf, ArgLen, std::back_inserter(NewArg));
  Env.Args.push_back(std::move(NewArg));
  return {};
}

Expect<void> WasmEdgeProcessAddEnv::body(const Runtime::CallingFrame &Frame,
                                         uint32_t EnvNamePtr,
                                         uint32_t EnvNameLen,
                                         uint32_t EnvValPtr,
                                         uint32_t EnvValLen) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  char *EnvBuf = MemInst->getPointer<char *>(EnvNamePtr);
  char *ValBuf = MemInst->getPointer<char *>(EnvValPtr);
  std::string NewEnv, NewVal;
  std::copy_n(EnvBuf, EnvNameLen, std::back_inserter(NewEnv));
  std::copy_n(ValBuf, EnvValLen, std::back_inserter(NewVal));
  Env.Envs.emplace(std::move(NewEnv), std::move(NewVal));
  return {};
}

Expect<void> WasmEdgeProcessAddStdIn::body(const Runtime::CallingFrame &Frame,
                                           uint32_t BufPtr, uint32_t BufLen) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  uint8_t *Buf = MemInst->getPointer<uint8_t *>(BufPtr);
  Env.StdIn.reserve(Env.StdIn.size() + BufLen);
  std::copy_n(Buf, BufLen, std::back_inserter(Env.StdIn));
  return {};
}

Expect<void> WasmEdgeProcessSetTimeOut::body(const Runtime::CallingFrame &,
                                             uint32_t Time) {
  Env.TimeOut = Time;
  return {};
}

Expect<uint32_t> WasmEdgeProcessRun::body(const Runtime::CallingFrame &) {
#if WASMEDGE_OS_LINUX || WASMEDGE_OS_MACOS
  // Clear outputs.
  Env.StdOut.clear();
  Env.StdErr.clear();
  Env.ExitCode = static_cast<uint32_t>(-1);

  // Check white list of commands.
  if (!Env.AllowedAll &&
      Env.AllowedCmd.find(Env.Name) == Env.AllowedCmd.end()) {
    std::string Msg = "Permission denied: Command \"";
    Msg.append(Env.Name);
    Msg.append("\" is not in the white list. Please use --allow-command=");
    Msg.append(Env.Name);
    Msg.append(" or --allow-command-all to add \"");
    Msg.append(Env.Name);
    Msg.append("\" command into the white list.\n");
    Env.Name.clear();
    Env.Args.clear();
    Env.Envs.clear();
    Env.StdIn.clear();
    Env.StdErr.reserve(Msg.length());
    std::copy_n(Msg.c_str(), Msg.length(), std::back_inserter(Env.StdErr));
    Env.ExitCode = static_cast<int32_t>(INT8_C(-1));
    Env.TimeOut = Env.DEFAULT_TIMEOUT;
    return Env.ExitCode;
  }

  // Create pipes for stdin, stdout, and stderr.
  int FDStdIn[2], FDStdOut[2], FDStdErr[2];
  if (pipe(FDStdIn) == -1) {
    // Create stdin pipe failed.
    return Env.ExitCode;
  }
  if (pipe(FDStdOut) == -1) {
    // Create stdout pipe failed.
    close(FDStdIn[0]);
    close(FDStdIn[1]);
    return Env.ExitCode;
  }
  if (pipe(FDStdErr) == -1) {
    // Create stderr pipe failed.
    close(FDStdIn[0]);
    close(FDStdIn[1]);
    close(FDStdOut[0]);
    close(FDStdOut[1]);
    return Env.ExitCode;
  }

  // Create a child process for executing command.
  pid_t PID = fork();
  if (PID == -1) {
    // Create process failed.
    close(FDStdIn[0]);
    close(FDStdIn[1]);
    close(FDStdOut[0]);
    close(FDStdOut[1]);
    close(FDStdErr[0]);
    close(FDStdErr[1]);
    return Env.ExitCode;
  } else if (PID == 0) {
    // Child process. Setup pipes.
    dup2(FDStdIn[0], 0);
    dup2(FDStdOut[1], 1);
    dup2(FDStdErr[1], 2);
    close(FDStdIn[0]);
    close(FDStdIn[1]);
    close(FDStdOut[0]);
    close(FDStdOut[1]);
    close(FDStdErr[0]);
    close(FDStdErr[1]);

    // Prepare arguments and environment variables.
    std::vector<std::string> EnvStr;
    for (auto &It : Env.Envs) {
      EnvStr.push_back(It.first + "=" + It.second);
    }
    std::vector<char *> Argv, Envp;
    Argv.push_back(Env.Name.data());
    std::transform(Env.Args.begin(), Env.Args.end(), std::back_inserter(Argv),
                   [](std::string &S) { return S.data(); });
    std::transform(EnvStr.begin(), EnvStr.end(), std::back_inserter(Envp),
                   [](std::string &S) { return S.data(); });
    Argv.push_back(nullptr);
    Envp.push_back(nullptr);
#if defined(__GLIBC_PREREQ)
#if __GLIBC_PREREQ(2, 11)
    if (execvpe(Env.Name.c_str(), &Argv[0], &Envp[0]) == -1) {
#else
    if (execve(Env.Name.c_str(), &Argv[0], &Envp[0]) == -1) {
#endif
#else
    if (execve(Env.Name.c_str(), &Argv[0], &Envp[0]) == -1) {
#endif
      switch (errno) {
      case EACCES:
        spdlog::error("Permission denied.");
        break;
      case ENOENT:
        spdlog::error("Command not found.");
        break;
      default:
        spdlog::error("Unknown error.");
        break;
      }
      _exit(-1);
    }
  } else {
    // Parent process. Close unused file descriptors.
    close(FDStdIn[0]);
    close(FDStdOut[1]);
    close(FDStdErr[1]);

    // Send inputs.
    uint32_t WBytes = 0;
    while (WBytes < Env.StdIn.size()) {
      uint32_t WriteNum =
          std::min(static_cast<size_t>(PIPE_BUF), Env.StdIn.size() - WBytes);
      if (auto Res = write(FDStdIn[1], &Env.StdIn[WBytes], WriteNum); Res > 0) {
        WBytes += Res;
      } else {
        break;
      }
    }
    close(FDStdIn[1]);

    // Waiting for child process and get outputs.
    uint8_t Buf[PIPE_BUF];
    ssize_t RBytes;
    int ChildStat;
    struct timeval TStart, TCurr;
    gettimeofday(&TStart, NULL);
    while (true) {
      gettimeofday(&TCurr, NULL);
      if ((TCurr.tv_sec - TStart.tv_sec) * 1000U +
              (TCurr.tv_usec - TStart.tv_usec) / 1000000U >
          Env.TimeOut) {
        // Over timeout. Interrupt child process.
        kill(PID, SIGKILL);
        Env.ExitCode = static_cast<uint32_t>(ETIMEDOUT);
        break;
      }

      // Wait for child process.
      pid_t WPID = waitpid(PID, &ChildStat, WNOHANG);
      if (WPID == -1) {
        // waitpid failed.
        Env.ExitCode = static_cast<uint32_t>(EINVAL);
        break;
      } else if (WPID > 0) {
        // Child process returned.
        Env.ExitCode = static_cast<int8_t>(WEXITSTATUS(ChildStat));
        break;
      }

      // Read stdout and stderr.
      fd_set FDSet;
      int NFD = std::max(FDStdOut[0], FDStdErr[0]) + 1;
      FD_ZERO(&FDSet);
      FD_SET(FDStdOut[0], &FDSet);
      FD_SET(FDStdErr[0], &FDSet);
      struct timeval TSelect = {.tv_sec = 0, .tv_usec = 0};
      if (select(NFD, &FDSet, NULL, NULL, &TSelect) > 0) {
        if (FD_ISSET(FDStdOut[0], &FDSet)) {
          if (RBytes = read(FDStdOut[0], Buf, sizeof(Buf)); RBytes > 0) {
            Env.StdOut.reserve(Env.StdOut.size() + RBytes);
            std::copy_n(Buf, RBytes, std::back_inserter(Env.StdOut));
          }
        }
        if (FD_ISSET(FDStdErr[0], &FDSet)) {
          if (RBytes = read(FDStdErr[0], Buf, sizeof(Buf)); RBytes > 0) {
            Env.StdErr.reserve(Env.StdErr.size() + RBytes);
            std::copy_n(Buf, RBytes, std::back_inserter(Env.StdErr));
          }
        }
      }
      usleep(Env.DEFAULT_POLLTIME * 1000);
    }

    // Read remained stdout and stderr.
    do {
      RBytes = read(FDStdOut[0], Buf, sizeof(Buf));
      if (RBytes > 0) {
        Env.StdOut.reserve(Env.StdOut.size() + RBytes);
        std::copy_n(Buf, RBytes, std::back_inserter(Env.StdOut));
      }
    } while (RBytes > 0);
    do {
      RBytes = read(FDStdErr[0], Buf, sizeof(Buf));
      if (RBytes > 0) {
        Env.StdErr.reserve(Env.StdErr.size() + RBytes);
        std::copy_n(Buf, RBytes, std::back_inserter(Env.StdErr));
      }
    } while (RBytes > 0);
    close(FDStdOut[0]);
    close(FDStdErr[0]);
  }

  // Reset inputs.
  Env.Name.clear();
  Env.Args.clear();
  Env.Envs.clear();
  Env.StdIn.clear();
  Env.TimeOut = Env.DEFAULT_TIMEOUT;
  return Env.ExitCode;
#elif WASMEDGE_OS_WINDOWS

  // Clear outputs.
  Env.StdOut.clear();
  Env.StdErr.clear();
  Env.ExitCode = static_cast<uint32_t>(-1);

  // Check white list of commands.
  if (!Env.AllowedAll &&
      Env.AllowedCmd.find(Env.Name) == Env.AllowedCmd.end()) {
    std::string Msg = "Permission denied: Command \"";
    Msg.append(Env.Name);
    Msg.append("\" is not in the white list. Please use --allow-command=");
    Msg.append(Env.Name);
    Msg.append(" or --allow-command-all to add \"");
    Msg.append(Env.Name);
    Msg.append("\" command into the white list.\n");
    Env.Name.clear();
    Env.Args.clear();
    Env.Envs.clear();
    Env.StdIn.clear();
    Env.StdErr.reserve(Msg.length());
    std::copy_n(Msg.c_str(), Msg.length(), std::back_inserter(Env.StdErr));
    Env.ExitCode = static_cast<uint32_t>(INT8_C(-1));
    Env.TimeOut = Env.DEFAULT_TIMEOUT;
    return Env.ExitCode;
  }

  HANDLE g_hChildStd_IN_Rd = NULL;
  HANDLE g_hChildStd_IN_Wr = NULL;
  HANDLE g_hChildStd_OUT_Rd = NULL;
  HANDLE g_hChildStd_OUT_Wr = NULL;

  HANDLE g_hInputFile = NULL;

  SECURITY_ATTRIBUTES saAttr;

  printf("\n->Start of parent execution.\n");

  // Set the bInheritHandle flag so pipe handles are inherited.

  saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  saAttr.bInheritHandle = TRUE;
  saAttr.lpSecurityDescriptor = NULL;

  // Create a pipe for the child process's STDOUT.

  if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
    return Env.ExitCode;

  // Ensure the read handle to the pipe for STDOUT is not inherited.

  if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
    return Env.ExitCode;

  // Create a pipe for the child process's STDIN.

  if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
    return Env.ExitCode;

  // Ensure the write handle to the pipe for STDIN is not inherited.

  if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
    return Env.ExitCode;

  // Prepare arguments and environment variables.
  std::vector<std::string> EnvStr;
  for (auto &It : Env.Envs) {
    EnvStr.push_back(It.first + "=" + It.second);
  }

  // Create the child process.

  std::vector<char *> Argv, Envp;
  Argv.push_back(Env.Name.data());
  std::transform(Env.Args.begin(), Env.Args.end(), std::back_inserter(Argv),
                 [](std::string &S) { return S.data(); });
  std::transform(EnvStr.begin(), EnvStr.end(), std::back_inserter(Envp),
                 [](std::string &S) { return S.data(); });
  Argv.push_back(nullptr);
  Envp.push_back(nullptr);

  PROCESS_INFORMATION piProcInfo;
  STARTUPINFO siStartInfo;
  BOOL bSuccess = FALSE;

  // Set up members of the PROCESS_INFORMATION structure.

  ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

  // Set up members of the STARTUPINFO structure.
  // This structure specifies the STDIN and STDOUT handles for redirection.

  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.hStdError = g_hChildStd_OUT_Wr;
  siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
  siStartInfo.hStdInput = g_hChildStd_IN_Rd;
  siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

  // Create the child process.

  bSuccess = CreateProcess(Env.Name.c_str(),
                           Argv[0],      // command line
                           NULL,         // process security attributes
                           NULL,         // primary thread security attributes
                           TRUE,         // handles are inherited
                           0,            // creation flags
                           &Envp[0],     // use parent's environment
                           NULL,         // use parent's current directory
                           &siStartInfo, // STARTUPINFO pointer
                           &piProcInfo); // receives PROCESS_INFORMATION

  // If an error occurs, exit the application.
  if (!bSuccess) {
    return Env.ExitCode;
  }

  else {
    // Close handles to the child process and its primary thread.
    // Some applications might keep these handles to monitor the status
    // of the child process, for example.

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    // Close handles to the stdin and stdout pipes no longer needed by the child
    // process. If they are not explicitly closed, there is no way to recognize
    // that the child process has ended.

    CloseHandle(g_hChildStd_OUT_Wr);
    CloseHandle(g_hChildStd_IN_Rd);
  }

  // Get a handle to an input file for the parent.
  // This example assumes a plain text file and uses string output to verify
  // data flow.

  /*
  HANDLE hTimer = NULL;
  LARGE_INTEGER liDueTime;

  liDueTime.QuadPart = - static_cast<int64_t>(Env.TimeOut);

  // Create an unnamed waitable timer.
  hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
  if (NULL == hTimer) {
    printf("CreateWaitableTimer failed (%d)\n", GetLastError());
    return Env.ExitCode;
  }

  printf("Waiting for 10 seconds...\n");

  // Set a timer to wait for 10 seconds.
  if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0)) {
    printf("SetWaitableTimer failed (%d)\n", GetLastError());
    return 2;
  }

  // Wait for the timer.

  if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)
    printf("WaitForSingleObject failed (%d)\n", GetLastError());
  else
    printf("Timer was signaled.\n");

  */

  // Write to the pipe that is the standard input for a child process.
  // Data is written to the pipe's buffers, so it is not necessary to wait
  // until the child process is running before writing data.

  // Read from a file and write its contents to the pipe for the child's STDIN.
  // Stop when there is no more data.
  {
    DWORD dwRead, dwWritten;
    CHAR chBuf[BUFSIZE];
    bSuccess = FALSE;

    //    for (;;) {
    //      bSuccess = ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, NULL);
    //      if (!bSuccess || dwRead == 0) {
    //        break;
    //      }

    uint32_t WBytes = 0;
    while (WBytes < Env.StdIn.size()) {
      uint32_t WriteNum =
          static_cast<uint32_t>(std::min(static_cast<size_t>(BUFSIZE), Env.StdIn.size() - WBytes));
      bSuccess =
          WriteFile(g_hChildStd_IN_Wr, chBuf, WriteNum, &dwWritten, NULL);
      if (!bSuccess) {
        break;
      }
      WBytes += dwWritten;
    }

    //    }

    // Close the pipe handle so the child process stops reading.

    if (!CloseHandle(g_hChildStd_IN_Wr)) {
      return Env.ExitCode;
    }

    // Read from pipe that is the standard output for child process.

    bSuccess = FALSE;
    HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for (;;) {
      bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
      if (!bSuccess || dwRead == 0)
        break;

      bSuccess = WriteFile(hParentStdOut, chBuf, dwRead, &dwWritten, NULL);
      if (!bSuccess) {
        break;
      }
    }

    // Reset inputs.
    Env.Name.clear();
    Env.Args.clear();
    Env.Envs.clear();
    Env.StdIn.clear();
    Env.TimeOut = Env.DEFAULT_TIMEOUT;
    return Env.ExitCode;

    // The remaining open handles are cleaned up when this process terminates.
    // To avoid resource leaks in a larger application, close handles
    // explicitly.
    //
  }
  // spdlog::error("wasmedge_process doesn't support windows now.");
  // return Unexpect(ErrCode::Value::HostFuncError);
#endif
}

Expect<uint32_t>
WasmEdgeProcessGetExitCode::body(const Runtime::CallingFrame &) {
  return Env.ExitCode;
}

Expect<uint32_t>
WasmEdgeProcessGetStdOutLen::body(const Runtime::CallingFrame &) {
  return static_cast<uint32_t>(Env.StdOut.size());
}

Expect<void> WasmEdgeProcessGetStdOut::body(const Runtime::CallingFrame &Frame,
                                            uint32_t BufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  char *Buf = MemInst->getPointer<char *>(BufPtr);
  std::copy_n(Env.StdOut.begin(), Env.StdOut.size(), Buf);
  return {};
}

Expect<uint32_t>
WasmEdgeProcessGetStdErrLen::body(const Runtime::CallingFrame &) {
  return static_cast<uint32_t>(Env.StdErr.size());
}

Expect<void> WasmEdgeProcessGetStdErr::body(const Runtime::CallingFrame &Frame,
                                            uint32_t BufPtr) {
  // Check memory instance from module.
  auto *MemInst = Frame.getMemoryByIndex(0);
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::Value::HostFuncError);
  }

  char *Buf = MemInst->getPointer<char *>(BufPtr);
  std::copy_n(Env.StdErr.begin(), Env.StdErr.size(), Buf);
  return {};
}

} // namespace Host
} // namespace WasmEdge
