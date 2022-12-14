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

#include <catch2/catch.hpp>

// NOLINTBEGIN

#include "rex_std/array.h"

TEST_CASE("array construction")
{
  const rsl::array<int, 10> arr;
  REQUIRE(arr.size() == 10);

  const rsl::array<int, 10> arr2 = {1, 2, 3};
  REQUIRE(arr.size() == 10);
}

TEST_CASE("array assignment")
{
  rsl::array<int, 10> arr;
  const rsl::array<int, 10> arr2;

  REQUIRE(arr.size() == 10);
  REQUIRE(arr2.size() == 10);

  arr = arr2;

  REQUIRE(arr.size() == 10);
  REQUIRE(arr2.size() == 10);
}

TEST_CASE("array element access")
{
  rsl::array<int, 10> arr;
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;

  REQUIRE(arr[0] == 1);
  REQUIRE(arr[1] == 2);
  REQUIRE(arr[2] == 3);

  const rsl::array<int, 10> arr2 = {1, 2, 3};
  REQUIRE(arr[0] == 1);
  REQUIRE(arr[1] == 2);
  REQUIRE(arr[2] == 3);
  REQUIRE(arr[3] == 0);
}

// NOLINTEND
