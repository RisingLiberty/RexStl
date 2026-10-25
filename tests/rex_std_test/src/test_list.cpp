// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_list.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/list.h"

#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_object.h"

namespace list_test
{
  // rsl::list::size() doesn't compile at the moment as cend() can't create a const_iterator
  // from a const list node, so we count the elements ourselves
  template <typename List>
  card32 num_elements(List& list)
  {
    card32 count = 0;
    for(auto it = list.begin(); it != list.end(); ++it)
    {
      ++count;
    }
    return count;
  }

  template <typename List>
  bool contains_in_order(List& list, rsl::initializer_list<int> values)
  {
    auto it = list.begin();
    for(int value : values)
    {
      if(it == list.end() || *it != value)
      {
        return false;
      }
      ++it;
    }
    return it == list.end();
  }
} // namespace list_test

TEST_CASE("list construction")
{
  // list()
  {
    rsl::list<int> list;
    CHECK(list.begin() == list.end());
    CHECK(list_test::num_elements(list) == 0);
  }

  // list(initializer_list)
  {
    rsl::list<int> list = {1, 2, 3, 4};
    CHECK(list_test::num_elements(list) == 4);
    CHECK(list_test::contains_in_order(list, {1, 2, 3, 4}));
    CHECK(list.front() == 1);
    CHECK(list.back() == 4);
  }

  // list(first, last)
  {
    int arr[]           = {5, 6, 7};
    rsl::list<int> list(arr, arr + 3);
    CHECK(list_test::num_elements(list) == 3);
    CHECK(list_test::contains_in_order(list, {5, 6, 7}));
  }

  // list(first, last) with an empty range
  {
    int arr[]           = {5};
    rsl::list<int> list(arr, arr);
    CHECK(list.begin() == list.end());
  }
}

TEST_CASE("list element access")
{
  rsl::list<int> list = {10, 20, 30};

  CHECK(list.front() == 10);
  CHECK(list.back() == 30);

  list.front() = 11;
  list.back()  = 31;
  CHECK(list.front() == 11);
  CHECK(list.back() == 31);

  const rsl::list<int>& const_list = list;
  CHECK(const_list.front() == 11);
}

TEST_CASE("list iterators")
{
  rsl::list<int> list = {1, 2, 3, 4, 5};

  // forward iteration
  {
    int expected = 1;
    for(auto it = list.begin(); it != list.end(); ++it)
    {
      CHECK(*it == expected);
      ++expected;
    }
    CHECK(expected == 6);
  }

  // range based for loop
  {
    int sum = 0;
    for(int x : list)
    {
      sum += x;
    }
    CHECK(sum == 15);
  }

  // const iteration
  {
    const rsl::list<int>& const_list = list;
    int expected                     = 1;
    for(const int& x : const_list)
    {
      CHECK(x == expected);
      ++expected;
    }
    CHECK(expected == 6);
  }

  // backward iteration
  {
    int expected = 5;
    auto it      = list.end();
    while(it != list.begin())
    {
      --it;
      CHECK(*it == expected);
      --expected;
    }
    CHECK(expected == 0);
  }

  // reverse iterators
  {
    int expected = 5;
    for(auto it = list.rbegin(); it != list.rend(); ++it)
    {
      CHECK(*it == expected);
      --expected;
    }
    CHECK(expected == 0);
  }

  // post increment and decrement
  {
    auto it   = list.begin();
    auto prev = it++;
    CHECK(*prev == 1);
    CHECK(*it == 2);

    prev = it--;
    CHECK(*prev == 2);
    CHECK(*it == 1);
  }

  // modify through an iterator
  {
    for(int& x : list)
    {
      x *= 2;
    }
    CHECK(list_test::contains_in_order(list, {2, 4, 6, 8, 10}));
  }

  // empty list
  {
    rsl::list<int> empty;
    CHECK(empty.begin() == empty.end());
    CHECK(empty.rbegin() == empty.rend());
  }
}

TEST_CASE("list push and emplace")
{
  // push back
  {
    rsl::list<int> list;
    list.push_back(1);
    CHECK(list.front() == 1);
    CHECK(list.back() == 1);
    list.push_back(2);
    list.push_back(3);
    CHECK(list_test::contains_in_order(list, {1, 2, 3}));
  }

  // push front
  {
    rsl::list<int> list;
    list.push_front(1);
    CHECK(list.front() == 1);
    CHECK(list.back() == 1);
    list.push_front(2);
    list.push_front(3);
    CHECK(list_test::contains_in_order(list, {3, 2, 1}));
  }

  // mixing push front and push back
  {
    rsl::list<int> list;
    list.push_back(2);
    list.push_front(1);
    list.push_back(3);
    list.push_front(0);
    CHECK(list_test::contains_in_order(list, {0, 1, 2, 3}));
  }

  // emplace back and front
  {
    rsl::list<rsl::test::test_object> list;
    list.emplace_back(1, 2, 3);
    list.emplace_front(4);
    list.emplace_back();
    CHECK(list_test::num_elements(list) == 3);
    CHECK(list.front().x() == 4);
    CHECK(list.back().x() == 0);
  }

  // push back of rvalues
  {
    rsl::list<rsl::test::test_object> list;
    rsl::test::test_object obj(5);
    list.push_back(rsl::move(obj));
    list.push_front(rsl::test::test_object(6));
    CHECK(list.front().x() == 6);
    CHECK(list.back().x() == 5);
  }
}

TEST_CASE("list insert and emplace at position")
{
  // insert at the front
  {
    rsl::list<int> list = {2, 3};
    auto it             = list.insert(list.begin(), 1);
    CHECK(*it == 1);
    CHECK(it == list.begin());
    CHECK(list_test::contains_in_order(list, {1, 2, 3}));
  }

  // insert at the end
  {
    rsl::list<int> list = {1, 2};
    auto it             = list.insert(list.end(), 3);
    CHECK(*it == 3);
    CHECK(list_test::contains_in_order(list, {1, 2, 3}));
  }

  // insert in the middle
  {
    rsl::list<int> list = {1, 3};
    auto pos            = list.begin();
    ++pos;
    auto it = list.insert(pos, 2);
    CHECK(*it == 2);
    CHECK(list_test::contains_in_order(list, {1, 2, 3}));
  }

  // insert an rvalue
  {
    rsl::list<int> list;
    int x   = 4;
    auto it = list.insert(list.end(), rsl::move(x));
    CHECK(*it == 4);
    CHECK(list_test::num_elements(list) == 1);
  }

  // insert an initializer list
  {
    rsl::list<int> list = {1, 5};
    auto pos            = list.begin();
    ++pos;
    list.insert(pos, {2, 3, 4});
    CHECK(list_test::contains_in_order(list, {1, 2, 3, 4, 5}));
  }

  // emplace
  {
    rsl::list<rsl::test::test_object> list;
    auto it = list.emplace(list.end(), 1, 2, 3); // test_object(x, y, z) stores x + y + z
    CHECK(it->x() == 6);
    it = list.emplace(list.begin(), 0);
    CHECK(it->x() == 0);
    CHECK(list.front().x() == 0);
    CHECK(list.back().x() == 6);
  }
}

TEST_CASE("list pop")
{
  rsl::list<int> list = {1, 2, 3, 4};

  list.pop_back();
  CHECK(list_test::contains_in_order(list, {1, 2, 3}));

  list.pop_front();
  CHECK(list_test::contains_in_order(list, {2, 3}));

  list.pop_back();
  list.pop_front();
  CHECK(list.begin() == list.end());

  // the list should be fully usable after being emptied
  list.push_back(5);
  CHECK(list_test::contains_in_order(list, {5}));
}

TEST_CASE("list erase")
{
  // erase the first element
  {
    rsl::list<int> list = {1, 2, 3};
    auto it             = list.erase(list.begin());
    CHECK(it == list.begin());
    CHECK(list_test::contains_in_order(list, {2, 3}));
  }

  // erase the last element
  {
    rsl::list<int> list = {1, 2, 3};
    auto pos            = list.end();
    --pos;
    auto it = list.erase(pos);
    CHECK(it == list.end());
    CHECK(list_test::contains_in_order(list, {1, 2}));
  }

  // erase a middle element
  {
    rsl::list<int> list = {1, 2, 3};
    auto pos            = list.begin();
    ++pos;
    auto it      = list.erase(pos);
    auto expected = list.begin();
    ++expected;
    CHECK(it == expected);
    CHECK(list_test::contains_in_order(list, {1, 3}));
  }
}

TEST_CASE("list reverse")
{
  {
    rsl::list<int> list = {1, 2, 3, 4, 5};
    list.reverse();
    CHECK(list_test::contains_in_order(list, {5, 4, 3, 2, 1}));
    CHECK(list.front() == 5);
    CHECK(list.back() == 1);

    list.reverse();
    CHECK(list_test::contains_in_order(list, {1, 2, 3, 4, 5}));
  }

  // reversing an empty and a single element list
  {
    rsl::list<int> list;
    list.reverse();
    CHECK(list.begin() == list.end());

    list.push_back(1);
    list.reverse();
    CHECK(list_test::contains_in_order(list, {1}));
  }
}

TEST_CASE("list merge")
{
  rsl::list<int> list1 = {1, 3, 5, 7};
  rsl::list<int> list2 = {2, 4, 6, 8, 9};

  list1.merge(list2);
  CHECK(list_test::contains_in_order(list1, {1, 2, 3, 4, 5, 6, 7, 8, 9}));
  CHECK(list2.begin() == list2.end());
}

TEST_CASE("list memory")
{
  using namespace rsl::test;

  card32 num_allocs = test_allocator::all_num_allocs();
  card32 num_frees  = test_allocator::all_num_frees();

  {
    rsl::list<int, test_allocator> list;
    CHECK(test_allocator::all_num_allocs() == num_allocs);

    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    CHECK(test_allocator::all_num_allocs() == num_allocs + 3);
    CHECK(test_allocator::all_num_frees() == num_frees);

    list.pop_back();
    CHECK(test_allocator::all_num_frees() == num_frees + 1);
  }

  // every allocated node is freed on destruction
  CHECK(test_allocator::all_num_allocs() - num_allocs == test_allocator::all_num_frees() - num_frees);

  // every element that was constructed gets destroyed
  test_object::reset();
  {
    rsl::list<test_object> list;
    list.emplace_back(1);
    list.emplace_back(2);
    list.emplace_front(3);
  }
  CHECK(test_object::num_ctor_calls() == 3);
  CHECK(test_object::num_dtor_calls() == 3);
  CHECK(test_object::is_clear());
  test_object::reset();
}

// NOLINTEND
