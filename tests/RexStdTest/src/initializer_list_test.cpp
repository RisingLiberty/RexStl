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

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/initializer_list.h"

TEST_CASE("initializer list creation")
{
  rsl::initializer_list<int> ilist = {1, 2, 3};

  CHECK(ilist.size() == 3);
  CHECK(*ilist.begin() + 0 == 1);
  CHECK(*ilist.begin() + 1 == 2);
  CHECK(*ilist.begin() + 2 == 3);

  rsl::initializer_list<int> ilist2 = {};
  CHECK(ilist2.size() == 0);
}

// NOLINTEND
