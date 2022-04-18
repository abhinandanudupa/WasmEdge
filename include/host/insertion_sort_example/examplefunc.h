// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include "common/defines.h"
#include "host/insertion_sort_example/examplebase.h"
#include <cstdint>
#include <iostream>
#include <vector>

namespace WasmEdge {
namespace Host {

class IS_RandomnInitialiseFunc
    : public InsertionSortExample<IS_RandomnInitialiseFunc> {
public:
  IS_RandomnInitialiseFunc(InsertionSortExampleEnvironment &HostEnv)
      : InsertionSortExample(HostEnv) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst, int length);
};

class IS_PrintVectorFunc : public InsertionSortExample<IS_PrintVectorFunc> {
public:
  IS_PrintVectorFunc(InsertionSortExampleEnvironment &HostEnv)
      : InsertionSortExample(HostEnv) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst);
};

class IS_SortFunc : public InsertionSortExample<IS_SortFunc> {
public:
  IS_SortFunc(InsertionSortExampleEnvironment &HostEnv)
      : InsertionSortExample(HostEnv) {}
  Expect<void> body(Runtime::Instance::MemoryInstance *MemInst);
};

} // namespace Host
} // namespace WasmEdge
