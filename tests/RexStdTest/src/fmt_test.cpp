// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"

#include "rex_std/format.h"

TEST_CASE("format")
{
  rsl::string s = rsl::format("{}", 1);
  REQUIRE(s == "1");
}