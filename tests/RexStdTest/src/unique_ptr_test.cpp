// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: unique_ptr_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std_test/test_object.h"

#include "rex_std/memory.h"

TEST_CASE("unique ptr construction")
{
  using namespace rsl::test;

  // unique_ptr()
  {
    test_object::reset();

    rsl::unique_ptr<test_object> ptr;
    
    CHECK(ptr.get() == nullptr);
    CHECK(ptr.operator->() == nullptr);
    CHECK(ptr.operator bool() == false);
    CHECK(test_object::num_alive() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 0);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 0);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  // unique_ptr(rsl::nullptr_t)
  {
    test_object::reset();

    rsl::unique_ptr<test_object> ptr = nullptr;

    CHECK(ptr.get() == nullptr);
    CHECK(ptr.operator->() == nullptr);
    CHECK(ptr.operator bool() == false);
    CHECK(test_object::num_alive() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 0);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 0);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  // unique_ptr(pointer ptr)
  {
    test_object::reset();

    rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);

    CHECK(ptr.get() != nullptr);
    CHECK(ptr.operator->() != nullptr);
    CHECK(ptr.operator bool() == true);
    CHECK(*ptr == 1);
    CHECK(*ptr.get() == 1);
    CHECK(test_object::num_alive() == 1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 1);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 1);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  // unique_ptr(pointer ptr, const deleter_t& deleter)
  {
    test_object::reset();

    auto custom_deleter = [](test_object* ptr) { delete ptr; };
    using custom_deleter_t = decltype(custom_deleter);
    rsl::unique_ptr<test_object, custom_deleter_t> ptr(new test_object(1), custom_deleter);

    CHECK(ptr.get() != nullptr);
    CHECK(ptr.operator->() != nullptr);
    CHECK(ptr.operator bool() == true);
    CHECK(*ptr == 1);
    CHECK(*ptr.get() == 1);
    CHECK(test_object::num_alive() == 1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 1);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 1);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  // unique_ptr(pointer ptr, deleter&& deleter)
  {
    test_object::reset();

    auto custom_deleter = [](test_object* ptr) { delete ptr; };
    using custom_deleter_t = decltype(custom_deleter);
    rsl::unique_ptr<test_object, custom_deleter_t> ptr(new test_object(1), rsl::move(custom_deleter));

    CHECK(ptr.get() != nullptr);
    CHECK(ptr.operator->() != nullptr);
    CHECK(ptr.operator bool() == true);
    CHECK(*ptr == 1);
    CHECK(*ptr.get() == 1);
    CHECK(test_object::num_alive() == 1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 1);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 1);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  // unique_ptr(unique_ptr&& ptr)
  {
    test_object::reset();

    rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);
    rsl::unique_ptr<test_object> ptr2 = rsl::move(ptr);

    CHECK(ptr.get() == nullptr);
    CHECK(ptr.operator->() == nullptr);
    CHECK(ptr.operator bool() == false);
    CHECK(ptr2.get() != nullptr);
    CHECK(ptr2.operator->() != nullptr);
    CHECK(ptr2.operator bool() == true);
    CHECK(*ptr2 == 1);
    CHECK(*ptr2.get() == 1);
    CHECK(test_object::num_alive() == 1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 1);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 1);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);
}
TEST_CASE("unique ptr assignment")
{
  using namespace rsl::test;

  // operator= (unique_ptr&& ptr)
  {
    {
      test_object::reset();

      rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);
      rsl::unique_ptr<test_object> ptr2;
      ptr2 = rsl::move(ptr);

      CHECK(ptr.get() == nullptr);
      CHECK(ptr.operator->() == nullptr);
      CHECK(ptr.operator bool() == false);
      CHECK(ptr2.get() != nullptr);
      CHECK(ptr2.operator->() != nullptr);
      CHECK(ptr2.operator bool() == true);
      CHECK(*ptr2 == 1);
      CHECK(*ptr2.get() == 1);

      CHECK(test_object::num_alive() == 1);
      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }
    {
      test_object::reset();

      rsl::unique_ptr<test_object> ptr;
      rsl::unique_ptr<test_object> ptr2 = rsl::make_unique<test_object>(1);
      ptr2 = rsl::move(ptr);

      CHECK(ptr.get() == nullptr);
      CHECK(ptr.operator->() == nullptr);
      CHECK(ptr.operator bool() == false);
      CHECK(ptr2.get() == nullptr);
      CHECK(ptr2.operator->() == nullptr);
      CHECK(ptr2.operator bool() == false);

      CHECK(test_object::num_alive() == 0);
      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 1);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }
    {
      test_object::reset();

      rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);
      rsl::unique_ptr<test_object> ptr2 = rsl::make_unique<test_object>(2);
      ptr2 = rsl::move(ptr);

      CHECK(ptr.get() == nullptr);
      CHECK(ptr.operator->() == nullptr);
      CHECK(ptr.operator bool() == false);
      CHECK(ptr2.get() != nullptr);
      CHECK(ptr2.operator->() != nullptr);
      CHECK(ptr2.operator bool() == true);
      CHECK(*ptr2 == 1);
      CHECK(*ptr2.get() == 1);

      CHECK(test_object::num_alive() == 1);
      CHECK(test_object::num_ctor_calls() == 2);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 1);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }
  }

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 2);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 2);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);
}
TEST_CASE("unique ptr release")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);

  test_object* raw_ptr = ptr.release();

  CHECK(ptr.get() == nullptr);
  CHECK(ptr.operator->() == nullptr);
  CHECK(ptr.operator bool() == false);

  CHECK(*raw_ptr == 1);

  CHECK(test_object::num_alive() == 1);
  CHECK(test_object::num_ctor_calls() == 1);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 0);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);

  delete raw_ptr;
}
TEST_CASE("unique ptr reset")
{
  using namespace rsl::test;

  test_object::reset();

  rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);

  ptr.reset();

  CHECK(ptr.get() == nullptr);
  CHECK(ptr.operator->() == nullptr);
  CHECK(ptr.operator bool() == false);

  CHECK(test_object::num_alive() == 0);
  CHECK(test_object::num_ctor_calls() == 1);
  CHECK(test_object::num_copy_ctor_calls() == 0);
  CHECK(test_object::num_move_ctor_calls() == 0);
  CHECK(test_object::num_dtor_calls() == 1);
  CHECK(test_object::num_copy_assignment_calls() == 0);
  CHECK(test_object::num_move_assignment_calls() == 0);
}
TEST_CASE("unique ptr swap")
{
  using namespace rsl::test;

  {
    test_object::reset();

    rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);
    rsl::unique_ptr<test_object> ptr2;
    ptr2.swap(ptr);

    CHECK(ptr.get() == nullptr);
    CHECK(ptr.operator->() == nullptr);
    CHECK(ptr.operator bool() == false);
    CHECK(ptr2.get() != nullptr);
    CHECK(ptr2.operator->() != nullptr);
    CHECK(ptr2.operator bool() == true);
    CHECK(*ptr2 == 1);
    CHECK(*ptr2.get() == 1);

    CHECK(test_object::num_alive() == 1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }
  {
    test_object::reset();

    rsl::unique_ptr<test_object> ptr;
    rsl::unique_ptr<test_object> ptr2 = rsl::make_unique<test_object>(1);
    ptr2.swap(ptr);

    CHECK(ptr.get() != nullptr);
    CHECK(ptr.operator->() != nullptr);
    CHECK(ptr.operator bool() == true);
    CHECK(ptr2.get() == nullptr);
    CHECK(ptr2.operator->() == nullptr);
    CHECK(ptr2.operator bool() == false);

    CHECK(test_object::num_alive() == 1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }
  {
    test_object::reset();

    rsl::unique_ptr<test_object> ptr = rsl::make_unique<test_object>(1);
    rsl::unique_ptr<test_object> ptr2 = rsl::make_unique<test_object>(2);
    ptr2.swap(ptr);

    CHECK(ptr.get() != nullptr);
    CHECK(ptr.operator->() != nullptr);
    CHECK(ptr.operator bool() == true);
    CHECK(ptr2.get() != nullptr);
    CHECK(ptr2.operator->() != nullptr);
    CHECK(ptr2.operator bool() == true);
    CHECK(*ptr2 == 1);
    CHECK(*ptr2.get() == 1);

    CHECK(test_object::num_alive() == 2);
    CHECK(test_object::num_ctor_calls() == 2);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }
}