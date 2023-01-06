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
    CHECK(vec.empty());
    CHECK(vec.size() == 0); // NOLINT
    CHECK(vec.capacity() == 0);
    CHECK(vec.get_allocator().num_allocs() == 0);
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(vec.get_allocator().num_bytes_allocated() == 0);
    CHECK(test_object::num_alive() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    const rsl::vector<test_object, test_allocator> vec(10_size);
    CHECK(vec.size() == 10);
    CHECK(vec.capacity() == 10);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_alive() == 10);
    CHECK(test_object::num_ctor_calls() == 10);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    const rsl::vector<test_object, test_allocator> vec(10_cap);
    CHECK(vec.size() == 0);
    CHECK(vec.capacity() == 10);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_alive() == 0);
    CHECK(test_object::num_ctor_calls() == 0);
    CHECK(test_object::num_dtor_calls() == 0);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 }; // don't forget that this creates an destroys 3 elements through the initializer list
    CHECK(vec.size() == 3);
    CHECK(vec.capacity() == 3);
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_alive() == 3);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

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
    CHECK(test_object::num_alive() == 6);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 6);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    rsl::vector<test_object, test_allocator> vec = { 1, 2, 3 };

    vec.clear();
    CHECK(vec.empty());
    CHECK(vec.size() == 0);
    CHECK(vec.capacity() == 3);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_alive() == 0);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 6);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }

  {
    rsl::scopeguard guard = []() { test_object::reset(); };

    rsl::vector<test_object, test_allocator> to_move = { 1, 2, 3 };
    const rsl::vector<test_object, test_allocator> vec = rsl::move(to_move);
    CHECK(to_move.empty());
    CHECK(to_move.size() == 0);
    CHECK(to_move.get_allocator().num_allocs() == 0);
    CHECK(to_move.get_allocator().num_bytes_allocated() == 0);
    CHECK(to_move.get_allocator().num_frees() == 0);
    CHECK(vec.size() == 3);
    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
    CHECK(vec.get_allocator().num_allocs() == 1);
    CHECK(vec.get_allocator().num_bytes_allocated() == vec.capacity() * sizeof(decltype(vec)::value_type));
    CHECK(vec.get_allocator().num_frees() == 0);
    CHECK(test_object::num_alive() == 3);
    CHECK(test_object::num_ctor_calls() == 3);
    CHECK(test_object::num_dtor_calls() == 3);
    CHECK(test_object::num_copy_ctor_calls() == 3);
    CHECK(test_object::num_move_ctor_calls() == 0);
    CHECK(test_object::num_copy_assignment_calls() == 0);
    CHECK(test_object::num_move_assignment_calls() == 0);
  }
}

TEST_CASE("vector assignment")
{
  rsl::vector<int> vec;
  rsl::vector<int> vec2 = {1, 2, 3};
  rsl::vector<int> vec3 = {4, 5};

  vec = vec2;
  CHECK(vec.size() == vec2.size());
  CHECK(vec.size() == 3);

  vec2 = vec3;
  CHECK(vec2.size() == vec3.size());
  CHECK(vec2.size() == 2);

  vec3 = vec;
  CHECK(vec3.size() == vec.size());
  CHECK(vec3.size() == 3);
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

  vec.reserve(10);
  CHECK(vec.size() == 5);

  vec.pop_back();
  CHECK(vec.size() == 4);

  vec.pop_back();
  CHECK(vec.size() == 3);
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

TEST_CASE("vector non trivial type")
{
  class non_trivial_type
  {
  public:
    non_trivial_type() {}
    virtual ~non_trivial_type() {}
  };

  rsl::vector<non_trivial_type> vec;
  CHECK(vec.size() == 0);

  vec.emplace_back();
  CHECK(vec.size() == 1);

  vec.clear();
  CHECK(vec.size() == 0);
}

// NOLINTEND
