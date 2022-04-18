// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include "host/insertion_sort_example/exampleenv.h"
#include "runtime/importobj.h"

#include <cstdint>

namespace WasmEdge {
namespace Host {

class InsertionSortExampleModule : public Runtime::ImportObject {
public:
  InsertionSortExampleModule();

  InsertionSortExampleEnvironment &getEnv() { return Env; }

private:
  InsertionSortExampleEnvironment Env;
};

} // namespace Host
} // namespace WasmEdge
