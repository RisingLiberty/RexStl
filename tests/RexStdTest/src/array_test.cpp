// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: array_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/array.h"

#include "rex_std/bonus/utility/scopeguard.h"

#include "rex_std_test/test_object.h"

TEST_CASE("array construction")
{
  using namespace rsl::test;

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr;
    REQUIRE(arr.size() == 10);
    REQUIRE(test_object::num_alive() == 10);
    REQUIRE(test_object::num_ctor_calls() == 10);
    REQUIRE(test_object::num_copy_ctor_calls() == 0);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  REQUIRE(test_object::num_alive() == 0);
  REQUIRE(test_object::num_ctor_calls() == 10);
  REQUIRE(test_object::num_copy_ctor_calls() == 0);
  REQUIRE(test_object::num_move_ctor_calls() == 0);
  REQUIRE(test_object::num_dtor_calls() == 10);
  REQUIRE(test_object::num_copy_assignment_calls() == 0);
  REQUIRE(test_object::num_move_assignment_calls() == 0);

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };
    REQUIRE(arr.size() == 10);
    REQUIRE(test_object::num_alive() == 10);
    REQUIRE(test_object::num_ctor_calls() == 10);
    REQUIRE(test_object::num_copy_ctor_calls() == 0);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  REQUIRE(test_object::num_alive() == 0);
  REQUIRE(test_object::num_ctor_calls() == 10);
  REQUIRE(test_object::num_copy_ctor_calls() == 0);
  REQUIRE(test_object::num_move_ctor_calls() == 0);
  REQUIRE(test_object::num_dtor_calls() == 10);
  REQUIRE(test_object::num_copy_assignment_calls() == 0);
  REQUIRE(test_object::num_move_assignment_calls() == 0);

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };
    const rsl::array<test_object, 10> arr2 = arr;
    REQUIRE(arr.size() == 10);
    REQUIRE(arr2.size() == 10);
    REQUIRE(test_object::num_alive() == 20);
    REQUIRE(test_object::num_ctor_calls() == 10);
    REQUIRE(test_object::num_copy_ctor_calls() == 10);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  REQUIRE(test_object::num_alive() == 0);
  REQUIRE(test_object::num_ctor_calls() == 10);
  REQUIRE(test_object::num_copy_ctor_calls() == 10);
  REQUIRE(test_object::num_move_ctor_calls() == 0);
  REQUIRE(test_object::num_dtor_calls() == 20);
  REQUIRE(test_object::num_copy_assignment_calls() == 0);
  REQUIRE(test_object::num_move_assignment_calls() == 0);

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };
    const rsl::array<test_object, 10> arr2 = rsl::move(arr);
    REQUIRE(arr.size() == 10);
    REQUIRE(arr2.size() == 10);
    REQUIRE(test_object::num_alive() == 20);
    REQUIRE(test_object::num_ctor_calls() == 10);
    REQUIRE(test_object::num_copy_ctor_calls() == 10); // std::move on a rsl::array copies each element, as there's no move ctor provided for a rsl::array
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  REQUIRE(test_object::num_alive() == 0);
  REQUIRE(test_object::num_ctor_calls() == 10);
  REQUIRE(test_object::num_copy_ctor_calls() == 10);
  REQUIRE(test_object::num_move_ctor_calls() == 0);
  REQUIRE(test_object::num_dtor_calls() == 20);
  REQUIRE(test_object::num_copy_assignment_calls() == 0);
  REQUIRE(test_object::num_move_assignment_calls() == 0);
}

TEST_CASE("array assignment")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::array<test_object, 10> arr;
  const rsl::array<test_object, 10> arr2;

  REQUIRE(arr.size() == 10);
  REQUIRE(arr2.size() == 10);
  REQUIRE(test_object::num_alive() == 20);
  REQUIRE(test_object::num_ctor_calls() == 20);
  REQUIRE(test_object::num_copy_ctor_calls() == 0);
  REQUIRE(test_object::num_move_ctor_calls() == 0);
  REQUIRE(test_object::num_dtor_calls() == 0);
  REQUIRE(test_object::num_copy_assignment_calls() == 0);
  REQUIRE(test_object::num_move_assignment_calls() == 0);

  arr = arr2;

  REQUIRE(arr.size() == 10);
  REQUIRE(arr2.size() == 10);
  REQUIRE(test_object::num_alive() == 20);
  REQUIRE(test_object::num_ctor_calls() == 20);
  REQUIRE(test_object::num_copy_ctor_calls() == 0);
  REQUIRE(test_object::num_move_ctor_calls() == 0);
  REQUIRE(test_object::num_dtor_calls() == 0);
  REQUIRE(test_object::num_copy_assignment_calls() == 10);
  REQUIRE(test_object::num_move_assignment_calls() == 0);
}

TEST_CASE("array element access")
{
  using namespace rsl::test;

  {
    test_object::reset();

    rsl::array<test_object, 10> arr;
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    REQUIRE(arr[0] == 1);
    REQUIRE(arr.at(0) == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr.at(1) == 2);
    REQUIRE(arr[2] == 3);
    REQUIRE(arr.at(2) == 3);
    REQUIRE(arr[3] == 0);
    REQUIRE(arr.at(3) == 0);

    REQUIRE(arr.front() == 1);
    REQUIRE(*arr.begin() == 1);
    REQUIRE(*arr.cbegin() == 1);
    REQUIRE(*arr.rbegin() == 0);
    REQUIRE(*arr.crbegin() == 0);
    REQUIRE(arr.back() == 0);
    REQUIRE(*--arr.end() == 0);
    REQUIRE(*--arr.cend() == 0);
    REQUIRE(*--arr.rend() == 1);
    REQUIRE(*--arr.crend() == 1);

    REQUIRE(test_object::num_alive() == 10);
    REQUIRE(test_object::num_ctor_calls() == 13);
    REQUIRE(test_object::num_copy_ctor_calls() == 0);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 3);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 3);
  }

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };

    REQUIRE(arr[0] == 1);
    REQUIRE(arr.at(0) == 1);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr.at(1) == 2);
    REQUIRE(arr[2] == 3);
    REQUIRE(arr.at(2) == 3);
    REQUIRE(arr[3] == 0);
    REQUIRE(arr.at(3) == 0);

    REQUIRE(test_object::num_alive() == 10);
    REQUIRE(test_object::num_ctor_calls() == 10);
    REQUIRE(test_object::num_copy_ctor_calls() == 0);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }
}

TEST_CASE("array swap")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::array<test_object, 3> arr = { 1, 2, 3 };
  rsl::array<test_object, 3> arr2 = { 4, 5, 6 };

  arr.swap(arr2);

  REQUIRE(arr[0] == 4);
  REQUIRE(arr[1] == 5);
  REQUIRE(arr[2] == 6);
  REQUIRE(arr2[0] == 1);
  REQUIRE(arr2[1] == 2);
  REQUIRE(arr2[2] == 3);

  REQUIRE(test_object::num_alive() == 6);
  REQUIRE(test_object::num_ctor_calls() == 6);
  REQUIRE(test_object::num_copy_ctor_calls() == 0);
  REQUIRE(test_object::num_move_ctor_calls() == 3);
  REQUIRE(test_object::num_dtor_calls() == 3);
  REQUIRE(test_object::num_copy_assignment_calls() == 0);
  REQUIRE(test_object::num_move_assignment_calls() == 6);
}

TEST_CASE("array fill")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::array<test_object, 3> arr;

  arr.fill(5);

  REQUIRE(arr[0] == 5);
  REQUIRE(arr[1] == 5);
  REQUIRE(arr[2] == 5);
  REQUIRE(test_object::num_alive() == 3);
  REQUIRE(test_object::num_ctor_calls() == 4);
  REQUIRE(test_object::num_copy_ctor_calls() == 0);
  REQUIRE(test_object::num_move_ctor_calls() == 0);
  REQUIRE(test_object::num_dtor_calls() == 1);
  REQUIRE(test_object::num_copy_assignment_calls() == 3);
  REQUIRE(test_object::num_move_assignment_calls() == 0);
}

TEST_CASE("array empty")
{
  using namespace rsl::test;

  test_object::reset();

  {
    rsl::array<test_object, 1> arr;
    REQUIRE(arr.empty() == false);
  }

  {
    rsl::array<test_object, 0> arr;
    REQUIRE(arr.empty() == true);
  }
}