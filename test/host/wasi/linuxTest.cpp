#include "common/defines.h"
#include <gtest/gtest.h>
#if WASMEDGE_OS_LINUX

#include "../../../lib/host/wasi/linux.h"

using namespace WasmEdge::Host::WASI::detail;

TEST(linuxTest, fromErrNo) {

  EXPECT_EQ(fromErrNo(0), __WASI_ERRNO_SUCCESS);
  EXPECT_EQ(fromErrNo(E2BIG), __WASI_ERRNO_2BIG);
  EXPECT_EQ(fromErrNo(EACCES), __WASI_ERRNO_ACCES);
  EXPECT_EQ(fromErrNo(EADDRINUSE), __WASI_ERRNO_ADDRINUSE);
  EXPECT_EQ(fromErrNo(EADDRNOTAVAIL), __WASI_ERRNO_ADDRNOTAVAIL);
  EXPECT_EQ(fromErrNo(EAFNOSUPPORT), __WASI_ERRNO_AFNOSUPPORT);
  EXPECT_EQ(fromErrNo(EAGAIN), __WASI_ERRNO_AGAIN);
  EXPECT_EQ(fromErrNo(EALREADY), __WASI_ERRNO_ALREADY);
  EXPECT_EQ(fromErrNo(EBADF), __WASI_ERRNO_BADF);
  EXPECT_EQ(fromErrNo(EBADMSG), __WASI_ERRNO_BADMSG);
  EXPECT_EQ(fromErrNo(EBUSY), __WASI_ERRNO_BUSY);
  EXPECT_EQ(fromErrNo(ECANCELED), __WASI_ERRNO_CANCELED);
  EXPECT_EQ(fromErrNo(ECHILD), __WASI_ERRNO_CHILD);
  EXPECT_EQ(fromErrNo(ECONNABORTED), __WASI_ERRNO_CONNABORTED);
  EXPECT_EQ(fromErrNo(ECONNREFUSED), __WASI_ERRNO_CONNREFUSED);
  EXPECT_EQ(fromErrNo(ECONNRESET), __WASI_ERRNO_CONNRESET);
  EXPECT_EQ(fromErrNo(EDEADLK), __WASI_ERRNO_DEADLK);
  EXPECT_EQ(fromErrNo(EDESTADDRREQ), __WASI_ERRNO_DESTADDRREQ);
  EXPECT_EQ(fromErrNo(EDOM), __WASI_ERRNO_DOM);
  EXPECT_EQ(fromErrNo(EDQUOT), __WASI_ERRNO_DQUOT);
  EXPECT_EQ(fromErrNo(EEXIST), __WASI_ERRNO_EXIST);
  EXPECT_EQ(fromErrNo(EFAULT), __WASI_ERRNO_FAULT);
  EXPECT_EQ(fromErrNo(EFBIG), __WASI_ERRNO_FBIG);
  EXPECT_EQ(fromErrNo(EHOSTUNREACH), __WASI_ERRNO_HOSTUNREACH);
  EXPECT_EQ(fromErrNo(EIDRM), __WASI_ERRNO_IDRM);
  EXPECT_EQ(fromErrNo(EILSEQ), __WASI_ERRNO_ILSEQ);
  EXPECT_EQ(fromErrNo(EINPROGRESS), __WASI_ERRNO_INPROGRESS);
  EXPECT_EQ(fromErrNo(EINTR), __WASI_ERRNO_INTR);
  EXPECT_EQ(fromErrNo(EINVAL), __WASI_ERRNO_INVAL);
  EXPECT_EQ(fromErrNo(EIO), __WASI_ERRNO_IO);
  EXPECT_EQ(fromErrNo(EISCONN), __WASI_ERRNO_ISCONN);
  EXPECT_EQ(fromErrNo(EISDIR), __WASI_ERRNO_ISDIR);
  EXPECT_EQ(fromErrNo(ELOOP), __WASI_ERRNO_LOOP);
  EXPECT_EQ(fromErrNo(EMFILE), __WASI_ERRNO_MFILE);
  EXPECT_EQ(fromErrNo(EMLINK), __WASI_ERRNO_MLINK);
  EXPECT_EQ(fromErrNo(EMSGSIZE), __WASI_ERRNO_MSGSIZE);
  EXPECT_EQ(fromErrNo(EMULTIHOP), __WASI_ERRNO_MULTIHOP);
  EXPECT_EQ(fromErrNo(ENAMETOOLONG), __WASI_ERRNO_NAMETOOLONG);
  EXPECT_EQ(fromErrNo(ENETDOWN), __WASI_ERRNO_NETDOWN);
  EXPECT_EQ(fromErrNo(ENETRESET), __WASI_ERRNO_NETRESET);
  EXPECT_EQ(fromErrNo(ENETUNREACH), __WASI_ERRNO_NETUNREACH);
  EXPECT_EQ(fromErrNo(ENFILE), __WASI_ERRNO_NFILE);
  EXPECT_EQ(fromErrNo(ENOBUFS), __WASI_ERRNO_NOBUFS);
  EXPECT_EQ(fromErrNo(ENODEV), __WASI_ERRNO_NODEV);
  EXPECT_EQ(fromErrNo(ENOENT), __WASI_ERRNO_NOENT);
  EXPECT_EQ(fromErrNo(ENOEXEC), __WASI_ERRNO_NOEXEC);
  EXPECT_EQ(fromErrNo(ENOLCK), __WASI_ERRNO_NOLCK);
  EXPECT_EQ(fromErrNo(ENOLINK), __WASI_ERRNO_NOLINK);
  EXPECT_EQ(fromErrNo(ENOMEM), __WASI_ERRNO_NOMEM);
  EXPECT_EQ(fromErrNo(ENOMSG), __WASI_ERRNO_NOMSG);
  EXPECT_EQ(fromErrNo(ENOPROTOOPT), __WASI_ERRNO_NOPROTOOPT);
  EXPECT_EQ(fromErrNo(ENOSPC), __WASI_ERRNO_NOSPC);
  EXPECT_EQ(fromErrNo(ENOSYS), __WASI_ERRNO_NOSYS);
  EXPECT_EQ(fromErrNo(ENOTCONN), __WASI_ERRNO_NOTCONN);
  EXPECT_EQ(fromErrNo(ENOTDIR), __WASI_ERRNO_NOTDIR);
  EXPECT_EQ(fromErrNo(ENOTEMPTY), __WASI_ERRNO_NOTEMPTY);
  EXPECT_EQ(fromErrNo(ENOTRECOVERABLE), __WASI_ERRNO_NOTRECOVERABLE);
  EXPECT_EQ(fromErrNo(ENOTSOCK), __WASI_ERRNO_NOTSOCK);
  EXPECT_EQ(fromErrNo(ENOTSUP), __WASI_ERRNO_NOTSUP);
  EXPECT_EQ(fromErrNo(ENOTTY), __WASI_ERRNO_NOTTY);
  EXPECT_EQ(fromErrNo(ENXIO), __WASI_ERRNO_NXIO);
  EXPECT_EQ(fromErrNo(EOVERFLOW), __WASI_ERRNO_OVERFLOW);
  EXPECT_EQ(fromErrNo(EOWNERDEAD), __WASI_ERRNO_OWNERDEAD);
  EXPECT_EQ(fromErrNo(EPERM), __WASI_ERRNO_PERM);
  EXPECT_EQ(fromErrNo(EPIPE), __WASI_ERRNO_PIPE);
  EXPECT_EQ(fromErrNo(EPROTO), __WASI_ERRNO_PROTO);
  EXPECT_EQ(fromErrNo(EPROTONOSUPPORT), __WASI_ERRNO_PROTONOSUPPORT);
  EXPECT_EQ(fromErrNo(EPROTOTYPE), __WASI_ERRNO_PROTOTYPE);
  EXPECT_EQ(fromErrNo(ERANGE), __WASI_ERRNO_RANGE);
  EXPECT_EQ(fromErrNo(EROFS), __WASI_ERRNO_ROFS);
  EXPECT_EQ(fromErrNo(ESPIPE), __WASI_ERRNO_SPIPE);
  EXPECT_EQ(fromErrNo(ESRCH), __WASI_ERRNO_SRCH);
  EXPECT_EQ(fromErrNo(ESTALE), __WASI_ERRNO_STALE);
  EXPECT_EQ(fromErrNo(ETIMEDOUT), __WASI_ERRNO_TIMEDOUT);
  EXPECT_EQ(fromErrNo(ETXTBSY), __WASI_ERRNO_TXTBSY);
  EXPECT_EQ(fromErrNo(EXDEV), __WASI_ERRNO_XDEV);
}

TEST(LinuxTest, fromEAIErrNo) {
  EXPECT_EQ(fromEAIErrNo(EAI_ADDRFAMILY), __WASI_ERRNO_AIADDRFAMILY);
  EXPECT_EQ(fromEAIErrNo(EAI_AGAIN), __WASI_ERRNO_AIAGAIN);
  EXPECT_EQ(fromEAIErrNo(EAI_BADFLAGS), __WASI_ERRNO_AIBADFLAG);
  EXPECT_EQ(fromEAIErrNo(EAI_FAIL), __WASI_ERRNO_AIFAIL);
  EXPECT_EQ(fromEAIErrNo(EAI_FAMILY), __WASI_ERRNO_AIFAMILY);
  EXPECT_EQ(fromEAIErrNo(EAI_MEMORY), __WASI_ERRNO_AIMEMORY);
  EXPECT_EQ(fromEAIErrNo(EAI_NODATA), __WASI_ERRNO_AINODATA);
  EXPECT_EQ(fromEAIErrNo(EAI_NONAME), __WASI_ERRNO_AINONAME);
  EXPECT_EQ(fromEAIErrNo(EAI_SERVICE), __WASI_ERRNO_AISERVICE);
  EXPECT_EQ(fromEAIErrNo(EAI_SOCKTYPE), __WASI_ERRNO_AISOCKTYPE);
  EXPECT_EQ(fromEAIErrNo(EAI_SYSTEM), __WASI_ERRNO_AISYSTEM);
}

TEST(LinuxTest, toClockId) {
  EXPECT_EQ(toClockId(__WASI_CLOCKID_REALTIME), CLOCK_REALTIME);
  EXPECT_EQ(toClockId(__WASI_CLOCKID_MONOTONIC), CLOCK_MONOTONIC);
  EXPECT_EQ(toClockId(__WASI_CLOCKID_PROCESS_CPUTIME_ID),
            CLOCK_PROCESS_CPUTIME_ID);
  EXPECT_EQ(toClockId(__WASI_CLOCKID_THREAD_CPUTIME_ID),
            CLOCK_THREAD_CPUTIME_ID);
}

TEST(LinuxTest, toTimespec) {
  const __wasi_timestamp_t kNanoSeconds1 = 9LL * 1000 * 1000 * 1000;
  const __wasi_timestamp_t kNanoSeconds2 = 5LL * 1000 * 1000;
  const __wasi_timestamp_t kTimestamp = kNanoSeconds1 + kNanoSeconds2;
  auto result = toTimespec(kTimestamp);
  EXPECT_EQ(result.tv_sec, kNanoSeconds1 / (1000 * 1000 * 1000));
  EXPECT_EQ(result.tv_nsec, kNanoSeconds2);
}

TEST(LinuxTest, fromTimespec) {
  const __time_t kSec = 20;
  const __time_t kNsec = 30;
  const timespec kTime = {kSec, kNsec};
  auto result = fromTimespec(kTime);
  const __wasi_timestamp_t kExpectResult = kSec * 1000 * 1000 * 1000 + kNsec;

  EXPECT_EQ(result, kExpectResult);
}

#if !__GLIBC_PREREQ(2, 6)
TEST(LinuxTest, toTimeval) {
  const __wasi_timestamp_t kNanoSeconds1 = 9LL * 1000 * 1000 * 1000;
  const __wasi_timestamp_t kNanoSeconds2 = 5LL * 1000 * 1000;
  const __wasi_timestamp_t kTimestamp = kNanoSeconds1 + kNanoSeconds2;
  auto result = toTimeval(kTimestamp);
  const timeval kExpectResult = {kNanoSeconds1 / (1000 * 1000 * 1000),
                                 kNanoSeconds2 / 1000};

  EXPECT_EQ(result.tv_sec, kExpectResult.tv_sec);
  EXPECT_EQ(result.tv_usec, kExpectResult.tv_usec);
}

TEST(LinuxTest, toTimeva_with_timespec_signiture) {
  const __time_t kSec = 20;
  const __time_t kNsec = 30 * 1000 * 1000;
  const timespec kTime = {kSec, kNsec};
  auto result = toTimeval(kTime);

  EXPECT_EQ(result.tv_sec, kSec);
  EXPECT_EQ(result.tv_usec, kNsec / 1000);
}
#endif

TEST(LinuxTest, toAdvice) {
  EXPECT_EQ(toAdvice(__WASI_ADVICE_NORMAL), POSIX_FADV_NORMAL);
  EXPECT_EQ(toAdvice(__WASI_ADVICE_SEQUENTIAL), POSIX_FADV_SEQUENTIAL);
  EXPECT_EQ(toAdvice(__WASI_ADVICE_RANDOM), POSIX_FADV_RANDOM);
  EXPECT_EQ(toAdvice(__WASI_ADVICE_WILLNEED), POSIX_FADV_WILLNEED);
  EXPECT_EQ(toAdvice(__WASI_ADVICE_DONTNEED), POSIX_FADV_DONTNEED);
  EXPECT_EQ(toAdvice(__WASI_ADVICE_NOREUSE), POSIX_FADV_NOREUSE);
}

TEST(LiuxTest, fromFileType) {
  EXPECT_EQ(fromFileType(static_cast<mode_t>(S_IFBLK)),
            __WASI_FILETYPE_BLOCK_DEVICE);
  EXPECT_EQ(fromFileType(static_cast<mode_t>(S_IFCHR)),
            __WASI_FILETYPE_CHARACTER_DEVICE);
  EXPECT_EQ(fromFileType(static_cast<mode_t>(S_IFDIR)),
            __WASI_FILETYPE_DIRECTORY);
  EXPECT_EQ(fromFileType(static_cast<mode_t>(S_IFREG)),
            __WASI_FILETYPE_REGULAR_FILE);
  EXPECT_EQ(fromFileType(static_cast<mode_t>(S_IFSOCK)),
            __WASI_FILETYPE_SOCKET_STREAM);
  EXPECT_EQ(fromFileType(static_cast<mode_t>(S_IFLNK)),
            __WASI_FILETYPE_SYMBOLIC_LINK);
  EXPECT_EQ(fromFileType(static_cast<mode_t>(S_IFIFO)),
            __WASI_FILETYPE_UNKNOWN);
}

TEST(LinuxTest, fromFileType) {
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(6)),
            __WASI_FILETYPE_BLOCK_DEVICE);
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(DT_CHR)),
            __WASI_FILETYPE_CHARACTER_DEVICE);
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(DT_DIR)),
            __WASI_FILETYPE_DIRECTORY);
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(DT_LNK)),
            __WASI_FILETYPE_SYMBOLIC_LINK);
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(DT_REG)),
            __WASI_FILETYPE_REGULAR_FILE);
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(DT_SOCK)),
            __WASI_FILETYPE_SOCKET_STREAM);
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(DT_FIFO)),
            __WASI_FILETYPE_UNKNOWN);
  EXPECT_EQ(fromFileType(static_cast<uint8_t>(DT_UNKNOWN)),
            __WASI_FILETYPE_UNKNOWN);
}

TEST(LinuxTest, toWhence) {
  EXPECT_EQ(toWhence(__WASI_WHENCE_CUR), SEEK_CUR);
  EXPECT_EQ(toWhence(__WASI_WHENCE_END), SEEK_END);
  EXPECT_EQ(toWhence(__WASI_WHENCE_SET), SEEK_SET);
}

TEST(LinuxTest, toSockOptLevel) {
  EXPECT_EQ(toSockOptLevel(__WASI_SOCK_OPT_LEVEL_SOL_SOCKET), SOL_SOCKET);
}

TEST(LinuxTest, toSockOptSoName) {
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_REUSEADDR), SO_REUSEADDR);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_TYPE), SO_TYPE);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_ERROR), SO_REUSEADDR);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_DONTROUTE), SO_TYPE);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_BROADCAST), SO_REUSEADDR);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_SNDBUF), SO_TYPE);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_RCVBUF), SO_REUSEADDR);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_KEEPALIVE), SO_TYPE);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_OOBINLINE), SO_REUSEADDR);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_LINGER), SO_TYPE);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_RCVLOWAT), SO_REUSEADDR);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_RCVTIMEO), SO_TYPE);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_SNDTIMEO), SO_REUSEADDR);
  EXPECT_EQ(toSockOptSoName(__WASI_SOCK_OPT_SO_ACCEPTCONN), SO_TYPE);
}

TEST(LinuxTest, fromAIFlags) {
  EXPECT_EQ(fromAIFlags(AI_PASSIVE), __WASI_AIFLAGS_AI_PASSIVE);
  EXPECT_EQ(fromAIFlags(AI_CANONNAME), __WASI_AIFLAGS_AI_CANONNAME);
  EXPECT_EQ(fromAIFlags(AI_NUMERICHOST), __WASI_AIFLAGS_AI_NUMERICHOST);
  EXPECT_EQ(fromAIFlags(AI_NUMERICSERV), __WASI_AIFLAGS_AI_NUMERICSERV);
  EXPECT_EQ(fromAIFlags(AI_V4MAPPED), __WASI_AIFLAGS_AI_V4MAPPED);
  EXPECT_EQ(fromAIFlags(AI_ALL), __WASI_AIFLAGS_AI_ALL);
  EXPECT_EQ(fromAIFlags(AI_ADDRCONFIG), __WASI_AIFLAGS_AI_ADDRCONFIG);
  EXPECT_EQ(fromAIFlags(0), 0);
}

TEST(LinuxTest, toAIFlags) {
  EXPECT_EQ(toAIFlags(__WASI_AIFLAGS_AI_PASSIVE), AI_PASSIVE);
  EXPECT_EQ(toAIFlags(__WASI_AIFLAGS_AI_CANONNAME), AI_CANONNAME);
  EXPECT_EQ(toAIFlags(__WASI_AIFLAGS_AI_NUMERICHOST), AI_NUMERICHOST);
  EXPECT_EQ(toAIFlags(__WASI_AIFLAGS_AI_NUMERICSERV), AI_NUMERICSERV);
  EXPECT_EQ(toAIFlags(__WASI_AIFLAGS_AI_V4MAPPED), AI_V4MAPPED);
  EXPECT_EQ(toAIFlags(__WASI_AIFLAGS_AI_ALL), AI_ALL);
  EXPECT_EQ(toAIFlags(__WASI_AIFLAGS_AI_ADDRCONFIG), AI_ADDRCONFIG);
  EXPECT_EQ(toAIFlags(static_cast<__wasi_aiflags_t>(0)), 0);
}

TEST(LinuxTest, fromSockType) {
  EXPECT_EQ(fromSockType(0), __WASI_SOCK_TYPE_SOCK_ANY);
  EXPECT_EQ(fromSockType(SOCK_DGRAM), __WASI_SOCK_TYPE_SOCK_DGRAM);
  EXPECT_EQ(fromSockType(SOCK_STREAM), __WASI_SOCK_TYPE_SOCK_STREAM);
}

TEST(LinuxTest, toSockType) {
  EXPECT_EQ(toSockType(__WASI_SOCK_TYPE_SOCK_ANY), 0);
  EXPECT_EQ(toSockType(__WASI_SOCK_TYPE_SOCK_DGRAM), SOCK_DGRAM);
  EXPECT_EQ(toSockType(__WASI_SOCK_TYPE_SOCK_STREAM), SOCK_STREAM);
}

TEST(LinuxTest, fromProtocol) {
  EXPECT_EQ(fromProtocol(IPPROTO_IP), __WASI_PROTOCOL_IPPROTO_IP);
  EXPECT_EQ(fromProtocol(IPPROTO_TCP), __WASI_PROTOCOL_IPPROTO_TCP);
  EXPECT_EQ(fromProtocol(IPPROTO_UDP), __WASI_PROTOCOL_IPPROTO_UDP);
}

TEST(LinuxTest, toProtocol) {
  EXPECT_EQ(toProtocol(__WASI_PROTOCOL_IPPROTO_IP), IPPROTO_IP);
  EXPECT_EQ(toProtocol(__WASI_PROTOCOL_IPPROTO_TCP), IPPROTO_TCP);
  EXPECT_EQ(toProtocol(__WASI_PROTOCOL_IPPROTO_UDP), IPPROTO_UDP);
}

TEST(LinuxTest, fromAddressFamily) {
  EXPECT_EQ(fromAddressFamily(PF_UNSPEC), __WASI_ADDRESS_FAMILY_UNSPEC);
  EXPECT_EQ(fromAddressFamily(PF_INET), __WASI_ADDRESS_FAMILY_INET4);
  EXPECT_EQ(fromAddressFamily(PF_INET6), __WASI_ADDRESS_FAMILY_INET6);
}

TEST(LinuxTest, toAddressFamily) {
  EXPECT_EQ(toAddressFamily(__WASI_ADDRESS_FAMILY_UNSPEC), PF_UNSPEC);
  EXPECT_EQ(toAddressFamily(__WASI_ADDRESS_FAMILY_INET4), PF_INET);
  EXPECT_EQ(toAddressFamily(__WASI_ADDRESS_FAMILY_INET6), PF_INET6);
}
#endif