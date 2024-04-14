// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_unordered_map.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/unordered_map.h"

#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_object.h"

#include "rex_std/type_traits.h"

#include <type_traits>

TEST_CASE("unordered_map construction")
{
  using namespace rsl::test;

  using hash_table = rsl::unordered_map<int, test_object, rsl::hash<int>, rsl::equal_to<int>, test_allocator>;

  // unordered_map()
  {
    card32 num_allocs = test_allocator::all_num_allocs();
    card32 num_allocated_bytes = test_allocator::all_num_bytes_allocated();
    card32 num_frees = test_allocator::all_num_frees();

    const hash_table map;

    CHECK(map.empty());
    CHECK(map.size() == 0);
    CHECK(map.bucket_count() == 1);
    CHECK(map.load_factor() == 0.0f);

    CHECK(test_allocator::all_num_allocs() == num_allocs + 1);
    CHECK(test_allocator::all_num_bytes_allocated() == num_allocated_bytes + 2 * sizeof(void*));
    CHECK(test_allocator::all_num_frees() == num_frees);
  }
  // unordered_map(size_type bucketCount)
  {
    card32 num_allocs = test_allocator::all_num_allocs();
    card32 num_allocated_bytes = test_allocator::all_num_bytes_allocated();
    card32 num_frees = test_allocator::all_num_frees();

    const hash_table map(2_size);

    CHECK(map.size() == 0);
    CHECK(map.bucket_count() == 2);
    CHECK(map.load_factor() == 0.0f);
    CHECK(map.bucket_count() > 0);

    CHECK(test_allocator::all_num_allocs() >= num_allocs);
    CHECK(test_allocator::all_num_bytes_allocated() >= num_allocated_bytes);
    CHECK(test_allocator::all_num_frees() == num_frees);
  }
  // unordered_map(initializer_list)
  {
    card32 num_allocs = test_allocator::all_num_allocs();
    card32 num_allocated_bytes = test_allocator::all_num_bytes_allocated();
    card32 num_frees = test_allocator::all_num_frees();

    const hash_table map = { {0, 0}, {1, 1} };

    CHECK(map.size() == 2);
    CHECK(map.bucket_count() > 0);
    CHECK(map.load_factor() > 0.0f);
    CHECK(map.bucket_count() > 0);

    CHECK(test_allocator::all_num_allocs() >= num_allocs);
    CHECK(test_allocator::all_num_bytes_allocated() >= num_allocated_bytes);
    CHECK(test_allocator::all_num_frees() == num_frees);
  }
}

TEST_CASE("unordered_map element access")
{
  using namespace rsl::test;
  using hash_table = rsl::unordered_map<int, test_object, rsl::hash<int>, rsl::equal_to<int>, test_allocator>;

  hash_table map   = {{0, 10}, {1, 11}};

  CHECK(map[0] == 10);
  CHECK(map[1] == 11);
  CHECK(map[2] == 0);

  card32 num_allocs = map.get_allocator().num_allocs();
  card32 num_bytes_allocated = map.get_allocator().num_bytes_allocated();
  card32 num_frees = map.get_allocator().num_frees();

  CHECK(map.at(0) == 10);
  CHECK(map.at(1) == 11);

  CHECK(map.count(0) == 1);
  CHECK(map.count(1) == 1);
  CHECK(map.count(2) == 1);
  CHECK(map.count(3) == 0);

  CHECK(map.find(0) != map.cend());
  CHECK(map.find(1) != map.cend());
  CHECK(map.find(2) != map.cend());
  CHECK(map.find(3) == map.cend());

  CHECK(map.get_allocator().num_allocs() == num_allocs);
  CHECK(map.get_allocator().num_bytes_allocated() == num_bytes_allocated);
  CHECK(map.get_allocator().num_frees() == num_frees);
}

TEST_CASE("unordered_map load factor")
{
  using namespace rsl::test;
  using hash_table = rsl::unordered_map<int, test_object, rsl::hash<int>, rsl::equal_to<int>, test_allocator>;

  hash_table map;
  map.set_max_load_factor(0.5f);

  map.insert({ 0, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 1, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 2, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 3, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 4, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 5, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 6, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 7, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 8, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 9, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 10, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 11, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 12, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 13, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
  map.insert({ 14, 0 });
  CHECK(map.load_factor() <= map.get_max_load_factor());
}