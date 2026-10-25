// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_sort.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/algorithm.h"
#include "rex_std/bonus/algorithm/comb_sort.h"
#include "rex_std/bonus/algorithm/get_partition.h"
#include "rex_std/functional.h"
#include "rex_std/vector.h"

#include "rex_std_test/test_rand.h"
#include "rex_std_test/test_rex_std.h"

namespace sort_test
{
  struct key_and_order
  {
    int key;
    int order;
  };

  rsl::vector<int> create_random_vector(rsl::test::rand& rng, int size, uint32 limit)
  {
    rsl::vector<int> vec;
    for(int i = 0; i < size; ++i)
    {
      vec.push_back(static_cast<int>(rng.rand_limit(limit)));
    }
    return vec;
  }
} // namespace sort_test

TEST_CASE("sort")
{
  // empty range
  {
    rsl::vector<int> vec;
    rsl::sort(vec.begin(), vec.end());
    CHECK(vec.empty());
  }

  // single element
  {
    rsl::vector<int> vec = {1};
    rsl::sort(vec.begin(), vec.end());
    CHECK(vec[0] == 1);
  }

  // two elements
  {
    rsl::vector<int> vec = {2, 1};
    rsl::sort(vec.begin(), vec.end());
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
  }

  // already sorted input
  {
    rsl::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    rsl::sort(vec.begin(), vec.end());
    CHECK(rsl::is_sorted(vec.begin(), vec.end()));
    CHECK(vec.front() == 1);
    CHECK(vec.back() == 10);
  }

  // reverse sorted input
  {
    rsl::vector<int> vec = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    rsl::sort(vec.begin(), vec.end());
    CHECK(rsl::is_sorted(vec.begin(), vec.end()));
    for(int i = 0; i < 10; ++i)
    {
      CHECK(vec[i] == i + 1);
    }
  }

  // input with duplicates
  {
    rsl::vector<int> vec = {5, 1, 5, 3, 1, 5, 3, 3, 1};
    rsl::sort(vec.begin(), vec.end());
    CHECK(rsl::is_sorted(vec.begin(), vec.end()));
    CHECK(rsl::count(vec.begin(), vec.end(), 1) == 3);
    CHECK(rsl::count(vec.begin(), vec.end(), 3) == 3);
    CHECK(rsl::count(vec.begin(), vec.end(), 5) == 3);
  }

  // negative numbers
  {
    rsl::vector<int> vec = {-3, 7, -100, 0, 42, -1};
    rsl::sort(vec.begin(), vec.end());
    CHECK(vec[0] == -100);
    CHECK(vec[1] == -3);
    CHECK(vec[2] == -1);
    CHECK(vec[3] == 0);
    CHECK(vec[4] == 7);
    CHECK(vec[5] == 42);
  }

  // custom comparison
  {
    rsl::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    rsl::sort(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(rsl::is_sorted(vec.begin(), vec.end(), rsl::greater<int>()));
    CHECK(vec.front() == 9);
    CHECK(vec.back() == 1);
  }

  // sorting a sub range leaves the rest untouched
  {
    rsl::vector<int> vec = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    rsl::sort(vec.begin() + 2, vec.begin() + 6);
    CHECK(vec[0] == 9);
    CHECK(vec[1] == 8);
    CHECK(vec[2] == 4);
    CHECK(vec[3] == 5);
    CHECK(vec[4] == 6);
    CHECK(vec[5] == 7);
    CHECK(vec[6] == 3);
    CHECK(vec[7] == 2);
    CHECK(vec[8] == 1);
  }

  // raw arrays
  {
    float arr[] = {3.5f, -1.0f, 2.25f, 0.0f};
    rsl::sort(arr, arr + 4);
    CHECK(arr[0] == -1.0f);
    CHECK(arr[1] == 0.0f);
    CHECK(arr[2] == 2.25f);
    CHECK(arr[3] == 3.5f);
  }

  // large random inputs (larger than the quick sort insertion sort threshold)
  {
    rsl::test::rand rng(rsl::test::rand_seed());
    for(int test = 0; test < 25; ++test)
    {
      rsl::vector<int> vec = sort_test::create_random_vector(rng, 1000, 500);
      rsl::sort(vec.begin(), vec.end());
      CHECK(rsl::is_sorted(vec.begin(), vec.end()));
    }
  }
}

TEST_CASE("is sorted")
{
  rsl::vector<int> vec;
  CHECK(rsl::is_sorted(vec.begin(), vec.end()));

  vec = {1};
  CHECK(rsl::is_sorted(vec.begin(), vec.end()));

  vec = {1, 2, 2, 3};
  CHECK(rsl::is_sorted(vec.begin(), vec.end()));
  CHECK(!rsl::is_sorted(vec.begin(), vec.end(), rsl::greater<int>()));

  vec = {3, 2, 2, 1};
  CHECK(!rsl::is_sorted(vec.begin(), vec.end()));
  CHECK(rsl::is_sorted(vec.begin(), vec.end(), rsl::greater<int>()));

  vec = {1, 2, 3, 0};
  CHECK(!rsl::is_sorted(vec.begin(), vec.end()));
  CHECK(rsl::is_sorted(vec.begin(), vec.end() - 1));
}

TEST_CASE("quick sort")
{
  // empty range
  {
    rsl::vector<int> vec;
    rsl::quick_sort(vec.begin(), vec.end());
    CHECK(vec.empty());
  }

  // small range
  {
    rsl::vector<int> vec = {3, 2, 1};
    rsl::quick_sort(vec.begin(), vec.end());
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
  }

  // custom comparison
  {
    rsl::vector<int> vec = {1, 2, 3, 4, 5};
    rsl::quick_sort(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(vec[0] == 5);
    CHECK(vec[1] == 4);
    CHECK(vec[2] == 3);
    CHECK(vec[3] == 2);
    CHECK(vec[4] == 1);
  }

  // large random ranges
  {
    rsl::test::rand rng(rsl::test::rand_seed());
    for(int test = 0; test < 25; ++test)
    {
      rsl::vector<int> vec = sort_test::create_random_vector(rng, 500, 100);
      rsl::quick_sort(vec.begin(), vec.end());
      CHECK(rsl::is_sorted(vec.begin(), vec.end()));

      rsl::quick_sort(vec.begin(), vec.end(), rsl::greater<int>());
      CHECK(rsl::is_sorted(vec.begin(), vec.end(), rsl::greater<int>()));
    }
  }

  // all equal elements
  {
    rsl::vector<int> vec(100_size, 7);
    rsl::quick_sort(vec.begin(), vec.end());
    CHECK(vec.size() == 100);
    CHECK(rsl::count(vec.begin(), vec.end(), 7) == 100);
  }
}

TEST_CASE("comb sort")
{
  // empty range
  {
    rsl::vector<int> vec;
    rsl::comb_sort(vec.begin(), vec.end());
    CHECK(vec.empty());
  }

  // single element
  {
    rsl::vector<int> vec = {5};
    rsl::comb_sort(vec.begin(), vec.end());
    CHECK(vec[0] == 5);
  }

  // small range
  {
    rsl::vector<int> vec = {9, 3, 7, 1};
    rsl::comb_sort(vec.begin(), vec.end());
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 3);
    CHECK(vec[2] == 7);
    CHECK(vec[3] == 9);
  }

  // custom comparison
  {
    rsl::vector<int> vec = {9, 3, 7, 1};
    rsl::comb_sort(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(vec[0] == 9);
    CHECK(vec[1] == 7);
    CHECK(vec[2] == 3);
    CHECK(vec[3] == 1);
  }

  // large random ranges
  {
    rsl::test::rand rng(rsl::test::rand_seed());
    for(int test = 0; test < 10; ++test)
    {
      rsl::vector<int> vec = sort_test::create_random_vector(rng, 300, 1000);
      rsl::comb_sort(vec.begin(), vec.end());
      CHECK(rsl::is_sorted(vec.begin(), vec.end()));
    }
  }
}

TEST_CASE("partition")
{
  auto is_even = [](int x) { return x % 2 == 0; };

  // all elements satisfying the predicate come first
  {
    rsl::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it              = rsl::partition(vec.begin(), vec.end(), is_even);

    CHECK(it - vec.begin() == 4);
    for(auto i = vec.begin(); i != it; ++i)
    {
      CHECK(is_even(*i));
    }
    for(auto i = it; i != vec.end(); ++i)
    {
      CHECK(!is_even(*i));
    }
  }

  // no element satisfies the predicate
  {
    rsl::vector<int> vec = {1, 3, 5};
    auto it              = rsl::partition(vec.begin(), vec.end(), is_even);
    CHECK(it == vec.begin());
  }

  // every element satisfies the predicate
  {
    rsl::vector<int> vec = {2, 4, 6};
    auto it              = rsl::partition(vec.begin(), vec.end(), is_even);
    CHECK(it == vec.end());
  }

  // empty range
  {
    rsl::vector<int> vec;
    auto it = rsl::partition(vec.begin(), vec.end(), is_even);
    CHECK(it == vec.end());
  }
}

TEST_CASE("get partition")
{
  // every element before the returned iterator is not greater than the pivot
  // every element after (and including) the returned iterator is not less than the pivot
  rsl::vector<int> vec = {7, 2, 9, 4, 5, 1, 8, 3, 6};
  const int pivot      = 5;
  auto it              = rsl::get_partition(vec.begin(), vec.end(), pivot);

  for(auto i = vec.begin(); i != it; ++i)
  {
    CHECK(*i <= pivot);
  }
  for(auto i = it; i != vec.end(); ++i)
  {
    CHECK(*i >= pivot);
  }

  // with a custom comparison, the order flips
  rsl::vector<int> vec2 = {7, 2, 9, 4, 5, 1, 8, 3, 6};
  auto it2              = rsl::get_partition(vec2.begin(), vec2.end(), pivot, rsl::greater<int>());

  for(auto i = vec2.begin(); i != it2; ++i)
  {
    CHECK(*i >= pivot);
  }
  for(auto i = it2; i != vec2.end(); ++i)
  {
    CHECK(*i <= pivot);
  }
}

TEST_CASE("median")
{
  CHECK(rsl::median(1, 2, 3) == 2);
  CHECK(rsl::median(1, 3, 2) == 2);
  CHECK(rsl::median(2, 1, 3) == 2);
  CHECK(rsl::median(2, 3, 1) == 2);
  CHECK(rsl::median(3, 1, 2) == 2);
  CHECK(rsl::median(3, 2, 1) == 2);
  CHECK(rsl::median(5, 5, 5) == 5);
  CHECK(rsl::median(5, 5, 1) == 5);
  CHECK(rsl::median(1, 5, 5) == 5);

  const int a = 10;
  const int b = 30;
  const int c = 20;
  CHECK(rsl::median(a, b, c) == 20);
  CHECK(&rsl::median(a, b, c) == &c);

  CHECK(rsl::median(1, 2, 3, rsl::greater<int>()) == 2);
  CHECK(rsl::median(3, 1, 2, rsl::greater<int>()) == 2);
}

TEST_CASE("binary search it")
{
  rsl::vector<int> vec = {1, 3, 5, 7, 9, 11};

  CHECK(rsl::binary_search_it(vec.begin(), vec.end(), 1) == vec.begin());
  CHECK(rsl::binary_search_it(vec.begin(), vec.end(), 7) == vec.begin() + 3);
  CHECK(rsl::binary_search_it(vec.begin(), vec.end(), 11) == vec.begin() + 5);
  CHECK(rsl::binary_search_it(vec.begin(), vec.end(), 0) == vec.end());
  CHECK(rsl::binary_search_it(vec.begin(), vec.end(), 4) == vec.end());
  CHECK(rsl::binary_search_it(vec.begin(), vec.end(), 12) == vec.end());

  rsl::vector<int> desc = {11, 9, 7, 5, 3, 1};
  CHECK(rsl::binary_search_it(desc.begin(), desc.end(), 7, rsl::greater<int>()) == desc.begin() + 2);
  CHECK(rsl::binary_search_it(desc.begin(), desc.end(), 8, rsl::greater<int>()) == desc.end());

  rsl::vector<int> empty;
  CHECK(rsl::binary_search_it(empty.begin(), empty.end(), 1) == empty.end());
}

// NOLINTEND
