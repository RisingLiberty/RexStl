// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_source_location.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/source_location.h"
#include "rex_std/string_view.h"
#include "rex_std/bonus/compiler.h"
#include "rex_std/iostream.h"

TEST_CASE("source location")
{
  rsl::source_location loc  = rsl::source_location::current();
  rsl::source_location loc2 = rsl::source_location::current();
  rsl::string_view file = __FILE__;
  rsl::string_view func = __func__;
  rsl::string_view loc_file(loc.file_name());
  rsl::string_view loc_func(loc.function_name());
  
  #if defined(RSL_COMPILER_MSVC)
  card32 column = 53;
  #elif defined(RSL_COMPILER_CLANG)
  card32 column = 31;
  #endif
  
  CHECK(loc.line() + 1 == loc2.line());
  CHECK(loc.column() == column);
  CHECK(loc_file == file);
  CHECK(loc_func == func);

}

// NOLINTEND
