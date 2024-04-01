// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_iterator.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/iterator.h"
#include "rex_std/array.h"

TEST_CASE("Iterator Advance")
{
  rsl::array arr = { 1,2,3 };
  auto it = arr.cbegin();

  rsl::advance(it, 1);

  CHECK(it == arr.cbegin() + 1);
  CHECK(*it == 2);

  rsl::advance(it, -1);

  CHECK(it == arr.cbegin());
  CHECK(*it == 1);

  rsl::advance(it, 2);

  CHECK(it == arr.cbegin() + 2);
  CHECK(*it == 3);
}

TEST_CASE("Move Iterator")
{

}

TEST_CASE("Reverse Iterator")
{

}