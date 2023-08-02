// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_optional.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/optional.h"

TEST_CASE("optional creation")
{
  rsl::optional<int> opt;

  CHECK(opt.has_value() == false);
  CHECK(opt.value_or(2) == 2);

  rsl::optional<int> opt2 = 1;
  CHECK(opt2.has_value() == true);
  CHECK(opt2.value_or(2) == 1);
  CHECK(*opt2 == 1);

  rsl::optional<int> opt3 = opt2;
  CHECK(opt2.has_value() == true);
  CHECK(opt2.value_or(2) == 1);
  CHECK(opt2.value() == 1);
  CHECK(*opt2 == 1);
  CHECK(opt3.has_value() == true);
  CHECK(opt3.value_or(2) == 1);
  CHECK(opt3.value() == 1);
  CHECK(*opt3 == 1);

  rsl::optional<int> opt4 = rsl::move(opt3);
  CHECK(opt3.has_value() == true);
  CHECK(opt3.value_or(2) == 1);
  CHECK(opt4.has_value() == true);
  CHECK(opt4.value_or(2) == 1);
  CHECK(*opt4 == 1);

  rsl::optional<bool> opt5(opt4);
  CHECK(opt5.has_value() == true);
  CHECK(opt5.value() == true);
  CHECK(opt5.value_or(false) == true);

  rsl::optional<int> opt6 = rsl::nullopt_t{};

  CHECK(opt6.has_value() == false);
  CHECK(opt6.value_or(2) == 2);

}

TEST_CASE("optional modifiers")
{
  rsl::optional<int> opt  = 3;
  rsl::optional<int> opt2 = 4;

  opt.swap(opt2);
  CHECK(opt.value() == 4);
  CHECK(opt2.value() == 3);

  opt.reset();
  CHECK(opt.has_value() == false);
  CHECK(opt.value_or(2) == 2);
  opt.swap(opt2);
  CHECK(opt.has_value() == true);
  CHECK(opt.value_or(2) == 3);
  CHECK(opt2.has_value() == false);
  CHECK(opt2.value_or(2) == 2);
  opt.swap(opt2);
  CHECK(opt.has_value() == false);
  CHECK(opt.value_or(2) == 2);
  CHECK(opt2.has_value() == true);
  CHECK(opt2.value_or(2) == 3);

  opt.emplace(10);
  CHECK(opt.has_value() == true);
  CHECK(opt.value_or(2) == 10);
  CHECK(opt.value() == 10);
  CHECK(*opt == 10);

  opt.emplace(20);
  CHECK(opt.has_value() == true);
  CHECK(opt.value_or(2) == 20);
  CHECK(opt.value() == 20);
  CHECK(*opt == 20);

}

TEST_CASE("coverage tests")
{
  rsl::optional<uint64> opt = 3ui64;
  CHECK(opt.has_value() == true);
  CHECK(opt.value() == 3);
  CHECK(*opt == 3);

  rsl::optional<uint32> opt2 = 3;
  CHECK(opt2.has_value() == true);
}

// NOLINTEND
