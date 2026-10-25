// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_map.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/map.h"

#include "rex_std_test/test_object.h"
#include "rex_std_test/test_rand.h"
#include "rex_std_test/test_rex_std.h"

namespace map_test
{
  using int_map = rsl::map<int, int>;

  // fills a map with keys [0, count) using emplace and value = key * 10
  void fill(int_map& map, int count)
  {
    for(int i = 0; i < count; ++i)
    {
      map.emplace(i, i * 10);
    }
  }

  template <typename Map>
  bool is_sorted_by_key(const Map& map)
  {
    auto it = map.begin();
    if(it == map.end())
    {
      return true;
    }

    auto prev = it;
    ++it;
    for(; it != map.end(); ++it, ++prev)
    {
      if(!(prev->key < it->key))
      {
        return false;
      }
    }
    return true;
  }
} // namespace map_test

TEST_CASE("map construction")
{
  // map()
  {
    const map_test::int_map map;
    CHECK(map.empty());
    CHECK(map.size() == 0);
    CHECK(map.begin() == map.end());
  }

  // map(first, last)
  {
    rsl::key_value<const int, int> arr[] = {{3, 30}, {1, 10}, {2, 20}};
    map_test::int_map map(arr, arr + 3);
    CHECK(map.size() == 3);
    CHECK(map.at(1) == 10);
    CHECK(map.at(2) == 20);
    CHECK(map.at(3) == 30);
    CHECK(map_test::is_sorted_by_key(map));
  }

  // map(first, last) with duplicate keys keeps the first one
  {
    rsl::key_value<const int, int> arr[] = {{1, 10}, {1, 20}};
    map_test::int_map map(arr, arr + 2);
    CHECK(map.size() == 1);
    CHECK(map.at(1) == 10);
  }

  // map(const map&)
  {
    map_test::int_map map;
    map_test::fill(map, 5);

    map_test::int_map copy(map);
    CHECK(copy.size() == 5);
    CHECK(map.size() == 5);
    for(int i = 0; i < 5; ++i)
    {
      CHECK(copy.at(i) == i * 10);
    }

    // the copy is a deep copy
    copy[0] = 100;
    CHECK(map.at(0) == 0);
  }

  // map(map&&)
  {
    map_test::int_map map;
    map_test::fill(map, 5);

    map_test::int_map moved(rsl::move(map));
    CHECK(moved.size() == 5);
    for(int i = 0; i < 5; ++i)
    {
      CHECK(moved.at(i) == i * 10);
    }
    CHECK(map.empty());
  }

  // copying an empty map
  {
    map_test::int_map map;
    map_test::int_map copy(map);
    CHECK(copy.empty());
  }
}

TEST_CASE("map assignment")
{
  // copy assignment
  {
    map_test::int_map map;
    map_test::fill(map, 3);

    map_test::int_map other;
    other.emplace(100, 1);
    other = map;
    CHECK(other.size() == 3);
    CHECK(other.contains(100) == false);
    CHECK(other.at(2) == 20);
    CHECK(map.size() == 3);
  }

  // move assignment
  {
    map_test::int_map map;
    map_test::fill(map, 3);

    map_test::int_map other;
    other.emplace(100, 1);
    other = rsl::move(map);
    CHECK(other.size() == 3);
    CHECK(other.contains(100) == false);
    CHECK(other.at(2) == 20);
  }
}

TEST_CASE("map element access")
{
  map_test::int_map map;
  map_test::fill(map, 5);

  // at
  CHECK(map.at(0) == 0);
  CHECK(map.at(4) == 40);
  map.at(4) = 41;
  CHECK(map.at(4) == 41);

  const map_test::int_map& const_map = map;
  CHECK(const_map.at(3) == 30);

  // operator[] on an existing key
  CHECK(map[1] == 10);
  map[1] = 11;
  CHECK(map.at(1) == 11);
  CHECK(map.size() == 5);

  // operator[] on a new key inserts a value initialized element
  CHECK(map[10] == 0);
  CHECK(map.size() == 6);
  map[11] = 110;
  CHECK(map.size() == 7);
  CHECK(map.at(11) == 110);

  // operator[] with an rvalue key
  int key   = 20;
  map[rsl::move(key)] = 200;
  CHECK(map.at(20) == 200);
}

TEST_CASE("map iterators")
{
  map_test::int_map map;
  map.emplace(5, 50);
  map.emplace(1, 10);
  map.emplace(3, 30);
  map.emplace(2, 20);
  map.emplace(4, 40);

  // iteration happens in key order
  {
    int expected = 1;
    for(auto& kv : map)
    {
      CHECK(kv.key == expected);
      CHECK(kv.value == expected * 10);
      ++expected;
    }
    CHECK(expected == 6);
  }

  // const iteration
  {
    const map_test::int_map& const_map = map;
    int expected                       = 1;
    for(auto it = const_map.cbegin(); it != const_map.cend(); ++it)
    {
      CHECK(it->key == expected);
      ++expected;
    }
    CHECK(expected == 6);
  }

  // reverse iteration
  {
    int expected = 5;
    for(auto it = map.rbegin(); it != map.rend(); ++it)
    {
      CHECK((*it).key == expected);
      --expected;
    }
    CHECK(expected == 0);
  }

  // backward iteration with operator--
  {
    int expected = 5;
    auto it      = map.end();
    while(it != map.begin())
    {
      --it;
      CHECK(it->key == expected);
      --expected;
    }
    CHECK(expected == 0);
  }

  // values can be modified through iterators
  for(auto& kv : map)
  {
    kv.value += 1;
  }
  CHECK(map.at(1) == 11);
  CHECK(map.at(5) == 51);
}

TEST_CASE("map capacity")
{
  map_test::int_map map;
  CHECK(map.empty());
  CHECK(map.size() == 0);
  CHECK(map.max_size() > 0);

  map.emplace(1, 1);
  CHECK(!map.empty());
  CHECK(map.size() == 1);

  // emplacing an existing key doesn't change the size
  map.emplace(1, 2);
  CHECK(map.size() == 1);
  CHECK(map.at(1) == 1);
}

TEST_CASE("map modifiers")
{
  // emplace
  {
    map_test::int_map map;
    auto res = map.emplace(1, 10);
    CHECK(res.emplace_successful);
    CHECK(res.inserted_element->key == 1);
    CHECK(res.inserted_element->value == 10);

    auto res2 = map.emplace(1, 20);
    CHECK(!res2.emplace_successful);
    CHECK(res2.inserted_element->key == 1);
    CHECK(res2.inserted_element->value == 10);
    CHECK(map.size() == 1);
  }

  // insert an lvalue key value pair
  {
    map_test::int_map map;
    rsl::key_value<const int, int> kv(1, 10);
    auto res = map.insert(kv);
    CHECK(res.emplace_successful);
    CHECK(map.at(1) == 10);
  }

  // clear
  {
    map_test::int_map map;
    map_test::fill(map, 10);
    CHECK(map.size() == 10);
    map.clear();
    CHECK(map.empty());
    CHECK(map.begin() == map.end());

    // the map is usable after being cleared
    map.emplace(1, 1);
    CHECK(map.size() == 1);
  }

  // erase by key
  {
    map_test::int_map map;
    map_test::fill(map, 5);

    CHECK(map.erase(2) == 1);
    CHECK(map.size() == 4);
    CHECK(!map.contains(2));
    CHECK(map.erase(2) == 0);
    CHECK(map.size() == 4);
    CHECK(map.erase(100) == 0);
    CHECK(map_test::is_sorted_by_key(map));
  }

  // erase by iterator
  {
    map_test::int_map map;
    map_test::fill(map, 5);

    auto it = map.erase(map.begin());
    CHECK(it == map.begin());
    CHECK(it->key == 1);
    CHECK(map.size() == 4);

    it = map.find(3);
    it = map.erase(it);
    CHECK(it->key == 4);
    CHECK(map.size() == 3);

    it = map.find(4);
    it = map.erase(it);
    CHECK(it == map.end());
    CHECK(map.size() == 2);
  }

  // swap
  {
    map_test::int_map map1;
    map_test::fill(map1, 3);
    map_test::int_map map2;
    map2.emplace(100, 1000);

    map1.swap(map2);
    CHECK(map1.size() == 1);
    CHECK(map1.at(100) == 1000);
    CHECK(map2.size() == 3);
    CHECK(map2.at(2) == 20);

    // swapping with an empty map
    map_test::int_map empty;
    map1.swap(empty);
    CHECK(map1.empty());
    CHECK(empty.size() == 1);
    CHECK(empty.at(100) == 1000);
  }
}

TEST_CASE("map lookup")
{
  map_test::int_map map;
  map.emplace(10, 1);
  map.emplace(20, 2);
  map.emplace(30, 3);

  // count
  CHECK(map.count(10) == 1);
  CHECK(map.count(15) == 0);

  // find
  CHECK(map.find(20) != map.end());
  CHECK(map.find(20)->value == 2);
  CHECK(map.find(25) == map.end());

  const map_test::int_map& const_map = map;
  CHECK(const_map.find(30) != const_map.end());
  CHECK(const_map.find(35) == const_map.end());

  // contains
  CHECK(map.contains(10));
  CHECK(!map.contains(0));
  CHECK(!map.contains(40));

  // lower bound
  CHECK(map.lower_bound(10)->key == 10);
  CHECK(map.lower_bound(15)->key == 20);
  CHECK(map.lower_bound(0)->key == 10);
  CHECK(map.lower_bound(31) == map.end());

  // upper bound
  CHECK(map.upper_bound(10)->key == 20);
  CHECK(map.upper_bound(15)->key == 20);
  CHECK(map.upper_bound(0)->key == 10);
  CHECK(map.upper_bound(30) == map.end());
}

TEST_CASE("map erase if")
{
  map_test::int_map map;
  map_test::fill(map, 10);

  auto num_erased = rsl::erase_if(map, [](const auto& kv) { return kv.key % 2 == 0; });
  CHECK(num_erased == 5);
  CHECK(map.size() == 5);
  for(const auto& kv : map)
  {
    CHECK(kv.key % 2 == 1);
  }

  num_erased = rsl::erase_if(map, [](const auto&) { return false; });
  CHECK(num_erased == 0);
  CHECK(map.size() == 5);
}

TEST_CASE("map stress")
{
  rsl::test::rand rng(rsl::test::rand_seed());
  map_test::int_map map;

  // insert random keys, keeping a count of the unique ones
  int num_unique = 0;
  for(int i = 0; i < 1000; ++i)
  {
    const int key = static_cast<int>(rng.rand_limit(500));
    if(map.emplace(key, i).emplace_successful)
    {
      ++num_unique;
    }
  }

  CHECK(map.size() == num_unique);
  CHECK(map_test::is_sorted_by_key(map));

  // erase half of the keys and verify the tree is still ordered
  for(int key = 0; key < 500; key += 2)
  {
    map.erase(key);
  }
  CHECK(map_test::is_sorted_by_key(map));
  for(const auto& kv : map)
  {
    CHECK(kv.key % 2 == 1);
  }
}

TEST_CASE("map with non trivial type")
{
  using namespace rsl::test;
  test_object::reset();

  {
    rsl::map<int, test_object> map;
    map.emplace(1, 10);
    map.emplace(2, 20);
    map.emplace(3, 30);
    CHECK(map.at(2) == 20);

    map.erase(2);
    CHECK(map.size() == 2);
  }

  CHECK(test_object::is_clear());
  test_object::reset();
}

TEST_CASE("multimap")
{
  rsl::multimap<int, int> map;
  map.emplace(1, 10);
  map.emplace(1, 11);
  map.emplace(2, 20);
  map.emplace(1, 12);

  CHECK(map.size() == 4);
  CHECK(map.find(1) != map.end());
  CHECK(map.find(2)->value == 20);
  CHECK(map.find(3) == map.end());

  // all duplicate keys are stored next to each other
  int num_ones = 0;
  for(auto it = map.lower_bound(1); it != map.upper_bound(1); ++it)
  {
    CHECK(it->key == 1);
    ++num_ones;
  }
  CHECK(num_ones == 3);
}

// NOLINTEND
