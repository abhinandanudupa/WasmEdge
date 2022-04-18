# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

wasmedge_add_library(wasmedgeHostModuleInsertionSortExample
  examplefunc.cpp
  examplemodule.cpp
)

target_link_libraries(wasmedgeHostModuleInsertionSortExample
  PUBLIC
  wasmedgeCommon
  wasmedgeSystem
)
