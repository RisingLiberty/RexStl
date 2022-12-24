// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: source_location_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/source_location.h"

TEST_CASE("source location")
{
  rsl::source_location loc  = rsl::source_location::current();
  rsl::source_location loc2 = rsl::source_location::current();
  REQUIRE(loc.line() + 1 == loc2.line());
  REQUIRE(loc.column() == 2);
  REQUIRE(loc.file_name() == __FILE__);
  REQUIRE(loc.function_name() == __FUNCSIG__);

}

// NOLINTEND
