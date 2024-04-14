// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_vector.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/vector.h"
#include "rex_std/bonus/utility/scopeguard.h"

#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_object.h"
#include "rex_std/string.h"

TEST_CASE("vector construction")
{
  using namespace rsl::test;

  {
    test_allocator::all_reset();

    {
      test_object::reset();

      const rsl::vector<test_object, test_allocator> vec;
      CHECK(vec.empty());
      CHECK(vec.size() == 0);
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

      const rsl::vector<test_object, test_allocator> vec(3_size, 2);
      CHECK(vec.size() == 3);
      CHECK(vec.capacity() == 3);
      CHECK(vec[0] == 2);
      CHECK(vec[1] == 2);
      CHECK(vec[2] == 2);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 4);
      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_dtor_calls() == 1);
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

      rsl::vector<test_object, test_allocator> to_copy = { 1, 2, 3 };
      rsl::vector<test_object, test_allocator> vec(to_copy, test_allocator());
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

    {
      test_object::reset();

      rsl::vector<test_object, test_allocator> to_move = { 1, 2, 3 };
      const rsl::vector<test_object, test_allocator> vec(rsl::move(to_move), test_allocator());
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

  {
    {
      using test_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::test::test_allocator>;

      test_allocator::all_reset();

      rsl::vector<test_string, test_allocator> vec;
      rsl::vector<test_string, test_allocator> vec2(10_size);
      rsl::vector<test_string, test_allocator> vec3(3_size, test_string("this is a big string"));
      rsl::vector<test_string, test_allocator> vec4(10_cap);
      rsl::vector<test_string, test_allocator> vec5 = { test_string("this is a big string"), test_string("this is a big string"), test_string("this is a big string") }; // don't forget that this creates an destroys 3 elements through the initializer list
      rsl::vector<test_string, test_allocator> to_copy1 = { test_string("this is a big string"), test_string("this is a big string"), test_string("this is a big string") };
      rsl::vector<test_string, test_allocator> vec6 = to_copy1;
      rsl::vector<test_string, test_allocator> to_copy2 = { test_string("this is a big string"), test_string("this is a big string"), test_string("this is a big string") };
      rsl::vector<test_string, test_allocator> vec7(to_copy2, test_allocator());
      rsl::vector<test_string, test_allocator> vec8 = { test_string("this is a big string"), test_string("this is a big string"), test_string("this is a big string") };
      rsl::vector<test_string, test_allocator> to_move1 = { test_string("this is a big string"), test_string("this is a big string"), test_string("this is a big string") };
      rsl::vector<test_string, test_allocator> vec9 = rsl::move(to_move1);
      rsl::vector<test_string, test_allocator> to_move2 = { test_string("this is a big string"), test_string("this is a big string"), test_string("this is a big string") };
      rsl::vector<test_string, test_allocator> vec10(rsl::move(to_move2), test_allocator());
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);
  }
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

  {
    {
      using test_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::test::test_allocator>;

      test_allocator::all_reset();

      {
        rsl::vector<test_object, test_allocator> vec;
        rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

        vec = vec2; // none-empty to empty
      }
      {
        rsl::vector<test_object, test_allocator> vec = { 4, 5 };
        rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

        vec2 = vec; // none-empty to none-empty ( smaller vector to bigger vector)
      }
      {
        rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 };
        rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

        vec2 = vec; // none-empty to none-empty ( bigger vector to smaller vector)
      }
      {
        rsl::vector<test_object, test_allocator> vec;
        rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

        vec2 = vec; // empty to none-empty
      }
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

  {
    {
      using test_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::test::test_allocator>;

      test_allocator::all_reset();

      {
        rsl::vector<test_object, test_allocator> vec;
        rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

        vec = rsl::move(vec2); // none-empty to empty
      }

      {
        rsl::vector<test_object, test_allocator> vec = { 4, 5 };
        rsl::vector<test_object, test_allocator> vec2 = { 1, 2, 3 };

        vec2 = rsl::move(vec); // non-empty to none-empty ( smaller vector to bigger vector)
      }

      {
        rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 };
        rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

        vec2 = rsl::move(vec); // none-empty to none-empty ( bigger vector to smaller vector)
      }

      {
        rsl::vector<test_object, test_allocator> vec;
        rsl::vector<test_object, test_allocator> vec2 = { 4, 5 };

        vec2 = rsl::move(vec); // none-empty to empty
      }
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);
  }
}

TEST_CASE("vector misc assignment")
{
  using namespace rsl::test;

  {
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

  using test_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::test::test_allocator>;

  test_allocator::all_reset();

  {
    {
      rsl::vector<test_object, test_allocator> vec;

      vec.assign(10, 2);
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3 };

      vec.assign(10, 2);
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };

      vec.assign(5, 2);
    }
    {
      rsl::vector<test_object, test_allocator> vec;
      rsl::vector<test_object, test_allocator> vec2 = { 1,2,3 };

      vec.assign(vec2.cbegin(), vec2.cend());
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3 };
      rsl::vector<test_object, test_allocator> vec2 = { 1,2,3,4,5,6 };

      vec.assign(vec2.cbegin(), vec2.cend());
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };
      rsl::vector<test_object, test_allocator> vec2 = { 1,2,3 };

      vec.assign(vec2.cbegin(), vec2.cend());
    }
    {
      rsl::vector<test_object, test_allocator> vec;

      vec.assign({ 1,2,3 });
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3 };

      vec.assign({ 1,2,3,4,5,6 });
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };

      vec.assign({ 1,2,3 });
    }
    {
      rsl::vector<test_object, test_allocator> vec;

      vec = { 1,2,3 };
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3 };

      vec = { 1,2,3,4,5,6 };
    }
    {
      rsl::vector<test_object, test_allocator> vec = { 1,2,3,4,5,6,7 };

      vec = { 1,2,3 };
    }
  }

  CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
  CHECK(test_allocator::all_num_bytes_allocated() == 0);
}

TEST_CASE("vector size and capacity")
{
  using namespace rsl::test;

  {
    test_allocator::all_reset();

    rsl::vector<test_object, test_allocator> vec;
    CHECK(vec.size() == 0);
    CHECK(vec.empty());

    test_object::reset();

    test_object obj(1);
    // simple push back
    vec.push_back(obj);

    CHECK(vec.size() == 1);
    CHECK(vec.capacity() >= 1);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_created() == 2);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 1);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    card32 old_num_allocs = vec.get_allocator().num_allocs();
    card32 old_num_frees = vec.get_allocator().num_frees();

    test_object::reset();

    // another push back
    card32 old_cap = vec.capacity();

    vec.push_back(1);

    CHECK(vec.size() == 2);
    CHECK(vec.capacity() >= 2);
    CHECK(vec.get_allocator().num_allocs() >= old_num_allocs);
    CHECK(vec.get_allocator().num_frees() >= old_num_frees);

    if (old_cap == vec.capacity()) // no realocation happened
    {
      CHECK(test_object::num_created() == 2);
      CHECK(test_object::num_dtor_calls() == 1);
      CHECK(test_object::num_move_ctor_calls() == 1);

    }
    else // reallocation happened
    {
      CHECK(test_object::num_created() == 3);
      CHECK(test_object::num_dtor_calls() == 2);
      CHECK(test_object::num_move_ctor_calls() == 2);
    }

    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();
    old_cap = vec.capacity();

    test_object::reset();

    card32 old_size = vec.size();

    // clearing
    vec.clear();

    CHECK(vec.empty());
    CHECK(vec.size() == 0);
    CHECK(vec.capacity() == old_cap);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs);
    CHECK(vec.get_allocator().num_frees() == old_num_frees);
    CHECK(test_object::num_created() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == old_size);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();

    test_object::reset();

    // resizing
    vec.resize(10);
    CHECK(vec.size() == 10);
    CHECK(vec.capacity() >= 10);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs + 1);
    CHECK(vec.get_allocator().num_frees() == old_num_frees + 1);
    CHECK(test_object::num_created() == 10);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();
    old_cap = vec.capacity();

    test_object::reset();

    // resizing with value
    // size was 10 before this, so we're just adding 1 element
    vec.resize(11, 2);

    CHECK(vec[0] == 0);
    CHECK(vec[1] == 0);
    CHECK(vec[2] == 0);
    CHECK(vec[10] == 2);
    CHECK(vec.size() == 11);
    CHECK(vec.capacity() >= old_cap);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs);
    CHECK(vec.get_allocator().num_frees() == old_num_frees);
    CHECK(test_object::num_created() == 2);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_dtor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 1);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();

    test_object::reset();

    // reserving
    vec.reserve(20);

    CHECK(vec.size() == 11);
    CHECK(vec.capacity() == 20);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs + 1);
    CHECK(vec.get_allocator().num_frees() == old_num_frees + 1);
    CHECK(test_object::num_created() == 11);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 11);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 11);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();
    old_cap = vec.capacity();

    test_object::reset();

    // resizing with value
    vec.resize(25, 2);

    CHECK(vec.size() == 25);
    CHECK(vec.capacity() >= old_cap);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs + 1);
    CHECK(vec.get_allocator().num_frees() == old_num_frees + 1);
    CHECK(test_object::num_created() == 26);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_dtor_calls() == 12);
    CHECK(test_object::num_copy_ctor_calls() == 14);
    CHECK(test_object::num_move_ctor_calls() == 11);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();
    old_cap = vec.capacity();

    test_object::reset();

    // reserving to a smaller capacity than size
    vec.reserve(20);

    CHECK(vec.size() == 25);
    CHECK(vec.capacity() == old_cap);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs);
    CHECK(vec.get_allocator().num_frees() == old_num_frees);
    CHECK(test_object::num_created() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();
    old_cap = vec.capacity();

    test_object::reset();

    // popping
    vec.pop_back();

    CHECK(vec.size() == 24);
    CHECK(vec.capacity() == old_cap);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs);
    CHECK(vec.get_allocator().num_frees() == old_num_frees);
    CHECK(test_object::num_created() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);

    old_num_allocs = vec.get_allocator().num_allocs();
    old_num_frees = vec.get_allocator().num_frees();
    old_cap = vec.capacity();

    test_object::reset();

    // more popping
    vec.pop_back();

    CHECK(vec.size() == 23);
    CHECK(vec.capacity() == old_cap);
    CHECK(vec.get_allocator().num_allocs() == old_num_allocs);
    CHECK(vec.get_allocator().num_frees() == old_num_frees);
    CHECK(test_object::num_created() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  {
    using test_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::test::test_allocator>;

    test_allocator::all_reset();

    {
      rsl::vector<test_string, test_allocator> vec;

      vec.push_back(test_string("this is a very big string"));
      vec.push_back(test_string("this is a very big string"));
      vec.clear();
      vec.resize(10);
      vec.resize(11, test_string("this is another big string"));
      vec.reserve(20);
      vec.resize(25, test_string("this is another big string"));
      vec.reserve(20);
      vec.pop_back();
      vec.pop_back();
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);
  }
}

TEST_CASE("vector element access")
{
  {
    rsl::vector<int> vec;

    vec.push_back(1);
    CHECK(vec[0] == 1);
    CHECK(vec.at(0) == 1);
    CHECK(vec.front() == 1);
    CHECK(*vec.begin() == 1);
    CHECK(*vec.cbegin() == 1);
    CHECK(*vec.rbegin() == 1);
    CHECK(*vec.crbegin() == 1);
    CHECK(vec.back() == 1);
    CHECK(*--vec.end() == 1);
    CHECK(*--vec.cend() == 1);
    CHECK(*--vec.rend() == 1);
    CHECK(*--vec.crend() == 1);

    vec.push_back(2);
    CHECK(vec[0] == 1);
    CHECK(vec.at(0) == 1);
    CHECK(vec.front() == 1);
    CHECK(*vec.begin() == 1);
    CHECK(*vec.cbegin() == 1);
    CHECK(*vec.rbegin() == 2);
    CHECK(*vec.crbegin() == 2);
    CHECK(vec[1] == 2);
    CHECK(vec.at(1) == 2);
    CHECK(vec.back() == 2);
    CHECK(*--vec.end() == 2);
    CHECK(*--vec.cend() == 2);
    CHECK(*--vec.rend() == 1);
    CHECK(*--vec.crend() == 1);

    vec.push_back(3);
    CHECK(vec[0] == 1);
    CHECK(vec.at(0) == 1);
    CHECK(vec.front() == 1);
    CHECK(*vec.begin() == 1);
    CHECK(*vec.cbegin() == 1);
    CHECK(*vec.rbegin() == 3);
    CHECK(*vec.crbegin() == 3);
    CHECK(vec[1] == 2);
    CHECK(vec.at(1) == 2);
    CHECK(vec[2] == 3);
    CHECK(vec.at(2) == 3);
    CHECK(vec.back() == 3);
    CHECK(*--vec.end() == 3);
    CHECK(*--vec.cend() == 3);
    CHECK(*--vec.rend() == 1);
    CHECK(*--vec.crend() == 1);
  }

  {
    const rsl::vector<int> vec = { 1, 2, 3 };

    CHECK(vec[0] == 1);
    CHECK(vec.at(0) == 1);
    CHECK(vec.front() == 1);
    CHECK(*vec.begin() == 1);
    CHECK(*vec.cbegin() == 1);
    CHECK(*vec.rbegin() == 3);
    CHECK(*vec.crbegin() == 3);
    CHECK(vec[1] == 2);
    CHECK(vec.at(1) == 2);
    CHECK(vec[2] == 3);
    CHECK(vec.at(2) == 3);
    CHECK(vec.back() == 3);
    CHECK(*--vec.end() == 3);
    CHECK(*--vec.cend() == 3);
    CHECK(*--vec.rend() == 1);
    CHECK(*--vec.crend() == 1);
  }
}

TEST_CASE("vector insertion")
{
  using namespace rsl::test;

  {
    test_allocator::all_reset();

    // insert by const value, empty vec
    {
      rsl::vector<test_object, test_allocator> vec;

      test_object x = 1;

      test_object::reset();

      vec.insert(vec.cbegin(), x); // insert by const value

      CHECK(vec[0] == 1);
      CHECK(vec.size() == 1);
      CHECK(vec.capacity() >= 1);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 1);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 0);
      CHECK(test_object::num_copy_ctor_calls() == 1);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // insert by const value, non-empty vec
    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2 };

      test_object x = 3;

      test_object::reset();

      card32 old_size = vec.size();
      card32 old_cap = vec.capacity();

      vec.insert(vec.cbegin() + 1, x); // insert by const value

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 3);
      CHECK(vec[2] == 2);
      CHECK(vec.size() == 3);
      CHECK(vec.capacity() >= 3);

      if (old_cap == vec.capacity()) // no reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 1);
        CHECK(vec.get_allocator().num_frees() == 0);
        CHECK(test_object::num_created() == 1);
        CHECK(test_object::num_dtor_calls() == 0);
        CHECK(test_object::num_move_ctor_calls() == 0);
      }
      else // reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 2);
        CHECK(vec.get_allocator().num_frees() == 1);
        CHECK(test_object::num_created() == 3);
        CHECK(test_object::num_dtor_calls() == old_size);
        CHECK(test_object::num_move_ctor_calls() == old_size);
      }

      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_copy_ctor_calls() == 1);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // // insert by rvalue, empty vec
    {
      rsl::vector<test_object, test_allocator> vec;

      test_object::reset();

      vec.insert(vec.cbegin(), test_object(2));

      CHECK(vec[0] == 2);
      CHECK(vec.size() == 1);
      CHECK(vec.capacity() >= 1);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 2);
      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_dtor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 1);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);

    }

    // // insert by rvalue, non-empty vec
    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2 };

      test_object::reset();

      card32 old_cap = vec.capacity();
      vec.insert(vec.cbegin() + 1, test_object(3)); // insert by rvalue

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 3);
      CHECK(vec[2] == 2);
      CHECK(vec.size() == 3);
      CHECK(vec.capacity() >= 3);
      CHECK(vec.get_allocator().num_allocs() == 2);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));

      if (old_cap == vec.capacity()) // no reallocation happened
      {
        CHECK(vec.get_allocator().num_frees() == 0);
        CHECK(test_object::num_created() == 2);
        CHECK(test_object::num_dtor_calls() == 1);
        CHECK(test_object::num_move_ctor_calls() == 1);
      }
      else // reallocation happened
      {
        CHECK(vec.get_allocator().num_frees() == 1);
        CHECK(test_object::num_created() == 4);
        CHECK(test_object::num_dtor_calls() == 3);
        CHECK(test_object::num_move_ctor_calls() == 3);
      }

      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);

    }

    // insert by number of elements, empty vec
    {
      rsl::vector<test_object, test_allocator> vec;

      test_object::reset();

      vec.insert(vec.cbegin(), 2, test_object(10));

      CHECK(vec[0] == 10);
      CHECK(vec[1] == 10);
      CHECK(vec.size() == 2);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 3);
      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_dtor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 2);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // insert by number of elements, non-empty vec
    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2 };

      test_object::reset();

      card32 old_cap = vec.capacity();
      vec.insert(vec.cbegin() + 1, 2, test_object(10));

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 10);
      CHECK(vec[2] == 10);
      CHECK(vec[3] == 2);
      CHECK(vec.size() == 4);

      if (old_cap == vec.capacity()) // no reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 1);
        CHECK(vec.get_allocator().num_frees() == 0);
        CHECK(test_object::num_created() == 3);
        CHECK(test_object::num_dtor_calls() == 1);
        CHECK(test_object::num_move_ctor_calls() == 0);
      }
      else // reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 2);
        CHECK(vec.get_allocator().num_frees() == 1);
        CHECK(test_object::num_created() == 5);
        CHECK(test_object::num_dtor_calls() == 3);
        CHECK(test_object::num_move_ctor_calls() == 2);
      }

      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 2);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // insert from iterators, empty vec
    {
      rsl::vector<test_object, test_allocator> vec;
      rsl::vector<test_object, test_allocator> to_insert = { 1,2 };

      test_object::reset();

      vec.insert(vec.cbegin(), to_insert.cbegin(), to_insert.cend());

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 2);
      CHECK(vec.size() == to_insert.size());
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 2);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 0);
      CHECK(test_object::num_copy_ctor_calls() == 2);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // insert from iterators, non-empty vec
    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2 };
      rsl::vector<test_object, test_allocator> to_insert = { 1,2 };

      test_object::reset();

      card32 old_size = vec.size();
      card32 old_cap = vec.capacity();
      vec.insert(vec.cbegin() + 1, to_insert.cbegin(), to_insert.cend());

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 1);
      CHECK(vec[2] == 2);
      CHECK(vec[3] == 2);
      CHECK(vec.size() == old_size + to_insert.size());

      if (old_cap == vec.capacity()) // no reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 1);
        CHECK(vec.get_allocator().num_frees() == 0);
        CHECK(test_object::num_created() == 2);
        CHECK(test_object::num_dtor_calls() == 0);
        CHECK(test_object::num_move_ctor_calls() == 0);
      }
      else // reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 2);
        CHECK(vec.get_allocator().num_frees() == 1);
        CHECK(test_object::num_created() == 4);
        CHECK(test_object::num_dtor_calls() == 2);
        CHECK(test_object::num_move_ctor_calls() == 2);
      }

      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_copy_ctor_calls() == 2);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // insert from initializer list, empty vec
    {
      rsl::vector<test_object, test_allocator> vec;

      test_object::reset();

      vec.insert(vec.cbegin(), { 1,2 });

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 2);
      CHECK(vec.size() == 2);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 4);
      CHECK(test_object::num_ctor_calls() == 2);
      CHECK(test_object::num_dtor_calls() == 2);
      CHECK(test_object::num_copy_ctor_calls() == 2);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // insert from initializer list, non-empty vec
    {
      rsl::vector<test_object, test_allocator> vec{ 1, 2 };

      test_object::reset();

      card32 old_size = vec.size();
      card32 old_cap = vec.capacity();
      vec.insert(vec.cbegin() + 1, { 1,2 });

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 1);
      CHECK(vec[2] == 2);
      CHECK(vec[3] == 2);
      CHECK(vec.size() == old_size + 2);

      if (old_cap == vec.capacity()) // no reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 1);
        CHECK(vec.get_allocator().num_frees() == 0);
        CHECK(test_object::num_created() == 2);
        CHECK(test_object::num_dtor_calls() == 0);
        CHECK(test_object::num_move_ctor_calls() == 0);
      }
      else // reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 2);
        CHECK(vec.get_allocator().num_frees() == 1);
        CHECK(test_object::num_created() == 6);
        CHECK(test_object::num_dtor_calls() == 4);
        CHECK(test_object::num_move_ctor_calls() == 2);
      }

      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(test_object::num_ctor_calls() == 2);
      CHECK(test_object::num_copy_ctor_calls() == 2);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // emplace, empty vec
    {
      rsl::vector<test_object, test_allocator> vec;

      test_object::reset();

      vec.emplace(vec.cbegin(), 1);

      CHECK(vec[0] == 1);
      CHECK(vec.size() == 1);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 1);
      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_dtor_calls() == 0);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // emplace, non-empty vec
    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2 };

      test_object::reset();

      card32 old_cap = vec.capacity();
      vec.emplace(vec.cbegin() + 1, 3);

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 3);
      CHECK(vec[2] == 2);
      CHECK(vec.size() == 3);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));

      if (old_cap == vec.capacity()) // no reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 1);
        CHECK(vec.get_allocator().num_frees() == 0);
        CHECK(test_object::num_created() == 1);
        CHECK(test_object::num_dtor_calls() == 0);
        CHECK(test_object::num_move_ctor_calls() == 0);
      }
      else // reallocation happened
      {
        CHECK(vec.get_allocator().num_allocs() == 2);
        CHECK(vec.get_allocator().num_frees() == 1);
        CHECK(test_object::num_created() == 3);
        CHECK(test_object::num_dtor_calls() == 2);
        CHECK(test_object::num_move_ctor_calls() == 2);
      }

      CHECK(test_object::num_ctor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 0);
    }

    // erase single point
    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2 };

      test_object::reset();

      vec.erase(vec.cbegin());

      CHECK(vec[0] == 2);
      CHECK(vec.size() == 1);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 1);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 1);
    }

    // erase range
    {
      rsl::vector<test_object, test_allocator> vec = { 1, 2, 3, 4 };

      test_object::reset();

      vec.erase(vec.cbegin() + 1, vec.cbegin() + 3);

      CHECK(vec[0] == 1);
      CHECK(vec[1] == 4);
      CHECK(vec.size() == 2);
      CHECK(vec.get_allocator().num_allocs() == 1);
      CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
      CHECK(vec.get_allocator().num_frees() == 0);
      CHECK(test_object::num_created() == 0);
      CHECK(test_object::num_ctor_calls() == 0);
      CHECK(test_object::num_dtor_calls() == 2);
      CHECK(test_object::num_copy_ctor_calls() == 0);
      CHECK(test_object::num_move_ctor_calls() == 0);
      CHECK(test_object::num_copy_assignment_calls() == 0);
      CHECK(test_object::num_move_assignment_calls() == 1);
    }
  }

  {
    using test_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::test::test_allocator>;

    test_allocator::all_reset();

    {
      {
        rsl::vector<test_string, test_allocator> vec;
        test_string x("this is a very big string");

        vec.insert(vec.cbegin(), x); // insert by const value
      }

      {
        rsl::vector<test_string, test_allocator> vec = { test_string("this is a very big string"), test_string("this is a very big string") };
        test_string x("this is a very big string");

        vec.insert(vec.cbegin() + 1, x); // insert by const value
      }

      {
        rsl::vector<test_string, test_allocator> vec;
        vec.insert(vec.cbegin(), test_string("this is another very big string")); // insert by rvalue
      }

      {
        rsl::vector<test_string, test_allocator> vec = { test_string("this is a very big string"), test_string("this is a very big string") };
        vec.insert(vec.cbegin() + 1, test_string("this is another very big string")); // insert by rvalue
      }

      {
        rsl::vector<test_string, test_allocator> vec;
        vec.insert(vec.cbegin(), 2, test_string("this is another very big string"));
      }

      {
        rsl::vector<test_string, test_allocator> vec = { test_string("this is a very big string"), test_string("this is a very big string") };
        vec.insert(vec.cbegin() + 1, 2, test_string("this is another very big string"));
      }

      {
        rsl::vector<test_string, test_allocator> vec;
        rsl::vector<test_string, test_allocator> to_insert = { test_string("this is a very big string"), test_string("this is a very big string") };
        vec.insert(vec.cbegin(), to_insert.cbegin(), to_insert.cend());
      }

      {
        rsl::vector<test_string, test_allocator> vec = { test_string("this is a very big string"), test_string("this is a very big string") };
        rsl::vector<test_string, test_allocator> to_insert = { test_string("this is a very big string"), test_string("this is a very big string") };
        vec.insert(vec.cbegin() + 1, to_insert.cbegin(), to_insert.cend());
      }

      {
        rsl::vector<test_string, test_allocator> vec;
        vec.insert(vec.cbegin(), { test_string("this is a very big string"), test_string("this is a very big string") });
      }

      {
        rsl::vector<test_string, test_allocator> vec{ test_string("this is a very big string"), test_string("this is a very big string") };
        vec.insert(vec.cbegin() + 1, { test_string("this is a very big string"), test_string("this is a very big string") });
      }

      {
        rsl::vector<test_string, test_allocator> vec;
        vec.emplace(vec.cbegin(), "this is a very big string");
      }

      {
        rsl::vector<test_string, test_allocator> vec = { test_string("this is a very big string"), test_string("this is a very big string") };
        vec.emplace(vec.cbegin() + 1, "this is a very big string");
      }

      {
        rsl::vector<test_string, test_allocator> vec = { test_string("this is a very big string"), test_string("this is a very big string") };
        vec.erase(vec.cbegin());
      }

      {
        rsl::vector<test_string, test_allocator> vec = { test_string("this is a very big string"), test_string("this is a very big string"), test_string("this is a very big string"), test_string("this is a very big string") };
        vec.erase(vec.cbegin() + 1, vec.cbegin() + 3);
      }
    }

    CHECK(test_allocator::all_num_allocs() == test_allocator::all_num_frees());
    CHECK(test_allocator::all_num_bytes_allocated() == 0);
  }
}

TEST_CASE("vector bug with inseration")
{
  rsl::vector<rsl::string> vec1;
  vec1.emplace_back("some text going in to heap");
  vec1.emplace_back("some text going in to heap");
  vec1.emplace_back("some text going in to heap");
  vec1.emplace_back("some text going in to heap");
  vec1.emplace_back("some text going in to heap");
  vec1.emplace_back("some text going in to heap");
  vec1.emplace_back("some text going in to heap");
  vec1.emplace_back("some text going in to heap");

  rsl::vector<rsl::string> vec2;
  vec2.emplace_back("some text going in to heap");
  vec2.emplace_back("some text going in to heap");
  vec2.emplace_back("some text going in to heap");
  vec2.emplace_back("some text going in to heap");

  vec1.insert(vec1.cend(), vec2.cbegin(), vec2.cend());
}
