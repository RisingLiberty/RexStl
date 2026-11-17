// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_span.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/span.h"
#include "rex_std/array.h"
#include "rex_std/string.h"
#include "rex_std/string_view.h"
#include "rex_std/type_traits.h"
#include "rex_std/vector.h"

TEST_CASE("span construction")
{
  // default construction
  {
    rsl::span<int> s;
    CHECK(s.empty());
    CHECK(s.size() == 0);
    CHECK(s.data() == nullptr);

    rsl::span<int, 0> s0;
    CHECK(s0.empty());

    static_assert(rsl::is_default_constructible_v<rsl::span<int>>);
    static_assert(rsl::is_default_constructible_v<rsl::span<int, 0>>);
    static_assert(!rsl::is_default_constructible_v<rsl::span<int, 3>>);
  }

  // pointer and count
  {
    int arr[] = {1, 2, 3, 4};
    rsl::span<int> s(arr, 3);
    CHECK(s.data() == arr);
    CHECK(s.size() == 3);
    CHECK(!s.empty());

    rsl::span<int, 4> fixed(arr, 4);
    CHECK(fixed.size() == 4);
  }

  // pointer range
  {
    int arr[] = {1, 2, 3, 4};
    rsl::span<int> s(arr + 1, arr + 4);
    CHECK(s.data() == arr + 1);
    CHECK(s.size() == 3);
    CHECK(s[0] == 2);
  }

  // c style array
  {
    int arr[] = {1, 2, 3};
    rsl::span<int> s(arr);
    CHECK(s.size() == 3);
    CHECK(s.data() == arr);

    rsl::span<int, 3> fixed(arr);
    CHECK(fixed.size() == 3);

    rsl::span<const int> const_span(arr);
    CHECK(const_span.size() == 3);

    static_assert(!rsl::is_constructible_v<rsl::span<int, 2>, int(&)[3]>);
  }

  // rsl::array
  {
    rsl::array<int, 3> arr = {1, 2, 3};
    rsl::span<int> s(arr);
    CHECK(s.size() == 3);
    CHECK(s.data() == arr.data());

    rsl::span<int, 3> fixed(arr);
    CHECK(fixed[2] == 3);

    const rsl::array<int, 3>& const_arr = arr;
    rsl::span<const int> const_span(const_arr);
    CHECK(const_span.size() == 3);

    static_assert(!rsl::is_constructible_v<rsl::span<int>, const rsl::array<int, 3>&>);
    static_assert(!rsl::is_constructible_v<rsl::span<int, 4>, rsl::array<int, 3>&>);
  }

  // containers
  {
    rsl::vector<int> vec = {1, 2, 3, 4, 5};
    rsl::span<int> s(vec);
    CHECK(s.size() == 5);
    CHECK(s.data() == vec.data());

    const rsl::vector<int>& const_vec = vec;
    rsl::span<const int> const_span(const_vec);
    CHECK(const_span.size() == 5);

    // static extent from a container has to be explicit
    rsl::span<int, 5> fixed(vec);
    CHECK(fixed.size() == 5);
    static_assert(!rsl::is_convertible_v<rsl::vector<int>&, rsl::span<int, 5>>);
    static_assert(rsl::is_convertible_v<rsl::vector<int>&, rsl::span<int>>);

    // a span of mutable elements can't view a const container
    static_assert(!rsl::is_constructible_v<rsl::span<int>, const rsl::vector<int>&>);

    rsl::string str("hello");
    rsl::span<char> str_span(str);
    CHECK(str_span.size() == 5);
    CHECK(str_span[0] == 'h');

    rsl::string_view view("world");
    rsl::span<const char> view_span(view);
    CHECK(view_span.size() == 5);
    CHECK(view_span[4] == 'd');
  }

  // from other spans
  {
    int arr[] = {1, 2, 3};
    rsl::span<int, 3> fixed(arr);

    rsl::span<int> dynamic = fixed;
    CHECK(dynamic.size() == 3);

    rsl::span<const int> const_span = dynamic;
    CHECK(const_span.data() == arr);

    rsl::span<const int, 3> const_fixed = fixed;
    CHECK(const_fixed.size() == 3);

    // dynamic -> static has to be explicit
    rsl::span<int, 3> back_to_fixed(dynamic);
    CHECK(back_to_fixed.data() == arr);
    static_assert(!rsl::is_convertible_v<rsl::span<int>, rsl::span<int, 3>>);

    // const -> non const isn't allowed
    static_assert(!rsl::is_constructible_v<rsl::span<int>, rsl::span<const int>>);
    // different extents aren't allowed
    static_assert(!rsl::is_constructible_v<rsl::span<int, 2>, rsl::span<int, 3>>);

    // copying
    rsl::span<int> copy = dynamic;
    CHECK(copy.data() == dynamic.data());
    CHECK(copy.size() == dynamic.size());

    rsl::span<int> assigned;
    assigned = dynamic;
    CHECK(assigned.data() == arr);
    CHECK(assigned.size() == 3);
  }
}

TEST_CASE("span deduction guides")
{
  int arr[] = {1, 2, 3};
  rsl::span s1(arr);
  static_assert(rsl::is_same_v<decltype(s1), rsl::span<int, 3>>);

  rsl::array<int, 4> rsl_arr = {1, 2, 3, 4};
  rsl::span s2(rsl_arr);
  static_assert(rsl::is_same_v<decltype(s2), rsl::span<int, 4>>);

  const rsl::array<int, 4>& const_rsl_arr = rsl_arr;
  rsl::span s3(const_rsl_arr);
  static_assert(rsl::is_same_v<decltype(s3), rsl::span<const int, 4>>);

  rsl::vector<int> vec = {1, 2};
  rsl::span s4(vec);
  static_assert(rsl::is_same_v<decltype(s4), rsl::span<int>>);

  const rsl::vector<int>& const_vec = vec;
  rsl::span s5(const_vec);
  static_assert(rsl::is_same_v<decltype(s5), rsl::span<const int>>);

  CHECK(s1.size() == 3);
  CHECK(s2.size() == 4);
  CHECK(s3.size() == 4);
  CHECK(s4.size() == 2);
  CHECK(s5.size() == 2);
}

TEST_CASE("span types")
{
  static_assert(rsl::is_same_v<rsl::span<const int>::element_type, const int>);
  static_assert(rsl::is_same_v<rsl::span<const int>::value_type, int>);
  static_assert(rsl::is_same_v<rsl::span<int>::pointer, int*>);
  static_assert(rsl::is_same_v<rsl::span<int>::reference, int&>);

  static_assert(rsl::span<int>::extent == rsl::dynamic_extent);
  static_assert(rsl::span<int, 5>::extent == 5);

  // a span with a static extent doesn't store its size
  static_assert(sizeof(rsl::span<int, 5>) == sizeof(int*));
  static_assert(sizeof(rsl::span<int>) > sizeof(int*));

  // spans are cheap to copy
  static_assert(rsl::is_trivially_copyable_v<rsl::span<int>>);
  static_assert(rsl::is_trivially_copyable_v<rsl::span<int, 5>>);
}

TEST_CASE("span element access")
{
  int arr[] = {1, 2, 3, 4, 5};
  rsl::span<int> s(arr);

  CHECK(s[0] == 1);
  CHECK(s[4] == 5);
  CHECK(s.at(2) == 3);
  CHECK(s.front() == 1);
  CHECK(s.back() == 5);
  CHECK(s.data() == arr);

  // a span is a view, modifying through it modifies the original
  s[0] = 10;
  CHECK(arr[0] == 10);
  s.front() = 11;
  CHECK(arr[0] == 11);
  s.back() = 50;
  CHECK(arr[4] == 50);
  s.at(1) = 20;
  CHECK(arr[1] == 20);

  // a const span still gives mutable access to its elements
  const rsl::span<int> const_s = s;
  const_s[2] = 30;
  CHECK(arr[2] == 30);

  // a span of const elements doesn't
  rsl::span<const int> const_elems = s;
  static_assert(rsl::is_same_v<decltype(const_elems[0]), const int&>);
  CHECK(const_elems[2] == 30);
}

TEST_CASE("span size")
{
  int arr[] = {1, 2, 3, 4};
  rsl::span<int> s(arr);
  CHECK(s.size() == 4);
  CHECK(s.size_bytes() == 4 * sizeof(int));
  CHECK(!s.empty());

  rsl::span<int> empty;
  CHECK(empty.size_bytes() == 0);
  CHECK(empty.empty());

  rsl::span<int> zero_count(arr, 0);
  CHECK(zero_count.empty());

  rsl::span<int, 4> fixed(arr);
  CHECK(fixed.size() == 4);
  CHECK(fixed.size_bytes() == 4 * sizeof(int));
}

TEST_CASE("span iteration")
{
  int arr[] = {1, 2, 3, 4, 5};
  rsl::span<int> s(arr);

  // range based for
  int expected = 1;
  for(int x : s)
  {
    CHECK(x == expected);
    ++expected;
  }
  CHECK(expected == 6);

  // iterators
  CHECK(s.end() - s.begin() == 5);
  CHECK(*s.begin() == 1);
  CHECK(*(s.end() - 1) == 5);
  CHECK(s.cbegin() == s.begin());
  CHECK(s.cend() == s.end());

  // modify through iterators
  for(auto it = s.begin(); it != s.end(); ++it)
  {
    *it *= 2;
  }
  CHECK(arr[0] == 2);
  CHECK(arr[4] == 10);

  // reverse iteration
  expected = 10;
  for(auto it = s.rbegin(); it != s.rend(); ++it)
  {
    CHECK(*it == expected);
    expected -= 2;
  }
  CHECK(expected == 0);

  expected = 10;
  for(auto it = s.crbegin(); it != s.crend(); ++it)
  {
    CHECK(*it == expected);
    expected -= 2;
  }
  CHECK(expected == 0);

  // empty span
  rsl::span<int> empty;
  CHECK(empty.begin() == empty.end());
  CHECK(empty.rbegin() == empty.rend());
}

TEST_CASE("span subviews")
{
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
  rsl::span<int> s(arr);

  // first
  {
    auto f = s.first<3>();
    static_assert(rsl::is_same_v<decltype(f), rsl::span<int, 3>>);
    CHECK(f.data() == arr);
    CHECK(f.size() == 3);
    CHECK(f[2] == 2);

    auto f2 = s.first(5);
    static_assert(rsl::is_same_v<decltype(f2), rsl::span<int>>);
    CHECK(f2.size() == 5);
    CHECK(f2.back() == 4);

    CHECK(s.first(0).empty());
    CHECK(s.first(8).size() == 8);
  }

  // last
  {
    auto l = s.last<3>();
    static_assert(rsl::is_same_v<decltype(l), rsl::span<int, 3>>);
    CHECK(l.data() == arr + 5);
    CHECK(l[0] == 5);
    CHECK(l.back() == 7);

    auto l2 = s.last(2);
    CHECK(l2.size() == 2);
    CHECK(l2.front() == 6);

    CHECK(s.last(0).empty());
    CHECK(s.last(8).data() == arr);
  }

  // subspan with template arguments
  {
    auto sub = s.subspan<2, 3>();
    static_assert(rsl::is_same_v<decltype(sub), rsl::span<int, 3>>);
    CHECK(sub.data() == arr + 2);
    CHECK(sub.size() == 3);
    CHECK(sub[0] == 2);
    CHECK(sub.back() == 4);

    // without a count, the subspan goes till the end
    auto rest = s.subspan<5>();
    static_assert(rsl::is_same_v<decltype(rest), rsl::span<int>>);
    CHECK(rest.size() == 3);
    CHECK(rest.front() == 5);

    // a span with a static extent results in a static extent
    rsl::span<int, 8> fixed(arr);
    auto fixed_rest = fixed.subspan<5>();
    static_assert(rsl::is_same_v<decltype(fixed_rest), rsl::span<int, 3>>);
    CHECK(fixed_rest.front() == 5);

    auto fixed_first = fixed.first<2>();
    CHECK(fixed_first.back() == 1);
    auto fixed_last = fixed.last<2>();
    CHECK(fixed_last.front() == 6);
  }

  // subspan with runtime arguments
  {
    auto sub = s.subspan(1, 4);
    static_assert(rsl::is_same_v<decltype(sub), rsl::span<int>>);
    CHECK(sub.data() == arr + 1);
    CHECK(sub.size() == 4);
    CHECK(sub.back() == 4);

    auto rest = s.subspan(6);
    CHECK(rest.size() == 2);
    CHECK(rest[0] == 6);

    CHECK(s.subspan(8).empty());
    CHECK(s.subspan(0).size() == 8);
    CHECK(s.subspan(3, 0).empty());
  }

  // subviews still point to the original data
  s.subspan(2, 2)[0] = 100;
  CHECK(arr[2] == 100);
}

TEST_CASE("span as bytes")
{
  rsl::uint32 arr[] = {0x01020304, 0x05060708};
  rsl::span<rsl::uint32> s(arr);

  auto bytes = rsl::as_bytes(s);
  static_assert(rsl::is_same_v<decltype(bytes), rsl::span<const rsl::byte>>);
  CHECK(bytes.size() == 8);
  CHECK(static_cast<const void*>(bytes.data()) == static_cast<const void*>(arr));
  CHECK(rsl::to_integer<rsl::uint8>(bytes[0]) == 0x04); // little endian

  auto writable = rsl::as_writable_bytes(s);
  static_assert(rsl::is_same_v<decltype(writable), rsl::span<rsl::byte>>);
  writable[0] = rsl::byte {0xFF};
  CHECK(arr[0] == 0x010203FF);

  // static extents are preserved
  rsl::span<rsl::uint32, 2> fixed(arr);
  auto fixed_bytes = rsl::as_bytes(fixed);
  static_assert(rsl::is_same_v<decltype(fixed_bytes), rsl::span<const rsl::byte, 8>>);
  CHECK(fixed_bytes.size() == 8);

  // const elements can't be written to
  rsl::span<const rsl::uint32> const_s = s;
  CHECK(rsl::as_bytes(const_s).size() == 8);
}

namespace span_test
{
  int sum(rsl::span<const int> values)
  {
    int res = 0;
    for(int v : values)
    {
      res += v;
    }
    return res;
  }
} // namespace span_test

TEST_CASE("span as function argument")
{
  // implicit conversions make spans convenient function arguments
  int arr[]                 = {1, 2, 3};
  rsl::array<int, 2> rsl_arr = {4, 5};
  rsl::vector<int> vec       = {6, 7, 8, 9};

  CHECK(span_test::sum(arr) == 6);
  CHECK(span_test::sum(rsl_arr) == 9);
  CHECK(span_test::sum(vec) == 30);
  CHECK(span_test::sum(rsl::span<int>(vec).subspan(1, 2)) == 15);
  CHECK(span_test::sum({}) == 0);
}

// NOLINTEND
