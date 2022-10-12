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

#include "rex_std/source_location.h"

TEST_CASE("source location")
{
  rsl::source_location loc = rsl::source_location::current();
  REQUIRE(loc.line() == 19);
}