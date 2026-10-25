// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_tuple.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/functional.h"
#include "rex_std/tuple.h"
#include "rex_std/type_traits.h"

#include "rex_std_test/test_object.h"

TEST_CASE("tuple construction")
{
  // default construction
  {
    rsl::tuple<int, float> t;
    rsl::get<0>(t) = 1;
    rsl::get<1>(t) = 2.0f;
    CHECK(rsl::get<0>(t) == 1);
    CHECK(rsl::get<1>(t) == 2.0f);
  }

  // construction from values
  {
    rsl::tuple<int, float, char> t(1, 2.0f, 'c');
    CHECK(rsl::get<0>(t) == 1);
    CHECK(rsl::get<1>(t) == 2.0f);
    CHECK(rsl::get<2>(t) == 'c');
  }

  // single element tuple
  {
    rsl::tuple<int> t(5);
    CHECK(rsl::get<0>(t) == 5);
  }

  // empty tuple
  {
    rsl::tuple<> t;
    CHECK(rsl::tuple_size_v<decltype(t)> == 0);
  }

  // move construction
  {
    using namespace rsl::test;
    test_object::reset();
    {
      rsl::tuple<test_object> t(test_object(5));
      rsl::tuple<test_object> moved(rsl::move(t));
      CHECK(rsl::get<0>(moved).x() == 5);
    }
    CHECK(test_object::is_clear());
    test_object::reset();
  }

  // tuple of references
  {
    int x = 1;
    rsl::tuple<int&> t(x);
    rsl::get<0>(t) = 2;
    CHECK(x == 2);
  }
}

TEST_CASE("tuple get")
{
  rsl::tuple<int, float, char> t(1, 2.0f, 'c');

  // get by index
  CHECK(rsl::get<0>(t) == 1);
  rsl::get<0>(t) = 10;
  CHECK(rsl::get<0>(t) == 10);

  // const access
  const rsl::tuple<int, float, char>& const_t = t;
  CHECK(rsl::get<0>(const_t) == 10);
  CHECK(rsl::get<1>(const_t) == 2.0f);
  static_assert(rsl::is_same_v<decltype(rsl::get<0>(const_t)), const int&>);

  // rvalue access
  static_assert(rsl::is_same_v<decltype(rsl::get<0>(rsl::move(t))), int&&>);
  int moved = rsl::get<0>(rsl::move(t));
  CHECK(moved == 10);
}

TEST_CASE("tuple size and element")
{
  using tuple_type = rsl::tuple<int, float, char>;

  static_assert(rsl::tuple_size_v<tuple_type> == 3);
  static_assert(rsl::tuple_size_v<rsl::tuple<>> == 0);
  static_assert(rsl::tuple_size_v<rsl::tuple<int>> == 1);
  static_assert(rsl::tuple_size_v<const tuple_type> == 3);

  static_assert(rsl::is_same_v<rsl::tuple_element_t<0, tuple_type>, int>);
  static_assert(rsl::is_same_v<rsl::tuple_element_t<1, tuple_type>, float>);
  static_assert(rsl::is_same_v<rsl::tuple_element_t<2, tuple_type>, char>);

  CHECK(rsl::tuple_size<tuple_type>::value == 3);
}

TEST_CASE("tuple assignment")
{
  rsl::tuple<int, float> t1(1, 2.0f);
  rsl::tuple<int, float> t2(3, 4.0f);

  t1 = t2;
  CHECK(rsl::get<0>(t1) == 3);
  CHECK(rsl::get<1>(t1) == 4.0f);

  rsl::get<0>(t2) = 5;
  CHECK(rsl::get<0>(t1) == 3);
}

TEST_CASE("tuple swap")
{
  rsl::tuple<int, float> t1(1, 2.0f);
  rsl::tuple<int, float> t2(3, 4.0f);

  t1.swap(t2);
  CHECK(rsl::get<0>(t1) == 3);
  CHECK(rsl::get<1>(t1) == 4.0f);
  CHECK(rsl::get<0>(t2) == 1);
  CHECK(rsl::get<1>(t2) == 2.0f);

  rsl::swap(t1, t2);
  CHECK(rsl::get<0>(t1) == 1);
  CHECK(rsl::get<0>(t2) == 3);
}

TEST_CASE("tuple comparison")
{
  rsl::tuple<int, float> t1(1, 2.0f);
  rsl::tuple<int, float> t2(1, 2.0f);
  rsl::tuple<int, float> t3(1, 3.0f);
  rsl::tuple<int, float> t4(2, 0.0f);

  CHECK(t1 == t2);
  CHECK(!(t1 != t2));
  CHECK(t1 != t3);

  // lexicographical comparison
  CHECK(t1 < t3);
  CHECK(t3 < t4);
  CHECK(t1 < t4);
  CHECK(!(t3 < t1));
  CHECK(!(t1 < t2));

  CHECK(t4 > t1);
  CHECK(t1 <= t2);
  CHECK(t1 <= t3);
  CHECK(t1 >= t2);
  CHECK(t4 >= t3);
}

TEST_CASE("make tuple")
{
  auto t = rsl::make_tuple(1, 2.0f, 'c');
  static_assert(rsl::is_same_v<decltype(t), rsl::tuple<int, float, char>>);
  CHECK(rsl::get<0>(t) == 1);
  CHECK(rsl::get<1>(t) == 2.0f);
  CHECK(rsl::get<2>(t) == 'c');
}

TEST_CASE("tie")
{
  int a   = 0;
  float b = 0.0f;

  auto t = rsl::tie(a, b);
  static_assert(rsl::is_same_v<decltype(t), rsl::tuple<int&, float&>>);
  rsl::get<0>(t) = 10;
  CHECK(a == 10);

  // tie can be used for lexicographical comparison
  int c = 1;
  int d = 2;
  CHECK(rsl::tie(c, d) < rsl::tie(d, c));
}

TEST_CASE("forward as tuple")
{
  int x  = 1;
  auto t = rsl::forward_as_tuple(x, 2);
  static_assert(rsl::is_same_v<decltype(t), rsl::tuple<int&, int&&>>);
  rsl::get<0>(t) = 5;
  CHECK(x == 5);
}

TEST_CASE("apply")
{
  auto t = rsl::make_tuple(1, 2, 3);
  CHECK(rsl::apply([](int a, int b, int c) { return a + b + c; }, t) == 6);

  auto t2 = rsl::make_tuple(2.0f, 3.0f);
  CHECK(rsl::apply([](float a, float b) { return a * b; }, t2) == 6.0f);

  // arguments can be modified through apply
  rsl::apply([](int& a, int&, int&) { a = 10; }, t);
  CHECK(rsl::get<0>(t) == 10);

  CHECK(rsl::apply([]() { return 42; }, rsl::tuple<>()) == 42);
}

// NOLINTEND
