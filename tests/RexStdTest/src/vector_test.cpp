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
  test_object::reset();

  {
    rsl::scopeguard guard = []() { test_object::reset(); };
    const rsl::vector<test_object, test_allocator> vec;
    REQUIRE(vec.empty());
    REQUIRE(vec.size() == 0); // NOLINT
    REQUIRE(vec.capacity() == 0);
    REQUIRE(vec.get_allocator().num_allocs() == 0);
    REQUIRE(vec.get_allocator().num_frees() == 0);
    REQUIRE(vec.get_allocator().num_bytes_allocated() == 0);
    REQUIRE(test_object::num_alive() == 0);
    REQUIRE(test_object::num_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_ctor_calls() == 0);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    const rsl::vector<test_object, test_allocator> vec(10_size);
    REQUIRE(vec.size() == 10);
    REQUIRE(vec.capacity() == 10);
    REQUIRE(vec.get_allocator().num_allocs() == 1);
    REQUIRE(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    REQUIRE(vec.get_allocator().num_frees() == 0);
    REQUIRE(test_object::num_alive() == 10);
    REQUIRE(test_object::num_ctor_calls() == 10);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_ctor_calls() == 0);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    const rsl::vector<test_object, test_allocator> vec(10_cap);
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 10);
    REQUIRE(vec.get_allocator().num_allocs() == 1);
    REQUIRE(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    REQUIRE(vec.get_allocator().num_frees() == 0);
    REQUIRE(test_object::num_alive() == 0);
    REQUIRE(test_object::num_ctor_calls() == 0);
    REQUIRE(test_object::num_dtor_calls() == 0);
    REQUIRE(test_object::num_copy_ctor_calls() == 0);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 }; // don't forget that this creates an destroys 3 elements through the initializer list
    REQUIRE(vec.size() == 3);
    REQUIRE(vec.capacity() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec.get_allocator().num_allocs() == 1);
    REQUIRE(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    REQUIRE(vec.get_allocator().num_frees() == 0);
    REQUIRE(test_object::num_alive() == 3);
    REQUIRE(test_object::num_ctor_calls() == 3);
    REQUIRE(test_object::num_dtor_calls() == 3);
    REQUIRE(test_object::num_copy_ctor_calls() == 3);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    rsl::vector<test_object, test_allocator> to_copy = { 1, 2, 3 };
    rsl::vector<test_object, test_allocator> vec = to_copy;
    REQUIRE(to_copy.size() == 3);
    REQUIRE(to_copy.capacity() == 3);
    REQUIRE(to_copy[0] == 1);
    REQUIRE(to_copy[1] == 2);
    REQUIRE(to_copy[2] == 3);
    REQUIRE(to_copy.get_allocator().num_allocs() == 1);
    REQUIRE(to_copy.get_allocator().num_bytes_allocated() == to_copy.capacity() * sizeof(decltype(to_copy)::value_type));
    REQUIRE(to_copy.get_allocator().num_frees() == 0);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec.capacity() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec.get_allocator().num_allocs() == 1);
    REQUIRE(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(to_copy)::value_type));
    REQUIRE(vec.get_allocator().num_frees() == 0);
    REQUIRE(test_object::num_alive() == 6);
    REQUIRE(test_object::num_ctor_calls() == 3);
    REQUIRE(test_object::num_dtor_calls() == 3);
    REQUIRE(test_object::num_copy_ctor_calls() == 6);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 };

    vec.clear();
    REQUIRE(vec.empty());
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 3);
    REQUIRE(vec.get_allocator().num_allocs() == 1);
    REQUIRE(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    REQUIRE(vec.get_allocator().num_frees() == 0);
    REQUIRE(test_object::num_alive() == 0);
    REQUIRE(test_object::num_ctor_calls() == 3);
    REQUIRE(test_object::num_dtor_calls() == 6);
    REQUIRE(test_object::num_copy_ctor_calls() == 3);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    rsl::vector<test_object, test_allocator> to_move = { 1, 2, 3 };
    const rsl::vector<test_object, test_allocator> vec = rsl::move(to_move);
    REQUIRE(to_move.empty());
    REQUIRE(to_move.size() == 0);
    REQUIRE(to_move.get_allocator().num_allocs() == 0);
    REQUIRE(to_move.get_allocator().num_bytes_allocated() == 0);
    REQUIRE(to_move.get_allocator().num_frees() == 0);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec.get_allocator().num_allocs() == 1);
    REQUIRE(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    REQUIRE(vec.get_allocator().num_frees() == 0);
    REQUIRE(test_object::num_alive() == 3);
    REQUIRE(test_object::num_ctor_calls() == 3);
    REQUIRE(test_object::num_dtor_calls() == 3);
    REQUIRE(test_object::num_copy_ctor_calls() == 3);
    REQUIRE(test_object::num_move_ctor_calls() == 0);
    REQUIRE(test_object::num_copy_assignment_calls() == 0);
    REQUIRE(test_object::num_move_assignment_calls() == 0);
  }
}

TEST_CASE("vector assignment")
{
  rsl::vector<int> vec;
  rsl::vector<int> vec2 = {1, 2, 3};
  rsl::vector<int> vec3 = {4, 5};

  vec = vec2;
  REQUIRE(vec.size() == vec2.size());
  REQUIRE(vec.size() == 3);

  vec2 = vec3;
  REQUIRE(vec2.size() == vec3.size());
  REQUIRE(vec2.size() == 2);

  vec3 = vec;
  REQUIRE(vec3.size() == vec.size());
  REQUIRE(vec3.size() == 3);
}

TEST_CASE("vector size")
{
  rsl::vector<int> vec;
  REQUIRE(vec.size() == 0); // NOLINT
  REQUIRE(vec.empty());

  vec.push_back(1);
  REQUIRE(vec.size() == 1);

  vec.push_back(1);
  REQUIRE(vec.size() == 2);

  vec.clear();
  REQUIRE(vec.empty());
  REQUIRE(vec.size() == 0); // NOLINT

  vec.resize(10);
  REQUIRE(vec.size() == 10);

  vec.resize(5);
  REQUIRE(vec.size() == 5);

  vec.reserve(10);
  REQUIRE(vec.size() == 5);

  vec.pop_back();
  REQUIRE(vec.size() == 4);

  vec.pop_back();
  REQUIRE(vec.size() == 3);
}

TEST_CASE("vector element access")
{
  rsl::vector<int> vec;

  vec.push_back(1);
  REQUIRE(vec[0] == 1);
  REQUIRE(vec.front() == 1);
  REQUIRE(*vec.begin() == 1);
  REQUIRE(vec.back() == 1);
  REQUIRE(*--vec.end() == 1);

  vec.push_back(2);
  REQUIRE(vec[0] == 1);
  REQUIRE(vec.front() == 1);
  REQUIRE(*vec.begin() == 1);
  REQUIRE(vec[1] == 2);
  REQUIRE(vec.back() == 2);
  REQUIRE(*--vec.end() == 2);

  vec.push_back(3);
  REQUIRE(vec[0] == 1);
  REQUIRE(vec.front() == 1);
  REQUIRE(*vec.begin() == 1);
  REQUIRE(vec[1] == 2);
  REQUIRE(vec[2] == 3);
  REQUIRE(vec.back() == 3);
  REQUIRE(*--vec.end() == 3);
}

TEST_CASE("vector insertion")
{
  rsl::vector<int> vec;

  vec.insert(vec.cend(), 1);
  REQUIRE(vec[0] == 1);
  REQUIRE(vec.size() == 1);
  REQUIRE(vec.capacity() >= 1);

  vec.insert(vec.cbegin(), 2);
  REQUIRE(vec[0] == 2);
  REQUIRE(vec[1] == 1);
  REQUIRE(vec.size() == 2);
  REQUIRE(vec.capacity() >= 2);

  vec.reserve(100);
  vec.insert(vec.cbegin(), 2);
  REQUIRE(vec[0] == 2);
  REQUIRE(vec[1] == 2);
  REQUIRE(vec[2] == 1);
  REQUIRE(vec.size() == 3);
  REQUIRE(vec.capacity() == 100);
}

TEST_CASE("vector non trivial type")
{
  class non_trivial_type
  {
  public:
    non_trivial_type() {}
    virtual ~non_trivial_type() {}
  };

  rsl::vector<non_trivial_type> vec;
  REQUIRE(vec.size() == 0);

  vec.emplace_back();
  REQUIRE(vec.size() == 1);

  vec.clear();
  REQUIRE(vec.size() == 0);
}

// NOLINTEND
