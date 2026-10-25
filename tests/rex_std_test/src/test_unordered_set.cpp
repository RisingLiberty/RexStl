// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_unordered_set.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/unordered_set.h"

#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_rand.h"
#include "rex_std_test/test_rex_std.h"

namespace unordered_set_test
{
  using int_set = rsl::unordered_set<int>;

  void fill(int_set& set, int count)
  {
    for(int i = 0; i < count; ++i)
    {
      set.insert(i);
    }
  }
} // namespace unordered_set_test

TEST_CASE("unordered set construction")
{
  // unordered_set()
  {
    const unordered_set_test::int_set set;
    CHECK(set.empty());
    CHECK(set.size() == 0);
    CHECK(set.begin() == set.end());
    CHECK(set.load_factor() == 0.0f);
  }

  // copy construction
  {
    unordered_set_test::int_set set;
    unordered_set_test::fill(set, 10);

    unordered_set_test::int_set copy(set);
    CHECK(copy.size() == 10);
    CHECK(set.size() == 10);
    for(int i = 0; i < 10; ++i)
    {
      CHECK(copy.contains(i));
    }

    // the copy is independent
    copy.insert(100);
    CHECK(!set.contains(100));
  }

  // move construction
  {
    unordered_set_test::int_set set;
    unordered_set_test::fill(set, 10);

    unordered_set_test::int_set moved(rsl::move(set));
    CHECK(moved.size() == 10);
    for(int i = 0; i < 10; ++i)
    {
      CHECK(moved.contains(i));
    }
  }
}

TEST_CASE("unordered set assignment")
{
  unordered_set_test::int_set set;
  unordered_set_test::fill(set, 5);

  unordered_set_test::int_set copy;
  copy.insert(100);
  copy = set;
  CHECK(copy.size() == 5);
  CHECK(!copy.contains(100));
  CHECK(copy.contains(4));

  unordered_set_test::int_set source;
  unordered_set_test::fill(source, 5);
  unordered_set_test::int_set moved;
  moved.insert(200);
  moved = rsl::move(source);
  CHECK(moved.size() == 5);
  CHECK(!moved.contains(200));
  CHECK(moved.contains(4));
}

TEST_CASE("unordered set insertion")
{
  unordered_set_test::int_set set;

  // inserting a new element
  auto res = set.insert(1);
  CHECK(res.emplace_successful);
  CHECK(*res.inserted_element == 1);
  CHECK(set.size() == 1);

  // inserting a duplicate element
  res = set.insert(1);
  CHECK(!res.emplace_successful);
  CHECK(*res.inserted_element == 1);
  CHECK(set.size() == 1);

  // inserting an lvalue
  int x = 2;
  res   = set.insert(x);
  CHECK(res.emplace_successful);
  CHECK(set.size() == 2);

  // emplace
  auto emplace_res = set.emplace(3);
  CHECK(emplace_res.emplace_successful);
  CHECK(*emplace_res.inserted_element == 3);
  emplace_res = set.emplace(3);
  CHECK(!emplace_res.emplace_successful);
  CHECK(set.size() == 3);
}

TEST_CASE("unordered set lookup")
{
  unordered_set_test::int_set set;
  unordered_set_test::fill(set, 10);

  for(int i = 0; i < 10; ++i)
  {
    CHECK(set.contains(i));
    CHECK(set.count(i) == 1);
    CHECK(set.find(i) != set.end());
    CHECK(*set.find(i) == i);
  }

  CHECK(!set.contains(10));
  CHECK(!set.contains(-1));
  CHECK(set.count(10) == 0);
  CHECK(set.find(10) == set.end());
}

TEST_CASE("unordered set erase")
{
  unordered_set_test::int_set set;
  unordered_set_test::fill(set, 10);

  CHECK(set.erase(3) == 1);
  CHECK(set.size() == 9);
  CHECK(!set.contains(3));

  // erasing a missing element doesn't do anything
  CHECK(set.erase(3) == 0);
  CHECK(set.erase(100) == 0);
  CHECK(set.size() == 9);

  // other elements are untouched
  for(int i = 0; i < 10; ++i)
  {
    if(i != 3)
    {
      CHECK(set.contains(i));
    }
  }

  set.clear();
  CHECK(set.empty());
  CHECK(set.begin() == set.end());
  CHECK(!set.contains(0));

  // the set is usable after being cleared
  set.insert(5);
  CHECK(set.size() == 1);
  CHECK(set.contains(5));
}

TEST_CASE("unordered set iteration")
{
  unordered_set_test::int_set set;
  unordered_set_test::fill(set, 20);

  // every element is visited exactly once
  int visited[20] = {};
  card32 count    = 0;
  for(int x : set)
  {
    REQUIRE(x >= 0);
    REQUIRE(x < 20);
    ++visited[x];
    ++count;
  }
  CHECK(count == 20);
  for(int v : visited)
  {
    CHECK(v == 1);
  }

  // const iteration
  const unordered_set_test::int_set& const_set = set;
  count                                        = 0;
  for(auto it = const_set.cbegin(); it != const_set.cend(); ++it)
  {
    ++count;
  }
  CHECK(count == 20);
}

TEST_CASE("unordered set buckets")
{
  unordered_set_test::int_set set;
  set.rehash(50);
  CHECK(set.bucket_count() >= 50);

  unordered_set_test::fill(set, 100);
  CHECK(set.load_factor() <= set.get_max_load_factor());
  for(int i = 0; i < 100; ++i)
  {
    CHECK(set.contains(i));
  }

  // reserve makes room for the requested amount of elements
  unordered_set_test::int_set reserved;
  reserved.reserve(100);
  const card32 bucket_count = reserved.bucket_count();
  unordered_set_test::fill(reserved, 100);
  CHECK(reserved.bucket_count() == bucket_count);
}

TEST_CASE("unordered set swap and comparison")
{
  unordered_set_test::int_set set1;
  unordered_set_test::fill(set1, 3);
  unordered_set_test::int_set set2;
  set2.insert(100);

  set1.swap(set2);
  CHECK(set1.size() == 1);
  CHECK(set1.contains(100));
  CHECK(set2.size() == 3);
  CHECK(set2.contains(2));

  unordered_set_test::int_set set3;
  unordered_set_test::fill(set3, 3);
  CHECK(set2 == set3);
  CHECK(!(set1 == set3));
}

TEST_CASE("unordered set stress")
{
  rsl::test::rand rng(rsl::test::rand_seed());
  unordered_set_test::int_set set;

  card32 num_unique = 0;
  for(int i = 0; i < 2000; ++i)
  {
    if(set.insert(static_cast<int>(rng.rand_limit(1000))).emplace_successful)
    {
      ++num_unique;
    }
  }
  CHECK(set.size() == num_unique);

  card32 count = 0;
  for(int x : set)
  {
    (void)x;
    ++count;
  }
  CHECK(count == num_unique);
}

// NOLINTEND
