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

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "rex_std/vector.h"

TEST_CASE("vector construction")
{
  const rsl::vector<int> vec;
  REQUIRE(vec.empty());
  REQUIRE(vec.size() == 0); // NOLINT
  REQUIRE(vec.capacity() == 0);

  const rsl::vector<int> vec2(10_size);
  REQUIRE(vec2.size() == 10);

  const rsl::vector<int> vec3(10_cap);
  REQUIRE(vec3.size() == 0); // NOLINT
  REQUIRE(vec3.capacity() == 10);

  rsl::vector<int> vec4 = { 1,2,3 };
  REQUIRE(vec4.size() == 3);
  REQUIRE(vec4[0] == 1);
  REQUIRE(vec4[1] == 2);
  REQUIRE(vec4[2] == 3);

  rsl::vector<int> vec5 = vec4;
  REQUIRE(vec4.size() == 3);
  REQUIRE(vec4[0] == 1);
  REQUIRE(vec4[1] == 2);
  REQUIRE(vec4[2] == 3);
  REQUIRE(vec5.size() == 3);
  REQUIRE(vec5[0] == 1);
  REQUIRE(vec5[1] == 2);
  REQUIRE(vec5[2] == 3);

  vec4.clear();
  REQUIRE(vec4.empty());
  REQUIRE(vec4.size() == 0); // NOLINT
  REQUIRE(vec5.size() == 3);
  REQUIRE(vec5[0] == 1);
  REQUIRE(vec5[1] == 2);
  REQUIRE(vec5[2] == 3);

  const rsl::vector<int> vec6 = rsl::move(vec5);
  REQUIRE(vec5.empty());
  REQUIRE(vec5.size() == 0); // NOLINT
  REQUIRE(vec6.size() == 3);
  REQUIRE(vec6[0] == 1);
  REQUIRE(vec6[1] == 2);
  REQUIRE(vec6[2] == 3);
}

TEST_CASE("vector assignment")
{
  rsl::vector<int> vec;
  rsl::vector<int> vec2 = { 1, 2, 3 };
  rsl::vector<int> vec3 = { 4, 5 };
  
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

  vec.insert(vec.cbegin(), 2);
  REQUIRE(vec[0] == 2);
  REQUIRE(vec[1] == 1);
}