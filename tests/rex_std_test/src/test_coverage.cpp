// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_coverage.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

// This file holds tests cases for all code that's generated but not explicitly tested in other files
// This mostly happens because a templated function is instantiated through complex means but not executed

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/format.h"
#include "rex_std/tuple.h"
#include "rex_std/string_view.h"

TEST_CASE("format coverage")
{
    
}
TEST_CASE("tuple coverage")
{
    rsl::tuple<> tuple1;
    rsl::tuple<> tuple2;
    tuple1.swap(tuple2);
}
TEST_CASE("string view coverage")
{
  rsl::basic_string_view<rsl::detail::char8_type> view;
  CHECK(view.data() == nullptr);
  CHECK(view.size() == 0);
}