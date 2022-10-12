// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: unordered_map_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include <catch2/catch.hpp>

#include "rex_std/unordered_map.h"

TEST_CASE("unordered_map construction")
{
  using hash_table = rsl::unordered_map<int, int>;
  const hash_table map;

  REQUIRE(map.empty());
  REQUIRE(map.size() == 0); // NOLINT
  REQUIRE(map.load_factor() == 0.0f);
  REQUIRE(map.bucket_count() == 0);

  const hash_table map2 = { {0, 0}, {1, 1} };
  REQUIRE(map2.size() == 2);
}

TEST_CASE("unordered_map element access")
{
  using hash_table = rsl::unordered_map<int, int>;
  hash_table map = { {0, 10}, {1, 11} };

  REQUIRE(map[0] == 10);
  REQUIRE(map[1] == 11);
  REQUIRE(map[2] == 0);
}