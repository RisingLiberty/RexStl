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

// somehow this is resulting in an asan issue with a misaligned global with an empty name (likely in one of the headers)
#include "rex_std/array.h"

#include "rex_std/bonus/utility/scopeguard.h"

#include "rex_std_test/test_object.h"

TEST_CASE("array construction")
{
  using namespace rsl::test;

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr;
    CHECK(arr.size() == 10);
    CHECK(test_object::num_created() == 10);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_created() == 10);
  CHECK(test_object::num_ctor_calls() == 10);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 10);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };
    CHECK(arr.size() == 10);
    CHECK(test_object::num_created() == 10);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_created() == 10);
  CHECK(test_object::num_ctor_calls() == 10);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 10);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };
    const rsl::array<test_object, 10> arr2 = arr;
    CHECK(arr.size() == 10);
    CHECK(arr2.size() == 10);
    CHECK(test_object::num_created() == 20);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_copy_ctor_calls() == 10);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_created() == 20);
  CHECK(test_object::num_ctor_calls() == 10);
  CHECK(test_object::num_copy_ctor_calls() == 10);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 20);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };
    const rsl::array<test_object, 10> arr2 = rsl::move(arr);
    CHECK(arr.size() == 10);
    CHECK(arr2.size() == 10);
    CHECK(test_object::num_created() == 20);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_copy_ctor_calls() == 10); // std::move on a rsl::array copies each element, as there's no move ctor provided for a rsl::array
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_created() == 20);
  CHECK(test_object::num_ctor_calls() == 10);
  CHECK(test_object::num_copy_ctor_calls() == 10);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 20);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);
}

TEST_CASE("array assignment")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::array<test_object, 10> arr;
  const rsl::array<test_object, 10> arr2;

  CHECK(arr.size() == 10);
  CHECK(arr2.size() == 10);
  CHECK(test_object::num_created() == 20);
  CHECK(test_object::num_ctor_calls() == 20);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 0);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  arr = arr2;

  CHECK(arr.size() == 10);
  CHECK(arr2.size() == 10);
  CHECK(test_object::num_created() == 20);
  CHECK(test_object::num_ctor_calls() == 20);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 0);
  CHECK(test_object::num_copy_assignment_calls() == 10);
  CHECK(test_object::num_move_assignment_calls() == 0);
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

    CHECK(arr[0] == 1);
    CHECK(arr.at(0) == 1);
    CHECK(arr[1] == 2);
    CHECK(arr.at(1) == 2);
    CHECK(arr[2] == 3);
    CHECK(arr.at(2) == 3);
    CHECK(arr[3] == 0);
    CHECK(arr.at(3) == 0);

    CHECK(arr.front() == 1);
    CHECK(*arr.begin() == 1);
    CHECK(*arr.cbegin() == 1);
    CHECK(*arr.rbegin() == 0);
    CHECK(*arr.crbegin() == 0);
    CHECK(arr.back() == 0);
    CHECK(*--arr.end() == 0);
    CHECK(*--arr.cend() == 0);
    CHECK(*--arr.rend() == 1);
    CHECK(*--arr.crend() == 1);

    CHECK(test_object::num_created() == 13);
    CHECK(test_object::num_ctor_calls() == 13);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 3);
  }

  {
    test_object::reset();

    const rsl::array<test_object, 10> arr = { 1, 2, 3 };

    CHECK(arr[0] == 1);
    CHECK(arr.at(0) == 1);
    CHECK(arr[1] == 2);
    CHECK(arr.at(1) == 2);
    CHECK(arr[2] == 3);
    CHECK(arr.at(2) == 3);
    CHECK(arr[3] == 0);
    CHECK(arr.at(3) == 0);

    CHECK(test_object::num_created() == 10);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }
}

TEST_CASE("array swap")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::array<test_object, 3> arr = { 1, 2, 3 };
  rsl::array<test_object, 3> arr2 = { 4, 5, 6 };

  arr.swap(arr2);

  CHECK(arr[0] == 4);
  CHECK(arr[1] == 5);
  CHECK(arr[2] == 6);
  CHECK(arr2[0] == 1);
  CHECK(arr2[1] == 2);
  CHECK(arr2[2] == 3);

  CHECK(test_object::num_created() == 9);
  CHECK(test_object::num_ctor_calls() == 6);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 3);
  CHECK(test_object::num_dtor_calls() == 3);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 6);
}

TEST_CASE("array fill")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::array<test_object, 3> arr;

  arr.fill(5);

  CHECK(arr[0] == 5);
  CHECK(arr[1] == 5);
  CHECK(arr[2] == 5);
  CHECK(test_object::num_created() == 4);
  CHECK(test_object::num_ctor_calls() == 4);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 1);
  CHECK(test_object::num_copy_assignment_calls() == 3);
  CHECK(test_object::num_move_assignment_calls() == 0);
}

TEST_CASE("array empty")
{
  using namespace rsl::test;

  test_object::reset();

  {
    rsl::array<test_object, 1> arr;
    CHECK(arr.empty() == false);
  }

  {
    rsl::array<test_object, 0> arr;
    CHECK(arr.empty() == true);
  }
}