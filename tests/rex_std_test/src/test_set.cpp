// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_set.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/functional.h"
#include "rex_std/set.h"

#include "rex_std_test/test_rand.h"
#include "rex_std_test/test_rex_std.h"

namespace set_test
{
  template <typename Set>
  bool contains_in_order(const Set& set, rsl::initializer_list<int> values)
  {
    auto it = set.begin();
    for(int value : values)
    {
      if(it == set.end() || *it != value)
      {
        return false;
      }
      ++it;
    }
    return it == set.end();
  }
} // namespace set_test

TEST_CASE("set construction")
{
  // set()
  {
    const rsl::set<int> set;
    CHECK(set.empty());
    CHECK(set.size() == 0);
    CHECK(set.begin() == set.end());
  }

  // set(first, last)
  {
    int arr[] = {3, 1, 2, 3, 1};
    rsl::set<int> set(arr, arr + 5);
    CHECK(set.size() == 3);
    CHECK(set_test::contains_in_order(set, {1, 2, 3}));
  }

  // set(const set&)
  {
    int arr[] = {3, 1, 2};
    rsl::set<int> set(arr, arr + 3);
    rsl::set<int> copy(set);
    CHECK(copy.size() == 3);
    CHECK(set.size() == 3);
    CHECK(set_test::contains_in_order(copy, {1, 2, 3}));
  }

  // set(set&&)
  {
    int arr[] = {3, 1, 2};
    rsl::set<int> set(arr, arr + 3);
    rsl::set<int> moved(rsl::move(set));
    CHECK(moved.size() == 3);
    CHECK(set.empty());
    CHECK(set_test::contains_in_order(moved, {1, 2, 3}));
  }

  // set(compare)
  {
    rsl::set<int, rsl::greater<int>> set(rsl::greater<int> {});
    set.emplace(1);
    set.emplace(3);
    set.emplace(2);
    CHECK(set_test::contains_in_order(set, {3, 2, 1}));
  }
}

TEST_CASE("set modifiers")
{
  // emplace
  {
    rsl::set<int> set;
    auto res = set.emplace(5);
    CHECK(res.emplace_successful);
    CHECK(*res.inserted_element == 5);

    auto res2 = set.emplace(5);
    CHECK(!res2.emplace_successful);
    CHECK(*res2.inserted_element == 5);
    CHECK(set.size() == 1);
  }

  // insert an lvalue
  {
    rsl::set<int> set;
    int x    = 3;
    auto res = set.insert(x);
    CHECK(res.emplace_successful);
    CHECK(set.contains(3));

    res = set.insert(x);
    CHECK(!res.emplace_successful);
    CHECK(set.size() == 1);
  }

  // erase by iterator
  {
    int arr[] = {1, 2, 3, 4};
    rsl::set<int> set(arr, arr + 4);

    auto it = set.erase(set.begin());
    CHECK(*it == 2);
    CHECK(set.size() == 3);
    CHECK(set_test::contains_in_order(set, {2, 3, 4}));

    it = set.erase(set.find(3));
    CHECK(*it == 4);
    CHECK(set_test::contains_in_order(set, {2, 4}));
  }

  // erase by key
  {
    int arr[] = {1, 2, 3, 4};
    rsl::set<int> set(arr, arr + 4);

    CHECK(set.erase(2) == 1);
    CHECK(set.size() == 3);
    CHECK(!set.contains(2));
  }

  // clear
  {
    int arr[] = {1, 2, 3, 4};
    rsl::set<int> set(arr, arr + 4);
    set.clear();
    CHECK(set.empty());
    CHECK(set.begin() == set.end());
    set.emplace(1);
    CHECK(set.size() == 1);
  }

  // swap
  {
    int arr[] = {1, 2, 3};
    rsl::set<int> set1(arr, arr + 3);
    rsl::set<int> set2;
    set2.emplace(10);

    set1.swap(set2);
    CHECK(set_test::contains_in_order(set1, {10}));
    CHECK(set_test::contains_in_order(set2, {1, 2, 3}));
  }
}

TEST_CASE("set lookup")
{
  int arr[] = {10, 20, 30};
  rsl::set<int> set(arr, arr + 3);

  CHECK(set.count(10) == 1);
  CHECK(set.count(11) == 0);

  CHECK(set.contains(20));
  CHECK(!set.contains(25));

  CHECK(set.find(30) != set.end());
  CHECK(*set.find(30) == 30);
  CHECK(set.find(31) == set.end());

  CHECK(*set.lower_bound(15) == 20);
  CHECK(*set.lower_bound(20) == 20);
  CHECK(set.lower_bound(31) == set.end());

  CHECK(*set.upper_bound(15) == 20);
  CHECK(*set.upper_bound(20) == 30);
  CHECK(set.upper_bound(30) == set.end());
}

TEST_CASE("set iterators")
{
  int arr[] = {5, 3, 1, 4, 2};
  rsl::set<int> set(arr, arr + 5);

  int expected = 1;
  for(int x : set)
  {
    CHECK(x == expected);
    ++expected;
  }
  CHECK(expected == 6);

  expected = 5;
  for(auto it = set.rbegin(); it != set.rend(); ++it)
  {
    CHECK(*it == expected);
    --expected;
  }
  CHECK(expected == 0);
}

TEST_CASE("set stress")
{
  rsl::test::rand rng(rsl::test::rand_seed());
  rsl::set<int> set;

  int num_unique = 0;
  for(int i = 0; i < 1000; ++i)
  {
    if(set.emplace(static_cast<int>(rng.rand_limit(300))).emplace_successful)
    {
      ++num_unique;
    }
  }

  CHECK(set.size() == num_unique);

  // all elements are unique and sorted
  auto it   = set.begin();
  auto prev = it;
  ++it;
  for(; it != set.end(); ++it, ++prev)
  {
    CHECK(*prev < *it);
  }
}

// NOLINTEND
