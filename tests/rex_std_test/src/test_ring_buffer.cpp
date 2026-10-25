// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_ring_buffer.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/circular_q.h"

#include "rex_std_test/test_object.h"

TEST_CASE("circular q construction")
{
  // default constructed queues are disabled, they never store anything
  {
    rsl::circular_q<int> q;
    CHECK(q.empty());
    CHECK(q.size() == 0);
    CHECK(!q.full());

    q.push_back(1);
    CHECK(q.empty());
    CHECK(q.size() == 0);
  }

  // circular_q(max_items)
  {
    rsl::circular_q<int> q(3);
    CHECK(q.empty());
    CHECK(q.size() == 0);
    CHECK(!q.full());
    CHECK(q.overrun_counter() == 0);
  }
}

TEST_CASE("circular q push and pop")
{
  rsl::circular_q<int> q(3);

  q.push_back(1);
  CHECK(!q.empty());
  CHECK(q.size() == 1);
  CHECK(q.front() == 1);

  q.push_back(2);
  q.push_back(3);
  CHECK(q.size() == 3);
  CHECK(q.full());
  CHECK(q.front() == 1);
  CHECK(q.at(0) == 1);
  CHECK(q.at(1) == 2);
  CHECK(q.at(2) == 3);

  q.pop_front();
  CHECK(q.size() == 2);
  CHECK(!q.full());
  CHECK(q.front() == 2);

  q.pop_front();
  q.pop_front();
  CHECK(q.empty());
  CHECK(q.size() == 0);

  // wrapping around the end of the internal buffer
  q.push_back(4);
  q.push_back(5);
  CHECK(q.size() == 2);
  CHECK(q.at(0) == 4);
  CHECK(q.at(1) == 5);
  CHECK(q.overrun_counter() == 0);
}

TEST_CASE("circular q overrun")
{
  rsl::circular_q<int> q(3);
  q.push_back(1);
  q.push_back(2);
  q.push_back(3);
  CHECK(q.full());

  // pushing into a full queue overwrites the oldest element
  q.push_back(4);
  CHECK(q.full());
  CHECK(q.size() == 3);
  CHECK(q.front() == 2);
  CHECK(q.at(0) == 2);
  CHECK(q.at(1) == 3);
  CHECK(q.at(2) == 4);
  CHECK(q.overrun_counter() == 1);

  q.push_back(5);
  q.push_back(6);
  CHECK(q.size() == 3);
  CHECK(q.at(0) == 4);
  CHECK(q.at(1) == 5);
  CHECK(q.at(2) == 6);
  CHECK(q.overrun_counter() == 3);

  q.reset_overrun_counter();
  CHECK(q.overrun_counter() == 0);
  CHECK(q.size() == 3);
}

TEST_CASE("circular q front modification")
{
  rsl::circular_q<int> q(2);
  q.push_back(1);
  q.front() = 10;
  CHECK(q.front() == 10);

  const rsl::circular_q<int>& const_q = q;
  CHECK(const_q.front() == 10);
}

TEST_CASE("circular q copy and move")
{
  rsl::circular_q<int> q(3);
  q.push_back(1);
  q.push_back(2);

  // copy construction
  rsl::circular_q<int> copy(q);
  CHECK(copy.size() == 2);
  CHECK(copy.at(0) == 1);
  CHECK(copy.at(1) == 2);
  CHECK(q.size() == 2);

  // copy assignment
  rsl::circular_q<int> copy_assigned;
  copy_assigned = q;
  CHECK(copy_assigned.size() == 2);
  CHECK(copy_assigned.at(1) == 2);

  // move construction leaves the source disabled
  rsl::circular_q<int> moved(rsl::move(q));
  CHECK(moved.size() == 2);
  CHECK(moved.at(0) == 1);
  CHECK(q.empty());
  q.push_back(3);
  CHECK(q.empty());

  // move assignment
  rsl::circular_q<int> move_assigned;
  move_assigned = rsl::move(moved);
  CHECK(move_assigned.size() == 2);
  CHECK(move_assigned.at(1) == 2);
  CHECK(moved.empty());
}

TEST_CASE("circular q with non trivial types")
{
  using namespace rsl::test;
  test_object::reset();

  {
    rsl::circular_q<test_object> q(2);
    q.push_back(test_object(1));
    q.push_back(test_object(2));
    q.push_back(test_object(3));
    CHECK(q.size() == 2);
    CHECK(q.at(0).x() == 2);
    CHECK(q.at(1).x() == 3);
    CHECK(q.overrun_counter() == 1);
  }

  CHECK(test_object::is_clear());
  test_object::reset();
}

// NOLINTEND
