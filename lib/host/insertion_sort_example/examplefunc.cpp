// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "host/insertion_sort_example/examplefunc.h"
#include <cmath>
#include <iostream>
#include <vector>

namespace WasmEdge {
namespace Host {

Expect<void> IS_RandomnInitialiseFunc::body(
    [[maybe_unused]] Runtime::Instance::MemoryInstance *MemInst, int length) {
  for (int i = 0; i < length; i++) {
    Env.vec.push_back(rand() % 100);
  }
  return {};
}

Expect<void>
IS_PrintVectorFunc::body(Runtime::Instance::MemoryInstance *MemInst) {
  // Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }
  std::cout << "The vector is:" << std::endl;
  for (int val : Env.vec) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  return {};
}

Expect<void> IS_SortFunc::body(Runtime::Instance::MemoryInstance *MemInst) {
  // Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  int i, key, j, n = Env.vec.size();
  for (i = 1; i < n; i++) {
    key = Env.vec[i];
    j = i - 1;

    /* Move elements of Env.vec[0..i-1], that are
    greater than key, to one position ahead
    of their current position */
    while (j >= 0 && Env.vec[j] > key) {
      Env.vec[j + 1] = Env.vec[j];
      j = j - 1;
    }
    Env.vec[j + 1] = key;
  }
  return {};
}

} // namespace Host
} // namespace WasmEdge
