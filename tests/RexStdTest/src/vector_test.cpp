// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vector_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/vector.h"
#include "rex_std/bonus/utility/scopeguard.h"

#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_object.h"

TEST_CASE("vector construction")
{
  using namespace rsl::test;

  test_allocator::all_reset();

  {
    test_object::reset();

    const rsl::vector<test_object, test_allocator> vec;
    CHECK(vec.empty());
    CHECK(vec.size() == 0); // NOLINT
    CHECK(vec.capacity() == 0);
    CHECK(vec.get_allocator().num_allocs() == 0);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == 0);
    CHECK(test_object::num_created() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
  test_allocator::all_reset();

  {
    test_object::reset();

    const rsl::vector<test_object, test_allocator> vec(10_size);
    CHECK(vec.size() == 10);
    CHECK(vec.capacity() == 10);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_created() == 10);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
  test_allocator::all_reset();

  {
    test_object::reset();

    const rsl::vector<test_object, test_allocator> vec(10_cap);
    CHECK(vec.size() == 0);
    CHECK(vec.capacity() == 10);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_created() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
  test_allocator::all_reset();

  {
    test_object::reset();

    rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 }; // don't forget that this creates an destroys 3 elements through the initializer list
    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 3);
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_created() == 6);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
  test_allocator::all_reset();

  {
    test_object::reset();

    rsl::vector<test_object, test_allocator> to_copy = { 1, 2, 3 };
    rsl::vector<test_object, test_allocator> vec = to_copy;
    CHECK(to_copy.size() == 3);
    CHECK(to_copy.capacity() == 3);
    CHECK(to_copy[0] == 1);
    CHECK(to_copy[1] == 2);
    CHECK(to_copy[2] == 3);
    CHECK(to_copy.get_allocator().num_allocs() == 1);
    CHECK(to_copy.get_allocator().num_bytes_allocated() == to_copy.capacity() * sizeof(decltype(to_copy)::value_type));
    CHECK(to_copy.get_allocator().num_frees() == 0);
    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 3);
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(to_copy)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_created() == 9);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 6);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
  test_allocator::all_reset();

  {
    test_object::reset();

    rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 };

    vec.clear();
    CHECK(vec.empty());
    CHECK(vec.size() == 0);
    CHECK(vec.capacity() == 3);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_created() == 6);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 6);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
  test_allocator::all_reset();

  {
    test_object::reset();

    rsl::vector<test_object, test_allocator> to_move = { 1, 2, 3 };
    const rsl::vector<test_object, test_allocator> vec = rsl::move(to_move);
    CHECK(to_move.empty());
    CHECK(to_move.size() == 0);
    CHECK(to_move.get_allocator().num_allocs() == 0);
    CHECK(to_move.get_allocator().num_bytes_allocated() == 0);
    CHECK(to_move.get_allocator().num_frees() == 0);
    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 3);
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_created() == 6);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
}

TEST_CASE("vector copy assignment")
{
  using namespace rsl::test;

  test_allocator::all_reset();

  {
    {
      rsl::vector<test_object, test_allocator> vec;
      rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

      test_object::reset();

      vec = vec2; // none-empty to empty

      CHECK(vec.size() == 3);
      CHECK(vec.size() == vec2.size());
      CHECK(vec.empty() == false);
      CHECK(vec.empty() == vec2.empty());
      CHECK(vec.capacity() == 3);
      CHECK(vec.capacity() == vec2.capacity());
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

      // test_object has been reset after creation of the test vectors,
      // this means that only 3 objects are still alive. Those objects
      // are the ones copied into "vec"
      CHECK(test_object::num_created() == vec2.size());
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 0);
      CHECK(test_object::num_copy_ctor_calls() == vec2.size());
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);

    {
      rsl::vector<test_object, test_allocator> vec = { 4, 5 };
      rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

      test_object::reset();

      card32 old_size = vec2.size();
      vec2 = vec; // none-empty to none-empty ( smaller vector to bigger vector)

      CHECK(vec2.size() == 2);
      CHECK(vec2.size() == vec.size());
      CHECK(vec2.empty() == false);
      CHECK(vec2.empty() == vec.empty());
      CHECK(vec2.capacity() == 3);
      CHECK(vec2.capacity() != vec.capacity());
      CHECK(vec2.get_allocator().num_allocs() == 1);
      CHECK(vec2.get_allocator().num_frees() == 0);
      CHECK(vec2.get_allocator().num_bytes_allocated() == sizeof(decltype(vec2)::value_type) * vec2.capacity());
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == old_size - vec.size());
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == vec.size());
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);

    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 };
      rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

      test_object::reset();

      card32 old_size = vec2.size();
      vec2 = vec; // none-empty to none-empty ( bigger vector to smaller vector)

      CHECK(vec2.size() == 3);
      CHECK(vec2.size() == vec.size());
      CHECK(vec2.empty() == false);
      CHECK(vec2.empty() == vec.empty());
      CHECK(vec2.capacity() == 3);
      CHECK(vec2.capacity() == vec.capacity());
      CHECK(vec2.get_allocator().num_allocs() == 2);  // creation and copy
      CHECK(vec2.get_allocator().num_frees() == 1);
      CHECK(vec2.get_allocator().num_bytes_allocated() == sizeof(decltype(vec2)::value_type) * vec2.capacity());
      CHECK(test_object::num_created() == vec.size());
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == old_size);
      CHECK(test_object::num_copy_ctor_calls() == vec.size());
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);

    {
      rsl::vector<test_object, test_allocator> vec;
      rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

      test_object::reset();

      card32 old_size = vec2.size();
      vec2 = vec; // empty to none-empty

      CHECK(vec2.size() == 0);
      CHECK(vec2.size() == vec.size());
      CHECK(vec2.empty() == true);
      CHECK(vec2.empty() == vec.empty());
      CHECK(vec2.capacity() == 2);
      CHECK(vec2.capacity() != vec.capacity());
      CHECK(vec2.get_allocator().num_allocs() == 1);  // creation
      CHECK(vec2.get_allocator().num_frees() == 0);
      CHECK(vec2.get_allocator().num_bytes_allocated() == sizeof(decltype(vec2)::value_type) * vec2.capacity());
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == old_size);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);
  }
}

TEST_CASE("vector move assignment")
{
  using namespace rsl::test;

  test_allocator::all_reset();

  {
    {
      rsl::vector<test_object, test_allocator> vec;
      rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

      test_object::reset();

      card32 vec2_size = vec2.size();
      card32 vec2_cap = vec2.capacity();
      bool vec2_empty = vec2.empty();

      vec = rsl::move(vec2); // none-empty to empty

      CHECK(vec.size() == 3);
      CHECK(vec.size() == vec2_size);
      CHECK(vec.empty() == false);
      CHECK(vec.empty() == vec2_empty);
      CHECK(vec.capacity() == 3);
      CHECK(vec.capacity() == vec2_cap);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec2_cap);

      // test_object has been reset after creation of the test vectors,
      // this means that only 3 objects are still alive. Those objects
      // are the ones copied into "vec"
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 0);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);

    {
      rsl::vector<test_object, test_allocator> vec = { 4, 5 };
      rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

      test_object::reset();

      card32 vec_size = vec.size();
      card32 vec_cap = vec.capacity();
      bool vec_empty = vec.empty();

      vec2 = rsl::move(vec); // non-empty to none-empty ( smaller vector to bigger vector)

      CHECK(vec2.size() == 2);
      CHECK(vec2.size() == vec_size);
      CHECK(vec2.empty() == false);
      CHECK(vec2.empty() == vec_empty);
      CHECK(vec2.capacity() == vec_cap);
      CHECK(vec2.get_allocator().num_allocs() == 1); // 1 allocation from construction
      CHECK(vec2.get_allocator().num_frees() == 0);
      CHECK(vec2.get_allocator().num_bytes_allocated() == sizeof(decltype(vec2)::value_type) * vec_cap);
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 3); // we clear a vector on move
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);

    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 };
      rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

      test_object::reset();

      card32 vec_size = vec.size();
      card32 vec_cap = vec.capacity();
      bool vec_empty = vec.empty();

      vec2 = rsl::move(vec); // none-empty to none-empty ( bigger vector to smaller vector)

      CHECK(vec2.size() == 3);
      CHECK(vec2.size() == vec_size);
      CHECK(vec2.empty() == false);
      CHECK(vec2.empty() == vec_empty);
      CHECK(vec2.capacity() == 3);
      CHECK(vec2.capacity() == vec_cap);
      CHECK(vec2.get_allocator().num_allocs() == 1); // from construction
      CHECK(vec2.get_allocator().num_frees() == 0);
      CHECK(vec2.get_allocator().num_bytes_allocated() == sizeof(decltype(vec2)::value_type) * vec_cap);
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 2);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);

    {
      rsl::vector<test_object, test_allocator> vec;
      rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

      test_object::reset();

      card32 vec_size = vec.size();
      card32 vec_cap = vec.capacity();
      bool vec_empty = vec.empty();

      vec2 = rsl::move(vec); // none-empty to empty

      CHECK(vec2.size() == 0);
      CHECK(vec2.size() == vec_size);
      CHECK(vec2.empty() == true);
      CHECK(vec2.empty() == vec_empty);
      CHECK(vec2.capacity() == 0);
      CHECK(vec2.capacity() == vec_cap);
      CHECK(vec2.get_allocator().num_allocs() == 0);
      CHECK(vec2.get_allocator().num_frees() == 0);
      CHECK(vec2.get_allocator().num_bytes_allocated() == 0);
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 2);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);
  }
}

TEST_CASE("vector misc assignment")
{
  using namespace rsl::test;

  test_allocator::all_reset();

  {
    rsl::vector<test_object, test_allocator> vec;

    test_object::reset();
    vec.assign(10, 2);

    CHECK(vec.size() == 10);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 11);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_dtor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 10);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3 };

    test_object::reset();
    vec.assign(10, 2);

    CHECK(vec.size() == 10);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 2);
    CHECK(vec.get_allocator().num_frees() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 11);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_dtor_calls() == 4);
    CHECK(test_object::num_copy_ctor_calls() == 10);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };

    test_object::reset();
    vec.assign(5, 2);

    CHECK(vec.size() == 5);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 1);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 5);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec;
    rsl::vector<test_object, test_allocator> vec2 = { 1,2,3 };

    test_object::reset();
    vec.assign(vec2.cbegin(), vec2.cend());

    CHECK(vec.size() == 3);
    CHECK(vec.size() == vec2.size());
    CHECK(vec.empty() == false);
    CHECK(vec.empty() == vec2.empty());
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 3);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3 };
    rsl::vector<test_object, test_allocator> vec2 = { 1,2,3,4,5,6 };

    test_object::reset();
    vec.assign(vec2.cbegin(), vec2.cend());

    CHECK(vec.size() == 6);
    CHECK(vec.size() == vec2.size());
    CHECK(vec.empty() == false);
    CHECK(vec.empty() == vec2.empty());
    CHECK(vec.get_allocator().num_allocs() == 2);
    CHECK(vec.get_allocator().num_frees() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 6);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 6);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };
    rsl::vector<test_object, test_allocator> vec2 = { 1,2,3 };

    test_object::reset();
    vec.assign(vec2.cbegin(), vec2.cend());

    CHECK(vec.size() == 3);
    CHECK(vec.size() == vec2.size());
    CHECK(vec.empty() == false);
    CHECK(vec.empty() == vec2.empty());
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 4);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 3);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec;

    test_object::reset();
    vec.assign({ 1,2,3 });

    CHECK(vec.size() == 3);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 6);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3 };

    test_object::reset();
    vec.assign({ 1,2,3,4,5,6 });

    CHECK(vec.size() == 6);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 2);
    CHECK(vec.get_allocator().num_frees() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 12);
    CHECK(test_object::num_ctor_calls() == 6);
    CHECK(test_object::num_dtor_calls() == 9);
    CHECK(test_object::num_copy_ctor_calls() == 6);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };

    test_object::reset();
    vec.assign({ 1,2,3 });

    CHECK(vec.size() == 3);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 3);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 7);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 3);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec;

    test_object::reset();
    vec = { 1,2,3 };

    CHECK(vec.size() == 3);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 6);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3 };

    test_object::reset();
    vec = { 1,2,3,4,5,6 };

    CHECK(vec.size() == 6);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 2);
    CHECK(vec.get_allocator().num_frees() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 12);
    CHECK(test_object::num_ctor_calls() == 6);
    CHECK(test_object::num_dtor_calls() == 9);
    CHECK(test_object::num_copy_ctor_calls() == 6);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);

  {
    rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };

    test_object::reset();
    vec = { 1,2,3 };

    CHECK(vec.size() == 3);
    CHECK(vec.empty() == false);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == sizeof(decltype(vec)::value_type) * vec.capacity());

    // test_object has been reset after creation of the test vectors,
    // this means that only 3 objects are still alive. Those objects
    // are the ones copied into "vec"
    CHECK(test_object::num_created() == 3);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 7);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 3);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
}

TEST_CASE("vector size")
{
  rsl::vector<int> vec;
  CHECK(vec.size() == 0); // NOLINT
  CHECK(vec.empty());

  vec.push_back(1);
  CHECK(vec.size() == 1);

  vec.push_back(1);
  CHECK(vec.size() == 2);

  vec.clear();
  CHECK(vec.empty());
  CHECK(vec.size() == 0); // NOLINT

  vec.resize(10);
  CHECK(vec.size() == 10);

  vec.resize(5);
  CHECK(vec.size() == 5);

  vec.reserve(20);
  CHECK(vec.size() == 5);
  CHECK(vec.capacity() == 20);

  vec.pop_back();
  CHECK(vec.size() == 4);
  CHECK(vec.capacity() == 20);

  vec.pop_back();
  CHECK(vec.size() == 3);
  CHECK(vec.capacity() == 20);
}

TEST_CASE("vector element access")
{
  rsl::vector<int> vec;

  vec.push_back(1);
  CHECK(vec[0] == 1);
  CHECK(vec.front() == 1);
  CHECK(*vec.begin() == 1);
  CHECK(vec.back() == 1);
  CHECK(*--vec.end() == 1);

  vec.push_back(2);
  CHECK(vec[0] == 1);
  CHECK(vec.front() == 1);
  CHECK(*vec.begin() == 1);
  CHECK(vec[1] == 2);
  CHECK(vec.back() == 2);
  CHECK(*--vec.end() == 2);

  vec.push_back(3);
  CHECK(vec[0] == 1);
  CHECK(vec.front() == 1);
  CHECK(*vec.begin() == 1);
  CHECK(vec[1] == 2);
  CHECK(vec[2] == 3);
  CHECK(vec.back() == 3);
  CHECK(*--vec.end() == 3);
}

TEST_CASE("vector insertion")
{
  rsl::vector<int> vec;

  vec.insert(vec.cend(), 1);
  CHECK(vec[0] == 1);
  CHECK(vec.size() == 1);
  CHECK(vec.capacity() >= 1);

  vec.insert(vec.cbegin(), 2);
  CHECK(vec[0] == 2);
  CHECK(vec[1] == 1);
  CHECK(vec.size() == 2);
  CHECK(vec.capacity() >= 2);

  vec.reserve(100);
  vec.insert(vec.cbegin(), 2);
  CHECK(vec[0] == 2);
  CHECK(vec[1] == 2);
  CHECK(vec[2] == 1);
  CHECK(vec.size() == 3);
  CHECK(vec.capacity() == 100);
}

// NOLINTEND
