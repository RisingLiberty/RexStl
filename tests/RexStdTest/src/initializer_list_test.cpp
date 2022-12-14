// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: initializer_list_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/initializer_list.h"

TEST_CASE("initializer list creation")
{
  rsl::initializer_list<int> ilist = {1, 2, 3};

  REQUIRE(ilist.size() == 3);
  REQUIRE(*ilist.begin() + 0 == 1);
  REQUIRE(*ilist.begin() + 1 == 2);
  REQUIRE(*ilist.begin() + 2 == 3);

  rsl::initializer_list<int> ilist2 = {};
  REQUIRE(ilist2.size() == 0);
}

// NOLINTEND
