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

#include "rex_std_test/catch2/catch.hpp"

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

  rsl::optional<int> opt6 = rsl::nullopt_t{};

  REQUIRE(opt6.has_value() == false);
  REQUIRE(opt6.value_or(2) == 2);

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
  opt.swap(opt2);
  REQUIRE(opt.has_value() == true);
  REQUIRE(opt.value_or(2) == 3);
  REQUIRE(opt2.has_value() == false);
  REQUIRE(opt2.value_or(2) == 2);
  opt.swap(opt2);
  REQUIRE(opt.has_value() == false);
  REQUIRE(opt.value_or(2) == 2);
  REQUIRE(opt2.has_value() == true);
  REQUIRE(opt2.value_or(2) == 3);

  opt.emplace(10);
  REQUIRE(opt.has_value() == true);
  REQUIRE(opt.value_or(2) == 10);
  REQUIRE(opt.value() == 10);
  REQUIRE(*opt == 10);

  opt.emplace(20);
  REQUIRE(opt.has_value() == true);
  REQUIRE(opt.value_or(2) == 20);
  REQUIRE(opt.value() == 20);
  REQUIRE(*opt == 20);

}

TEST_CASE("coverage tests")
{
  rsl::optional<uint64> opt = 3ui64;
  REQUIRE(opt.has_value() == true);
  REQUIRE(opt.value() == 3);
  REQUIRE(*opt == 3);

  rsl::optional<uint32> opt2 = 3;
  REQUIRE(opt2.has_value() == true);
}

// NOLINTEND
