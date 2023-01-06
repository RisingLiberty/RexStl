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

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/unordered_map.h"

TEST_CASE("unordered_map construction")
{
  using hash_table = rsl::unordered_map<int, int>;
  const hash_table map;

  CHECK(map.empty());
  CHECK(map.size() == 0); // NOLINT
  CHECK(map.load_factor() == 0.0f);
  CHECK(map.bucket_count() == 0);

  const hash_table map2 = {{0, 0}, {1, 1}};
  CHECK(map2.size() == 2);
}

TEST_CASE("unordered_map element access")
{
  using hash_table = rsl::unordered_map<int, int>;
  hash_table map   = {{0, 10}, {1, 11}};

  CHECK(map[0] == 10);
  CHECK(map[1] == 11);
  CHECK(map[2] == 0);
}

// NOLINTEND
