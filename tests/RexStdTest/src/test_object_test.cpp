// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_object_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/utility/move.h"

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std_test/test_object.h"

TEST_CASE("test object")
{
  {
    rsl::test::test_object::reset();

    rsl::test::test_object obj{};

    CHECK(rsl::test::test_object::num_created() == 1);
    CHECK(rsl::test::test_object::num_ctor_calls() == 1);
    CHECK(rsl::test::test_object::num_dtor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
    CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);
  }

  CHECK(rsl::test::test_object::num_created() == 1);
  CHECK(rsl::test::test_object::num_ctor_calls() == 1);
  CHECK(rsl::test::test_object::num_dtor_calls() == 1);
  CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
  CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);

  {
    rsl::test::test_object::reset();

    rsl::test::test_object obj{};
    rsl::test::test_object obj2{ obj };

    CHECK(rsl::test::test_object::num_created() == 2);
    CHECK(rsl::test::test_object::num_ctor_calls() == 1);
    CHECK(rsl::test::test_object::num_dtor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_ctor_calls() == 1);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
    CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);
  }

  CHECK(rsl::test::test_object::num_created() == 2);
  CHECK(rsl::test::test_object::num_ctor_calls() == 1);
  CHECK(rsl::test::test_object::num_dtor_calls() == 2);
  CHECK(rsl::test::test_object::num_copy_ctor_calls() == 1);
  CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
  CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);

  {
    rsl::test::test_object::reset();

    rsl::test::test_object obj{};
    rsl::test::test_object obj2{ rsl::move(obj) };

    CHECK(rsl::test::test_object::num_created() == 2);
    CHECK(rsl::test::test_object::num_ctor_calls() == 1);
    CHECK(rsl::test::test_object::num_dtor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 1);
    CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
    CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);
  }

  CHECK(rsl::test::test_object::num_created() == 2);
  CHECK(rsl::test::test_object::num_ctor_calls() == 1);
  CHECK(rsl::test::test_object::num_dtor_calls() == 2);
  CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_move_ctor_calls() == 1);
  CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
  CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);

  {
    rsl::test::test_object::reset();

    rsl::test::test_object obj{};
    rsl::test::test_object obj2{};
    obj2 = obj;

    CHECK(rsl::test::test_object::num_created() == 2);
    CHECK(rsl::test::test_object::num_ctor_calls() == 2);
    CHECK(rsl::test::test_object::num_dtor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_assignment_calls() == 1);
    CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);
  }

  CHECK(rsl::test::test_object::num_created() == 2);
  CHECK(rsl::test::test_object::num_ctor_calls() == 2);
  CHECK(rsl::test::test_object::num_dtor_calls() == 2);
  CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_copy_assignment_calls() == 1);
  CHECK(rsl::test::test_object::num_move_assignment_calls() == 0);

  {
    rsl::test::test_object::reset();

    rsl::test::test_object obj{};
    rsl::test::test_object obj2{};
    obj2 = rsl::move(obj);

    CHECK(rsl::test::test_object::num_created() == 2);
    CHECK(rsl::test::test_object::num_ctor_calls() == 2);
    CHECK(rsl::test::test_object::num_dtor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
    CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
    CHECK(rsl::test::test_object::num_move_assignment_calls() == 1);
  }

  CHECK(rsl::test::test_object::num_created() == 2);
  CHECK(rsl::test::test_object::num_ctor_calls() == 2);
  CHECK(rsl::test::test_object::num_dtor_calls() == 2);
  CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_move_ctor_calls() == 0);
  CHECK(rsl::test::test_object::num_copy_assignment_calls() == 0);
  CHECK(rsl::test::test_object::num_move_assignment_calls() == 1);
}