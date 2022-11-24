// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: array_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/optional.h"

TEST_CASE("optional creation")
{
  rsl::optional<int> opt;

  REQUIRE(opt.has_value() == false);
  REQUIRE(opt.value_or(2) == 2);

  rsl::optional<int> opt2 = 1;
  REQUIRE(opt2.has_value() == true);
  REQUIRE(opt2.value_or(2) == 1);
  REQUIRE(*opt2 == 1);

  rsl::optional<int> opt3 = opt2;
  REQUIRE(opt2.has_value() == true);
  REQUIRE(opt2.value_or(2) == 1);
  REQUIRE(opt2.value() == 1);
  REQUIRE(*opt2 == 1);
  REQUIRE(opt3.has_value() == true);
  REQUIRE(opt3.value_or(2) == 1);
  REQUIRE(opt3.value() == 1);
  REQUIRE(*opt3 == 1);

  rsl::optional<int> opt4 = rsl::move(opt3);
  REQUIRE(opt3.has_value() == true);
  REQUIRE(opt3.value_or(2) == 1);
  REQUIRE(opt4.has_value() == true);
  REQUIRE(opt4.value_or(2) == 1);
  REQUIRE(*opt4 == 1);

  rsl::optional<bool> opt5(opt4);
  REQUIRE(opt5.has_value() == true);
  REQUIRE(opt5.value() == true);
  REQUIRE(opt5.value_or(false) == true);
}

TEST_CASE("optional modifiers")
{
  rsl::optional<int> opt  = 3;
  rsl::optional<int> opt2 = 4;

  opt.swap(opt2);
  REQUIRE(opt.value() == 4);
  REQUIRE(opt2.value() == 3);

  opt.reset();
  REQUIRE(opt.has_value() == false);
  REQUIRE(opt.value_or(2) == 2);

  opt.emplace(10);
  REQUIRE(opt.has_value() == true);
  REQUIRE(opt.value_or(2) == 10);
  REQUIRE(opt.value() == 10);
  REQUIRE(*opt == 10);
}

// NOLINTEND
