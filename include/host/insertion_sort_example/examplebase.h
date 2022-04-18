// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include "common/errcode.h"
#include "host/insertion_sort_example/exampleenv.h"
#include "runtime/hostfunc.h"

namespace WasmEdge {
namespace Host {

template <typename T> class InsertionSortExample : public Runtime::HostFunction<T> {
public:
  InsertionSortExample(InsertionSortExampleEnvironment &HostEnv)
      : Runtime::HostFunction<T>(0), Env(HostEnv) {}

protected:
  InsertionSortExampleEnvironment &Env;
};

} // namespace Host
} // namespace WasmEdge
