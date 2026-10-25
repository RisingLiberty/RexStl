// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_heap.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/algorithm.h"
#include "rex_std/functional.h"
#include "rex_std/vector.h"
#include "rex_std/memory.h"

#include "rex_std_test/test_rand.h"
#include "rex_std_test/test_rex_std.h"

namespace heap_test
{
  // rsl::is_heap is an alias to std::is_heap, which is only available when RSL_ENABLE_STD_ALIAS is defined.
  // so we verify the heap property ourselves
  template <typename RandomAccessIterator, typename Compare>
  bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
  {
    const auto size = last - first;
    for(decltype(last - first) child = 1; child < size; ++child)
    {
      const auto parent = (child - 1) / 2;
      if(compare(*(first + parent), *(first + child)))
      {
        return false;
      }
    }

    return true;
  }

  template <typename RandomAccessIterator>
  bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
  {
    using value_type = typename rsl::iterator_traits<RandomAccessIterator>::value_type;
    return is_heap(first, last, rsl::less<value_type>());
  }
} // namespace heap_test

TEST_CASE("make heap")
{
  // empty and single element ranges are always heaps
  {
    rsl::vector<int> vec;
    rsl::make_heap(vec.begin(), vec.end());
    CHECK(vec.empty());
    CHECK(heap_test::is_heap(vec.begin(), vec.end()));
  }
  {
    rsl::vector<int> vec = {1};
    rsl::make_heap(vec.begin(), vec.end());
    CHECK(vec.size() == 1);
    CHECK(vec[0] == 1);
  }

  // max heap by default
  {
    rsl::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    rsl::make_heap(vec.begin(), vec.end());
    CHECK(heap_test::is_heap(vec.begin(), vec.end()));
    CHECK(vec.front() == 9);
    CHECK(vec.size() == 10);
  }

  // already sorted ascending input
  {
    rsl::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    rsl::make_heap(vec.begin(), vec.end());
    CHECK(heap_test::is_heap(vec.begin(), vec.end()));
    CHECK(vec.front() == 8);
  }

  // all values equal
  {
    rsl::vector<int> vec = {7, 7, 7, 7, 7};
    rsl::make_heap(vec.begin(), vec.end());
    CHECK(heap_test::is_heap(vec.begin(), vec.end()));
    CHECK(vec.front() == 7);
  }

  // min heap with custom comparison
  {
    rsl::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    rsl::make_heap(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(heap_test::is_heap(vec.begin(), vec.end(), rsl::greater<int>()));
    CHECK(vec.front() == 1);
  }

  // works on a raw array
  {
    int arr[] = {5, 2, 8, 1, 9, 3};
    rsl::make_heap(arr, arr + 6);
    CHECK(heap_test::is_heap(arr, arr + 6));
    CHECK(arr[0] == 9);
  }

  // works on random input
  {
    rsl::test::rand rng(rsl::test::rand_seed());
    for(int test = 0; test < 25; ++test)
    {
      rsl::vector<int> vec;
      for(int i = 0; i < 100; ++i)
      {
        vec.push_back(static_cast<int>(rng.rand_limit(1000)));
      }

      rsl::make_heap(vec.begin(), vec.end());
      CHECK(heap_test::is_heap(vec.begin(), vec.end()));
    }
  }
}

TEST_CASE("pop heap")
{
  // pop moves the largest element to the back
  {
    rsl::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    rsl::make_heap(vec.begin(), vec.end());

    rsl::pop_heap(vec.begin(), vec.end());
    CHECK(vec.back() == 9);
    CHECK(heap_test::is_heap(vec.begin(), vec.end() - 1));
    vec.pop_back();

    rsl::pop_heap(vec.begin(), vec.end());
    CHECK(vec.back() == 6);
    CHECK(heap_test::is_heap(vec.begin(), vec.end() - 1));
    vec.pop_back();

    rsl::pop_heap(vec.begin(), vec.end());
    CHECK(vec.back() == 5);
    CHECK(heap_test::is_heap(vec.begin(), vec.end() - 1));
  }

  // popping a single element heap
  {
    rsl::vector<int> vec = {42};
    rsl::pop_heap(vec.begin(), vec.end());
    CHECK(vec.size() == 1);
    CHECK(vec[0] == 42);
  }

  // pop with custom comparison (min heap)
  {
    rsl::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    rsl::make_heap(vec.begin(), vec.end(), rsl::greater<int>());

    rsl::pop_heap(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(vec.back() == 1);
    vec.pop_back();

    rsl::pop_heap(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(vec.back() == 1);
    vec.pop_back();

    rsl::pop_heap(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(vec.back() == 2);
    CHECK(heap_test::is_heap(vec.begin(), vec.end() - 1, rsl::greater<int>()));
  }

  // popping everything yields a descending sequence
  {
    rsl::vector<int> vec = {10, 20, 5, 15, 30, 25, 0};
    rsl::make_heap(vec.begin(), vec.end());

    rsl::vector<int> popped;
    while(!vec.empty())
    {
      rsl::pop_heap(vec.begin(), vec.end());
      popped.push_back(vec.back());
      vec.pop_back();
    }

    CHECK(popped.size() == 7);
    CHECK(rsl::is_sorted(popped.begin(), popped.end(), rsl::greater<int>()));
    CHECK(popped.front() == 30);
    CHECK(popped.back() == 0);
  }

  // pop heap with move only types
  {
    rsl::vector<rsl::unique_ptr<int>> vec;
    vec.emplace_back(new int(3));
    vec.emplace_back(new int(10));
    vec.emplace_back(new int(1));
    vec.emplace_back(new int(7));

    auto cmp = [](const rsl::unique_ptr<int>& lhs, const rsl::unique_ptr<int>& rhs) { return *lhs < *rhs; };
    rsl::make_heap(vec.begin(), vec.end(), cmp);
    CHECK(*vec.front() == 10);

    rsl::pop_heap(vec.begin(), vec.end(), cmp);
    CHECK(*vec.back() == 10);
    CHECK(*vec.front() == 7);
  }
}

TEST_CASE("sort heap")
{
  // sorts ascending by default
  {
    rsl::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    rsl::make_heap(vec.begin(), vec.end());
    rsl::sort_heap(vec.begin(), vec.end());
    CHECK(rsl::is_sorted(vec.begin(), vec.end()));
    CHECK(vec.front() == 1);
    CHECK(vec.back() == 9);
    CHECK(vec.size() == 11);
  }

  // sorting a heap of 0, 1 and 2 elements
  {
    rsl::vector<int> vec;
    rsl::sort_heap(vec.begin(), vec.end());
    CHECK(vec.empty());

    vec.push_back(1);
    rsl::sort_heap(vec.begin(), vec.end());
    CHECK(vec[0] == 1);

    vec.push_back(2);
    rsl::make_heap(vec.begin(), vec.end());
    rsl::sort_heap(vec.begin(), vec.end());
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
  }

  // sorts descending with a min heap
  {
    rsl::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    rsl::make_heap(vec.begin(), vec.end(), rsl::greater<int>());
    rsl::sort_heap(vec.begin(), vec.end(), rsl::greater<int>());
    CHECK(rsl::is_sorted(vec.begin(), vec.end(), rsl::greater<int>()));
    CHECK(vec.front() == 9);
    CHECK(vec.back() == 1);
  }

  // random input
  {
    rsl::test::rand rng(rsl::test::rand_seed());
    for(int test = 0; test < 25; ++test)
    {
      rsl::vector<int> vec;
      for(int i = 0; i < 100; ++i)
      {
        vec.push_back(static_cast<int>(rng.rand_limit(1000)));
      }

      rsl::make_heap(vec.begin(), vec.end());
      rsl::sort_heap(vec.begin(), vec.end());
      CHECK(rsl::is_sorted(vec.begin(), vec.end()));
    }
  }
}

TEST_CASE("partial sort")
{
  // sorts the first 'middle' elements, the rest is unspecified
  {
    rsl::vector<int> vec = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    rsl::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
    CHECK(vec[0] == 0);
    CHECK(vec[1] == 1);
    CHECK(vec[2] == 2);
    CHECK(vec.size() == 10);
  }

  // middle == last sorts the whole range
  {
    rsl::vector<int> vec = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    rsl::partial_sort(vec.begin(), vec.end(), vec.end());
    CHECK(rsl::is_sorted(vec.begin(), vec.end()));
  }

  // custom comparison
  {
    rsl::vector<int> vec = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    rsl::partial_sort(vec.begin(), vec.begin() + 4, vec.end(), rsl::greater<int>());
    CHECK(vec[0] == 9);
    CHECK(vec[1] == 8);
    CHECK(vec[2] == 7);
    CHECK(vec[3] == 6);
  }

  // the remaining elements are still all present
  {
    rsl::vector<int> vec = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    rsl::partial_sort(vec.begin(), vec.begin() + 5, vec.end());
    for(int i = 0; i < 10; ++i)
    {
      CHECK(rsl::find(vec.begin(), vec.end(), i) != vec.end());
    }
  }
}

// NOLINTEND
