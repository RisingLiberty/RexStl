// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_iterator.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/iterator.h"
#include "rex_std/array.h"
#include "rex_std/vector.h"
#include "rex_std/deque.h"
#include "rex_std/internal/iterator/back_insert_iterator.h"
#include "rex_std/internal/iterator/front_insert_iterator.h"
#include "rex_std/internal/iterator/move_iterator.h"
#include "rex_std/internal/iterator/begin.h"
#include "rex_std/internal/iterator/end.h"

#include "rex_std_test/test_object.h"

TEST_CASE("Iterator Advance")
{
  rsl::array arr = { 1,2,3 };
  auto it = arr.cbegin();

  rsl::advance(it, 1);

  CHECK(it == arr.cbegin() + 1);
  CHECK(*it == 2);

  rsl::advance(it, -1);

  CHECK(it == arr.cbegin());
  CHECK(*it == 1);

  rsl::advance(it, 2);

  CHECK(it == arr.cbegin() + 2);
  CHECK(*it == 3);
}

TEST_CASE("Move Iterator")
{
  using namespace rsl::test;

  // dereferencing a move iterator moves the element
  {
    test_object::reset();
    rsl::vector<test_object> src;
    src.emplace_back(1);
    src.emplace_back(2);
    src.emplace_back(3);

    // note: wrapping rsl::vector<T>::iterator doesn't compile at the moment as move_iterator::operator* is const
    // and dereferencing a const rsl vector iterator returns a const reference, so we wrap raw pointers instead
    rsl::move_iterator<test_object*> first(src.data());
    rsl::move_iterator<test_object*> last(src.data() + src.size());

    const card32 num_moves = test_object::num_move_ctor_calls();
    rsl::vector<test_object> dst;
    for(auto it = first; it != last; ++it)
    {
      dst.push_back(*it);
    }
    CHECK(test_object::num_move_ctor_calls() - num_moves >= 3);
    CHECK(dst.size() == 3);
    CHECK(dst[0] == 1);
    CHECK(dst[1] == 2);
    CHECK(dst[2] == 3);
  }
  test_object::reset();

  // the reference type is an rvalue reference
  {
    using iterator = rsl::move_iterator<int*>;
    static_assert(rsl::is_same_v<iterator::reference, int&&>);
    static_assert(rsl::is_same_v<iterator::value_type, int>);
    static_assert(rsl::is_same_v<iterator::iterator_type, int*>);
  }

  // iterator arithmetic
  {
    int arr[] = {1, 2, 3, 4, 5};
    rsl::move_iterator<int*> it(arr);
    CHECK(it.base() == arr);
    CHECK(*it == 1);

    ++it;
    CHECK(*it == 2);
    it++;
    CHECK(*it == 3);
    --it;
    CHECK(*it == 2);
    it--;
    CHECK(*it == 1);

    CHECK(*(it + 3) == 4);
    it += 4;
    CHECK(*it == 5);
    CHECK(*(it - 2) == 3);
    it -= 4;
    CHECK(it.base() == arr);
    CHECK(it[2] == 3);

    rsl::move_iterator<int*> other(arr);
    CHECK(it == other);
    ++other;
    CHECK(it != other);
  }

  // default construction and conversion
  {
    rsl::move_iterator<int*> it;
    CHECK(it.base() == nullptr);

    int arr[] = {1, 2};
    rsl::move_iterator<int*> it2(arr);
    rsl::move_iterator<const int*> const_it(it2);
    CHECK(const_it.base() == arr);
  }
}

TEST_CASE("Reverse Iterator")
{
  // iterating backwards
  {
    int arr[] = {1, 2, 3, 4, 5};
    rsl::reverse_iterator<int*> first(arr + 5);
    rsl::reverse_iterator<int*> last(arr);

    int expected = 5;
    for(auto it = first; it != last; ++it)
    {
      CHECK(*it == expected);
      --expected;
    }
    CHECK(expected == 0);
  }

  // base returns the wrapped iterator, which points one past the referenced element
  {
    int arr[] = {1, 2, 3};
    rsl::reverse_iterator<int*> it(arr + 3);
    CHECK(it.base() == arr + 3);
    CHECK(*it == 3);
  }

  // iterator arithmetic
  {
    int arr[] = {1, 2, 3, 4, 5};
    rsl::reverse_iterator<int*> it(arr + 5);

    CHECK(*(it + 1) == 4);
    CHECK(it[2] == 3);
    it += 2;
    CHECK(*it == 3);
    CHECK(*(it - 1) == 4);
    it -= 1;
    CHECK(*it == 4);
    --it;
    CHECK(*it == 5);

    rsl::reverse_iterator<int*> end(arr);
    CHECK(end - it == 5);

    auto old = it--;
    CHECK(*old == 5);
  }

  // comparison follows the reversed order
  {
    int arr[] = {1, 2, 3};
    rsl::reverse_iterator<int*> first(arr + 3);
    rsl::reverse_iterator<int*> second(arr + 2);

    CHECK(first == first);
    CHECK(first != second);
    CHECK(first < second);
    CHECK(first <= second);
    CHECK(second > first);
    CHECK(second >= first);
  }

  // reverse iterators from containers
  {
    rsl::vector<int> vec = {1, 2, 3};
    int expected         = 3;
    for(auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
      CHECK(*it == expected);
      --expected;
    }
    CHECK(expected == 0);

    // modify through a reverse iterator
    *vec.rbegin() = 10;
    CHECK(vec.back() == 10);
  }
}

TEST_CASE("Iterator Next Prev Distance")
{
  rsl::vector<int> vec = {1, 2, 3, 4, 5};

  CHECK(*rsl::next(vec.begin()) == 2);
  CHECK(*rsl::next(vec.begin(), 3) == 4);
  CHECK(rsl::next(vec.begin(), 5) == vec.end());

  CHECK(*rsl::prev(vec.end()) == 5);
  CHECK(*rsl::prev(vec.end(), 3) == 3);
  CHECK(rsl::prev(vec.end(), 5) == vec.begin());

  CHECK(rsl::distance(vec.begin(), vec.end()) == 5);
  CHECK(rsl::distance(vec.begin(), vec.begin()) == 0);
  CHECK(rsl::distance(vec.end(), vec.begin()) == -5);

  int arr[] = {1, 2, 3};
  CHECK(rsl::distance(arr, arr + 3) == 3);
  CHECK(*rsl::next(arr) == 2);
}

TEST_CASE("Insert Iterators")
{
  // back inserter
  {
    rsl::vector<int> vec;
    auto it = rsl::back_inserter(vec);
    *it     = 1;
    ++it;
    *it = 2;
    it++;
    *it = 3;
    CHECK(vec.size() == 3);
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
  }

  // front inserter
  {
    rsl::deque<int> deq;
    rsl::front_insert_iterator<rsl::deque<int>> it(deq);
    *it = 1;
    *it = 2;
    *it = 3;
    CHECK(deq.size() == 3);
    CHECK(deq[0] == 3);
    CHECK(deq[1] == 2);
    CHECK(deq[2] == 1);
  }

  // inserter
  {
    rsl::vector<int> vec = {1, 5};
    auto it              = rsl::inserter(vec, vec.begin() + 1);
    *it                  = 2;
    *it                  = 3;
    *it                  = 4;
    CHECK(vec.size() == 5);
    for(int i = 0; i < 5; ++i)
    {
      CHECK(vec[i] == i + 1);
    }
  }
}

TEST_CASE("Iterator Begin End")
{
  rsl::vector<int> vec = {1, 2, 3};
  CHECK(rsl::begin(vec) == vec.begin());
  CHECK(rsl::end(vec) == vec.end());
  CHECK(rsl::cbegin(vec) == vec.cbegin());
  CHECK(rsl::cend(vec) == vec.cend());

  const rsl::vector<int>& const_vec = vec;
  CHECK(rsl::begin(const_vec) == const_vec.begin());
  CHECK(rsl::end(const_vec) == const_vec.end());

  int arr[] = {1, 2, 3, 4};
  CHECK(rsl::begin(arr) == arr);
  CHECK(rsl::end(arr) == arr + 4);
  CHECK(rsl::cbegin(arr) == arr);
  CHECK(rsl::cend(arr) == arr + 4);
}
