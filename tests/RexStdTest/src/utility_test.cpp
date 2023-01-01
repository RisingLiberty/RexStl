// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: utility_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/internal/type_traits/add_const.h"
#include "rex_std/internal/type_traits/add_lvalue_reference.h"
#include "rex_std/internal/type_traits/is_same.h"
#include "rex_std/utility.h"

namespace utility_test
{
  enum class dummy_enum : short
  {

  };
} // namespace utility_test

TEST_CASE("as const")
{
  int x               = 0;
  const auto& const_x = rsl::as_const(x);

  static_assert(rsl::is_same_v<decltype(const_x), rsl::add_lvalue_reference_t<rsl::add_const_t<decltype(x)>>>);
}
TEST_CASE("swap")
{
  int x = 1;
  int y = 2;
  rsl::swap(x, y);

  REQUIRE(x == 2);
  REQUIRE(y == 1);
}
TEST_CASE("exchange")
{
  int x       = 1;
  const int y = rsl::exchange(x, 2);

  REQUIRE(x == 2);
  REQUIRE(y == 1);
}
TEST_CASE("to underlying")
{
  auto underlying = rsl::to_underlying(utility_test::dummy_enum());
  static_assert(rsl::is_same_v<decltype(underlying), rsl::underlying_type_t<utility_test::dummy_enum>>);
}
TEST_CASE("cmp equal")
{
  REQUIRE(rsl::cmp_equal(1, 1) == true);
  REQUIRE(rsl::cmp_equal(1, 2) == false);
  REQUIRE(rsl::cmp_equal(2, 1) == false);
  REQUIRE(rsl::cmp_equal(0u, -0) == true);
  REQUIRE(rsl::cmp_equal(-1, -1) == true);
  REQUIRE(rsl::cmp_equal(-1, 1u) == false);
  REQUIRE(rsl::cmp_equal(1, -1) == false);
}
TEST_CASE("cmp not equal")
{
  REQUIRE(rsl::cmp_not_equal(1, 1) == false);
  REQUIRE(rsl::cmp_not_equal(1, 2) == true);
  REQUIRE(rsl::cmp_not_equal(2, 1) == true);
  REQUIRE(rsl::cmp_not_equal(0u, -0) == false);
  REQUIRE(rsl::cmp_not_equal(-1, -1) == false);
  REQUIRE(rsl::cmp_not_equal(-1, 1u) == true);
  REQUIRE(rsl::cmp_not_equal(1, -1) == true);
}
TEST_CASE("cmp less")
{
  REQUIRE(rsl::cmp_less(1, 1) == false);
  REQUIRE(rsl::cmp_less(1, 2) == true);
  REQUIRE(rsl::cmp_less(2, 1) == false);
  REQUIRE(rsl::cmp_less(0u, -0) == false);
  REQUIRE(rsl::cmp_less(-1, -1) == false);
  REQUIRE(rsl::cmp_less(-1, 1u) == true);
  REQUIRE(rsl::cmp_less(1, -1) == false);
}
TEST_CASE("cmp greater")
{
  REQUIRE(rsl::cmp_greater(1, 1) == false);
  REQUIRE(rsl::cmp_greater(1, 2) == false);
  REQUIRE(rsl::cmp_greater(2, 1) == true);
  REQUIRE(rsl::cmp_greater(0u, -0) == false);
  REQUIRE(rsl::cmp_greater(-1, -1) == false);
  REQUIRE(rsl::cmp_greater(-1, 1u) == false);
  REQUIRE(rsl::cmp_greater(1, -1) == true);
}
TEST_CASE("cmp less equal")
{
  REQUIRE(rsl::cmp_less_equal(1, 1) == true);
  REQUIRE(rsl::cmp_less_equal(1, 2) == true);
  REQUIRE(rsl::cmp_less_equal(2, 1) == false);
  REQUIRE(rsl::cmp_less_equal(0u, -0) == true);
  REQUIRE(rsl::cmp_less_equal(-1, -1) == true);
  REQUIRE(rsl::cmp_less_equal(-1, 1u) == true);
  REQUIRE(rsl::cmp_less_equal(1, -1) == false);
}
TEST_CASE("cmp greater equal")
{
  REQUIRE(rsl::cmp_greater_equal(1, 1) == true);
  REQUIRE(rsl::cmp_greater_equal(1, 2) == false);
  REQUIRE(rsl::cmp_greater_equal(2, 1) == true);
  REQUIRE(rsl::cmp_greater_equal(0u, -0) == true);
  REQUIRE(rsl::cmp_greater_equal(-1, -1) == true);
  REQUIRE(rsl::cmp_greater_equal(-1, 1u) == false);
  REQUIRE(rsl::cmp_greater_equal(1, -1) == true);
}
TEST_CASE("in range")
{
  REQUIRE(rsl::in_range<char>(255) == false);
  REQUIRE(rsl::in_range<unsigned char>(255) == true);
  REQUIRE(rsl::in_range<int>(5'000'000'000) == false);
  REQUIRE(rsl::in_range<int>(2000) == true);
}
TEST_CASE("pair")
{
  rsl::pair my_pair(1, 2);
  REQUIRE(my_pair.first == 1);
  REQUIRE(my_pair.second == 2);
}
TEST_CASE("tuple size")
{
  rsl::pair my_pair(1, 2);

  static_assert(rsl::tuple_size_v<decltype(my_pair)> == 2);
}
TEST_CASE("tuple element")
{
  rsl::pair my_pair(1, 2.0f);

  static_assert(rsl::is_same_v<rsl::tuple_element_t<0, decltype(my_pair)>, int> == true);
  static_assert(rsl::is_same_v<rsl::tuple_element_t<1, decltype(my_pair)>, float> == true);
}
TEST_CASE("integer sequence")
{
  rsl::integer_sequence<int, 0, 1, 2> integers;

  REQUIRE(integers.size() == 3);
}

// NOLINTEND
