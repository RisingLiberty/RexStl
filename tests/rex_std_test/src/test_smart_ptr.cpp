// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_smart_ptr.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/memory.h"

// ref_ptr.h uses RSL_ASSERT_X but doesn't include the definition of rsl::rex_assert
#include "rex_std/assert.h"

#include "rex_std_test/test_object.h"

namespace smart_ptr_test
{
  struct base
  {
    virtual ~base() = default;
    int base_value  = 1;
  };

  struct derived : base
  {
    int derived_value = 2;
  };
} // namespace smart_ptr_test

TEST_CASE("shared ptr construction")
{
  // shared_ptr()
  {
    rsl::shared_ptr<int> ptr;
    CHECK(!ptr);
    CHECK(ptr.get() == nullptr);
    CHECK(ptr == nullptr);
  }

  // shared_ptr(nullptr)
  {
    rsl::shared_ptr<int> ptr(nullptr);
    CHECK(!ptr);
    CHECK(ptr.get() == nullptr);
  }

  // make_shared
  {
    rsl::shared_ptr<int> ptr = rsl::make_shared<int>(5);
    CHECK(ptr);
    CHECK(ptr.get() != nullptr);
    CHECK(*ptr == 5);
    CHECK(ptr.use_count() == 1);
    CHECK(ptr != nullptr);
  }

  // make_shared with multiple arguments
  {
    using namespace rsl::test;
    auto ptr = rsl::make_shared<test_object>(1, 2, 3);
    CHECK(ptr->x() == 6);
  }
}

TEST_CASE("shared ptr access")
{
  auto ptr = rsl::make_shared<smart_ptr_test::derived>();
  CHECK(ptr->base_value == 1);
  CHECK(ptr->derived_value == 2);
  CHECK((*ptr).derived_value == 2);

  ptr->derived_value = 10;
  CHECK(ptr.get()->derived_value == 10);
}

TEST_CASE("shared ptr shared ownership")
{
  using namespace smart_ptr_test;

  // converting copy construction shares ownership
  {
    rsl::shared_ptr<derived> ptr = rsl::make_shared<derived>();
    CHECK(ptr.use_count() == 1);

    {
      rsl::shared_ptr<base> base_ptr(ptr);
      CHECK(ptr.use_count() == 2);
      CHECK(base_ptr.use_count() == 2);
      CHECK(base_ptr.get() == ptr.get());
    }

    CHECK(ptr.use_count() == 1);
  }

  // converting copy assignment shares ownership
  {
    rsl::shared_ptr<derived> ptr = rsl::make_shared<derived>();
    rsl::shared_ptr<base> base_ptr;
    base_ptr = ptr;
    CHECK(ptr.use_count() == 2);
    CHECK(base_ptr.get() == ptr.get());
  }

  // converting move construction transfers ownership
  {
    rsl::shared_ptr<derived> ptr = rsl::make_shared<derived>();
    derived* raw                 = ptr.get();
    rsl::shared_ptr<base> base_ptr(rsl::move(ptr));
    CHECK(base_ptr.use_count() == 1);
    CHECK(base_ptr.get() == raw);
    CHECK(ptr.get() == nullptr);
  }

  // aliasing constructor
  {
    rsl::shared_ptr<derived> ptr = rsl::make_shared<derived>();
    rsl::shared_ptr<int> alias(ptr, &ptr->derived_value);
    CHECK(*alias == 2);
    CHECK(ptr.use_count() == 2);
    CHECK(alias.use_count() == 2);
  }
}

TEST_CASE("shared ptr lifetime")
{
  using namespace rsl::test;
  test_object::reset();

  {
    auto ptr = rsl::make_shared<test_object>(1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_dtor_calls() == 0);
  }
  CHECK(test_object::num_dtor_calls() == 1);
  CHECK(test_object::is_clear());

  // the object is destroyed only when the last owner goes away
  {
    struct holder : test_object
    {
      holder()
          : test_object(5)
      {
      }
    };

    rsl::shared_ptr<test_object> outer;
    {
      auto inner = rsl::make_shared<holder>();
      outer      = inner;
      CHECK(outer.use_count() == 2);
    }
    CHECK(outer.use_count() == 1);
    CHECK(test_object::num_dtor_calls() == 1);
    CHECK(outer->x() == 5);
  }
  CHECK(test_object::num_dtor_calls() == 2);
  CHECK(test_object::is_clear());
  test_object::reset();
}

TEST_CASE("shared ptr modifiers")
{
  using namespace rsl::test;
  test_object::reset();

  // reset
  {
    auto ptr = rsl::make_shared<test_object>(1);
    ptr.reset();
    CHECK(!ptr);
    CHECK(ptr.get() == nullptr);
    CHECK(test_object::num_dtor_calls() == 1);
  }

  // swap
  {
    auto ptr1 = rsl::make_shared<int>(1);
    auto ptr2 = rsl::make_shared<int>(2);
    int* raw1 = ptr1.get();
    int* raw2 = ptr2.get();

    ptr1.swap(ptr2);
    CHECK(ptr1.get() == raw2);
    CHECK(ptr2.get() == raw1);
    CHECK(*ptr1 == 2);
    CHECK(*ptr2 == 1);

    rsl::shared_ptr<int> empty;
    ptr1.swap(empty);
    CHECK(!ptr1);
    CHECK(*empty == 2);
  }

  CHECK(test_object::is_clear());
  test_object::reset();
}

TEST_CASE("shared ptr comparison")
{
  auto ptr1 = rsl::make_shared<int>(1);
  auto ptr2 = rsl::make_shared<int>(1);
  rsl::shared_ptr<int> empty1;
  rsl::shared_ptr<int> empty2;

  CHECK(ptr1 == ptr1);
  CHECK(ptr1 != ptr2);
  CHECK(empty1 == empty2);
  CHECK(empty1 == nullptr);
  CHECK(ptr1 != nullptr);
}

TEST_CASE("shared ptr casts")
{
  using namespace smart_ptr_test;

  rsl::shared_ptr<base> base_ptr = rsl::make_shared<derived>();
  auto derived_ptr               = rsl::static_pointer_cast<derived>(base_ptr);
  CHECK(derived_ptr.get() == base_ptr.get());
  CHECK(derived_ptr->derived_value == 2);
  CHECK(base_ptr.use_count() == 2);

  rsl::shared_ptr<const int> const_ptr = rsl::make_shared<const int>(5);
  rsl::shared_ptr<int> mutable_ptr     = rsl::const_pointer_cast<int>(const_ptr);
  CHECK(mutable_ptr.get() == const_ptr.get());
  *mutable_ptr = 6;
  CHECK(*const_ptr == 6);
}

TEST_CASE("unique array construction")
{
  // unique_array()
  {
    rsl::unique_array<int> arr;
    CHECK(!arr);
    CHECK(arr.get() == nullptr);
    CHECK(arr.count() == 0);
    CHECK(arr.byte_size() == 0);
  }

  // unique_array(nullptr)
  {
    rsl::unique_array<int> arr(nullptr);
    CHECK(!arr);
    CHECK(arr.count() == 0);
  }

  // make_unique
  {
    rsl::unique_array<int> arr = rsl::make_unique<int[]>(5);
    CHECK(arr);
    CHECK(arr.count() == 5);
    CHECK(arr.elem_size() == sizeof(int));
    CHECK(arr.byte_size() == 5 * sizeof(int));

    // elements are value initialized
    for(card64 i = 0; i < arr.count(); ++i)
    {
      CHECK(arr[i] == 0);
    }
  }

  // unique_array(pointer, count)
  {
    rsl::unique_array<int> arr(new int[3] {1, 2, 3}, 3);
    CHECK(arr.count() == 3);
    CHECK(arr[0] == 1);
    CHECK(arr[1] == 2);
    CHECK(arr[2] == 3);
  }

  // move construction
  {
    rsl::unique_array<int> arr = rsl::make_unique<int[]>(4);
    int* raw                   = arr.get();
    rsl::unique_array<int> moved(rsl::move(arr));
    CHECK(moved.get() == raw);
    CHECK(moved.count() == 4);
    CHECK(arr.get() == nullptr);
  }
}

TEST_CASE("unique array access")
{
  rsl::unique_array<int> arr = rsl::make_unique<int[]>(5);
  for(card64 i = 0; i < arr.count(); ++i)
  {
    arr[i] = static_cast<int>(i * 2);
  }

  CHECK(arr[0] == 0);
  CHECK(arr[4] == 8);

  const rsl::unique_array<int>& const_arr = arr;
  CHECK(const_arr[2] == 4);
  CHECK(const_arr.get() == arr.get());

  // iterators
  int sum = 0;
  for(int x : arr)
  {
    sum += x;
  }
  CHECK(sum == 20);
  CHECK(arr.end() - arr.begin() == 5);
  CHECK(const_arr.cend() - const_arr.cbegin() == 5);
}

TEST_CASE("unique array modifiers")
{
  // release
  {
    rsl::unique_array<int> arr = rsl::make_unique<int[]>(3);
    int* raw                   = arr.get();
    int* released              = arr.release();
    CHECK(released == raw);
    CHECK(arr.get() == nullptr);
    CHECK(arr.count() == 0);
    delete[] released;
  }

  // reset
  {
    rsl::unique_array<int> arr = rsl::make_unique<int[]>(3);
    arr.reset(new int[2] {7, 8}, 2);
    CHECK(arr.count() == 2);
    CHECK(arr[0] == 7);
    CHECK(arr[1] == 8);

    arr.reset();
    CHECK(!arr);
    CHECK(arr.count() == 0);
  }

  // move assignment
  {
    rsl::unique_array<int> arr1 = rsl::make_unique<int[]>(3);
    rsl::unique_array<int> arr2 = rsl::make_unique<int[]>(5);
    int* raw2                   = arr2.get();

    arr1 = rsl::move(arr2);
    CHECK(arr1.get() == raw2);
    CHECK(arr1.count() == 5);
    CHECK(arr2.get() == nullptr);
    CHECK(arr2.count() == 0);
  }

  // swap
  {
    rsl::unique_array<int> arr1 = rsl::make_unique<int[]>(3);
    rsl::unique_array<int> arr2 = rsl::make_unique<int[]>(5);
    int* raw1                   = arr1.get();
    int* raw2                   = arr2.get();

    arr1.swap(arr2);
    CHECK(arr1.get() == raw2);
    CHECK(arr1.count() == 5);
    CHECK(arr2.get() == raw1);
    CHECK(arr2.count() == 3);
  }
}

// Hidden by default: default_delete_array calls operator delete[] directly instead of using a delete[] expression.
// For types with a non trivial destructor this skips the destructors and corrupts the heap, crashing the test run.
// Run explicitly with: "unique array lifetime"
TEST_CASE("unique array lifetime", "[.]")
{
  using namespace rsl::test;
  test_object::reset();

  {
    rsl::unique_array<test_object> arr = rsl::make_unique<test_object[]>(4);
    CHECK(test_object::num_ctor_calls() == 4);
    CHECK(test_object::num_dtor_calls() == 0);
  }
  CHECK(test_object::num_dtor_calls() == 4);
  CHECK(test_object::is_clear());
  test_object::reset();
}

// NOLINTEND
