// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "host/insertion_sort_example/examplemodule.h"

#include "host/insertion_sort_example/examplefunc.h"

namespace WasmEdge {
namespace Host {

/// Register your functions in module.
InsertionSortExampleModule::InsertionSortExampleModule()
    : ImportObject("insertion_sort_example") {
  addHostFunc("insertion_sort_initialise",
              std::make_unique<IS_RandomnInitialiseFunc>(Env));
  addHostFunc("insertion_sort_print_vector",
              std::make_unique<IS_PrintVectorFunc>(Env));
  addHostFunc("insertion_sort_sort", std::make_unique<IS_SortFunc>(Env));
}

} // namespace Host
} // namespace WasmEdge
