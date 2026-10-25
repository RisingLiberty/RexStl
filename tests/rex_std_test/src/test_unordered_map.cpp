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
#include "rex_std/string.h"

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

TEST_CASE("unordered_map insertion")
{
  using map_type = rsl::unordered_map<int, int>;

  // insert
  {
    map_type map;
    rsl::key_value<const int, int> kv1(1, 10);
    auto res = map.insert(kv1);
    CHECK(res.emplace_successful);
    CHECK(res.inserted_element->key == 1);
    CHECK(res.inserted_element->value == 10);

    // inserting an existing key doesn't overwrite the value
    rsl::key_value<const int, int> kv1_dup(1, 20);
    res = map.insert(kv1_dup);
    CHECK(!res.emplace_successful);
    CHECK(res.inserted_element->value == 10);
    CHECK(map.size() == 1);

    // a braced list goes through the initializer list overload
    map.insert({2, 20});
    CHECK(map.size() == 2);
    CHECK(map.contains(2));
  }

  // emplace
  {
    map_type map;
    auto res = map.emplace(1, 10);
    CHECK(res.emplace_successful);
    CHECK(map.at(1) == 10);

    res = map.emplace(1, 20);
    CHECK(!res.emplace_successful);
    CHECK(map.at(1) == 10);
  }

  // try_emplace
  {
    map_type map;
    auto res = map.try_emplace(1, 10);
    CHECK(res.emplace_successful);
    CHECK(map.at(1) == 10);

    res = map.try_emplace(1, 20);
    CHECK(!res.emplace_successful);
    CHECK(map.at(1) == 10);
  }

  // operator[] inserts a default value
  {
    map_type map;
    map[5] = 50;
    CHECK(map.size() == 1);
    CHECK(map.at(5) == 50);
    map[5] += 1;
    CHECK(map.at(5) == 51);
  }
}

TEST_CASE("unordered_map erase")
{
  using map_type = rsl::unordered_map<int, int>;

  map_type map;
  for(int i = 0; i < 10; ++i)
  {
    map.emplace(i, i * 10);
  }

  CHECK(map.erase(5) == 1);
  CHECK(map.size() == 9);
  CHECK(!map.contains(5));
  CHECK(map.erase(5) == 0);
  CHECK(map.erase(100) == 0);
  CHECK(map.size() == 9);

  for(int i = 0; i < 10; ++i)
  {
    if(i != 5)
    {
      CHECK(map.at(i) == i * 10);
    }
  }

  map.clear();
  CHECK(map.empty());
  CHECK(map.begin() == map.end());

  // the map is usable after being cleared
  map.emplace(1, 1);
  CHECK(map.size() == 1);
}

TEST_CASE("unordered_map iteration")
{
  using map_type = rsl::unordered_map<int, int>;

  map_type map;
  for(int i = 0; i < 20; ++i)
  {
    map.emplace(i, i * 2);
  }

  // every element is visited exactly once
  int visited[20] = {};
  card32 count    = 0;
  for(auto& kv : map)
  {
    REQUIRE(kv.key >= 0);
    REQUIRE(kv.key < 20);
    CHECK(kv.value == kv.key * 2);
    ++visited[kv.key];
    ++count;
  }
  CHECK(count == 20);
  for(int v : visited)
  {
    CHECK(v == 1);
  }

  // values can be modified through iterators
  for(auto& kv : map)
  {
    kv.value = 0;
  }
  for(int i = 0; i < 20; ++i)
  {
    CHECK(map.at(i) == 0);
  }
}

TEST_CASE("unordered_map copy and move")
{
  using map_type = rsl::unordered_map<int, int>;

  map_type map;
  for(int i = 0; i < 5; ++i)
  {
    map.emplace(i, i);
  }

  // copy construction
  map_type copy(map);
  CHECK(copy.size() == 5);
  copy[0] = 100;
  CHECK(map.at(0) == 0);

  // move construction
  map_type moved(rsl::move(copy));
  CHECK(moved.size() == 5);
  CHECK(moved.at(0) == 100);

  // copy assignment
  map_type copy_assigned;
  copy_assigned.emplace(50, 50);
  copy_assigned = map;
  CHECK(copy_assigned.size() == 5);
  CHECK(!copy_assigned.contains(50));
  CHECK(copy_assigned.contains(4));

  // move assignment
  map_type move_assigned;
  move_assigned.emplace(50, 50);
  move_assigned = rsl::move(moved);
  CHECK(move_assigned.size() == 5);
  CHECK(!move_assigned.contains(50));
  CHECK(move_assigned.at(0) == 100);

  // swap
  map_type other;
  other.emplace(7, 7);
  other.swap(move_assigned);
  CHECK(other.size() == 5);
  CHECK(move_assigned.size() == 1);
  CHECK(move_assigned.at(7) == 7);
}

TEST_CASE("unordered_map with string keys")
{
  rsl::unordered_map<rsl::string, int> map;
  map.emplace(rsl::string("one"), 1);
  map.emplace(rsl::string("two"), 2);
  map[rsl::string("three")] = 3;

  CHECK(map.size() == 3);
  CHECK(map.at(rsl::string("one")) == 1);
  CHECK(map.at(rsl::string("two")) == 2);
  CHECK(map.at(rsl::string("three")) == 3);
  CHECK(map.find(rsl::string("four")) == map.end());
  CHECK(map.contains(rsl::string("two")));
}

TEST_CASE("unordered_map stress")
{
  rsl::unordered_map<int, int> map;
  for(int i = 0; i < 1000; ++i)
  {
    map.emplace(i, i);
  }
  CHECK(map.size() == 1000);
  CHECK(map.load_factor() <= map.get_max_load_factor());

  for(int i = 0; i < 1000; i += 2)
  {
    CHECK(map.erase(i) == 1);
  }
  CHECK(map.size() == 500);

  for(int i = 0; i < 1000; ++i)
  {
    CHECK(map.contains(i) == (i % 2 == 1));
  }
}