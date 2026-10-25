// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_memory.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/memory/memory_size.h"
#include "rex_std/memory.h"

// uninitialized_fill.h uses rsl::fill for trivial types but doesn't include it itself
#include "rex_std/algorithm.h"

#include "rex_std_test/test_object.h"

TEST_CASE("memcpy")
{
  const char src[] = "hello world";
  char dst[12]     = {};

  void* res = rsl::memcpy(dst, src, sizeof(src));
  CHECK(res == dst);
  for(int i = 0; i < 12; ++i)
  {
    CHECK(dst[i] == src[i]);
  }

  // copying 0 bytes doesn't do anything
  char dst2[4] = {'a', 'b', 'c', 'd'};
  rsl::memcpy(dst2, src, 0);
  CHECK(dst2[0] == 'a');
  CHECK(dst2[3] == 'd');

  // partial copy
  int ints_src[4] = {1, 2, 3, 4};
  int ints_dst[4] = {0, 0, 0, 0};
  rsl::memcpy(ints_dst, ints_src, 2 * sizeof(int));
  CHECK(ints_dst[0] == 1);
  CHECK(ints_dst[1] == 2);
  CHECK(ints_dst[2] == 0);
  CHECK(ints_dst[3] == 0);
}

TEST_CASE("memset")
{
  char buffer[8] = {};

  void* res = rsl::memset(buffer, 'x', 8);
  CHECK(res == buffer);
  for(char c : buffer)
  {
    CHECK(c == 'x');
  }

  rsl::memset(buffer, 0, 4);
  CHECK(buffer[0] == 0);
  CHECK(buffer[3] == 0);
  CHECK(buffer[4] == 'x');
  CHECK(buffer[7] == 'x');

  int ints[4] = {1, 2, 3, 4};
  rsl::memset(ints, 0, sizeof(ints));
  for(int x : ints)
  {
    CHECK(x == 0);
  }

  // setting 0 bytes doesn't do anything
  rsl::memset(buffer, 'y', 0);
  CHECK(buffer[4] == 'x');
}

TEST_CASE("memmove")
{
  // non overlapping
  {
    int src[4] = {1, 2, 3, 4};
    int dst[4] = {};
    rsl::memmove(dst, src, sizeof(src));
    CHECK(dst[0] == 1);
    CHECK(dst[3] == 4);
  }

  // overlapping, destination after source
  {
    int buffer[6] = {1, 2, 3, 4, 5, 6};
    rsl::memmove(buffer + 2, buffer, 4 * sizeof(int));
    CHECK(buffer[0] == 1);
    CHECK(buffer[1] == 2);
    CHECK(buffer[2] == 1);
    CHECK(buffer[3] == 2);
    CHECK(buffer[4] == 3);
    CHECK(buffer[5] == 4);
  }

  // overlapping, destination before source
  {
    int buffer[6] = {1, 2, 3, 4, 5, 6};
    rsl::memmove(buffer, buffer + 2, 4 * sizeof(int));
    CHECK(buffer[0] == 3);
    CHECK(buffer[1] == 4);
    CHECK(buffer[2] == 5);
    CHECK(buffer[3] == 6);
    CHECK(buffer[4] == 5);
    CHECK(buffer[5] == 6);
  }

  // moving onto itself
  {
    int buffer[3] = {1, 2, 3};
    rsl::memmove(buffer, buffer, sizeof(buffer));
    CHECK(buffer[0] == 1);
    CHECK(buffer[1] == 2);
    CHECK(buffer[2] == 3);
  }
}

TEST_CASE("construct at and destroy")
{
  using namespace rsl::test;
  test_object::reset();

  alignas(test_object) char buffer[sizeof(test_object) * 3];
  test_object* objects = reinterpret_cast<test_object*>(buffer);

  // construct_at
  test_object* obj = rsl::construct_at(objects, 5);
  CHECK(obj == objects);
  CHECK(obj->x() == 5);
  rsl::construct_at(objects + 1, 6);
  rsl::construct_at(objects + 2, 1, 2, 3);
  CHECK(objects[2].x() == 6);
  CHECK(test_object::num_ctor_calls() == 3);

  // destroy_at
  rsl::destroy_at(objects);
  CHECK(test_object::num_dtor_calls() == 1);

  // destroy
  rsl::destroy(objects + 1, objects + 3);
  CHECK(test_object::num_dtor_calls() == 3);
  CHECK(test_object::is_clear());

  test_object::reset();
}

TEST_CASE("uninitialized memory algorithms")
{
  using namespace rsl::test;
  test_object::reset();

  alignas(test_object) char buffer[sizeof(test_object) * 4];
  test_object* objects = reinterpret_cast<test_object*>(buffer);

  // uninitialized_fill
  {
    rsl::uninitialized_fill(objects, objects + 4, test_object(7));
    for(int i = 0; i < 4; ++i)
    {
      CHECK(objects[i].x() == 7);
    }
    rsl::destroy(objects, objects + 4);
  }

  // uninitialized_copy
  {
    test_object src[3] = {test_object(1), test_object(2), test_object(3)};
    test_object* end   = rsl::uninitialized_copy(src, src + 3, objects);
    CHECK(end == objects + 3);
    CHECK(objects[0].x() == 1);
    CHECK(objects[1].x() == 2);
    CHECK(objects[2].x() == 3);
    rsl::destroy(objects, objects + 3);
  }

  // uninitialized_copy_n
  {
    test_object src[3] = {test_object(1), test_object(2), test_object(3)};
    test_object* end   = rsl::uninitialized_copy_n(src, 2, objects);
    CHECK(end == objects + 2);
    CHECK(objects[0].x() == 1);
    CHECK(objects[1].x() == 2);
    rsl::destroy(objects, objects + 2);
  }

  // uninitialized_move
  {
    test_object src[2] = {test_object(4), test_object(5)};
    card32 num_moves   = test_object::num_move_ctor_calls();
    test_object* end   = rsl::uninitialized_move(src, src + 2, objects);
    CHECK(end == objects + 2);
    CHECK(objects[0].x() == 4);
    CHECK(objects[1].x() == 5);
    CHECK(test_object::num_move_ctor_calls() == num_moves + 2);
    rsl::destroy(objects, objects + 2);
  }

  // uninitialized_default_construct
  {
    test_object* end = rsl::uninitialized_default_construct(objects, 4);
    CHECK(end == objects + 4);
    for(int i = 0; i < 4; ++i)
    {
      CHECK(objects[i].x() == 0);
    }
    rsl::destroy(objects, objects + 4);
  }

  CHECK(test_object::is_clear());
  test_object::reset();

  // trivial types take the fast path
  {
    int src[4] = {1, 2, 3, 4};
    int dst[4] = {};
    int* end   = rsl::uninitialized_copy(src, src + 4, dst);
    CHECK(end == dst + 4);
    CHECK(dst[0] == 1);
    CHECK(dst[3] == 4);

    rsl::uninitialized_fill(dst, dst + 4, 9);
    CHECK(dst[0] == 9);
    CHECK(dst[3] == 9);
  }
}

TEST_CASE("memory size construction")
{
  constexpr rsl::memory_size empty;
  static_assert(empty.size_in_bytes() == 0);
  CHECK(empty == 0);

  constexpr rsl::memory_size size(1024);
  static_assert(size.size_in_bytes() == 1024);
  CHECK(static_cast<card64>(size) == 1024);

  CHECK(rsl::memory_size::from_bytes(10).size_in_bytes() == 10);
  CHECK(rsl::memory_size::from_kb(1).size_in_bytes() == 1000);
  CHECK(rsl::memory_size::from_mb(1).size_in_bytes() == 1000 * 1000);
  CHECK(rsl::memory_size::from_gb(1).size_in_bytes() == 1000ll * 1000 * 1000);
  CHECK(rsl::memory_size::from_kib(1).size_in_bytes() == 1024);
  CHECK(rsl::memory_size::from_mib(1).size_in_bytes() == 1024 * 1024);
  CHECK(rsl::memory_size::from_gib(1).size_in_bytes() == 1024ll * 1024 * 1024);
  CHECK(rsl::memory_size::from_gib(4).size_in_bytes() == 4ll * 1024 * 1024 * 1024);
}

TEST_CASE("memory size literals")
{
  CHECK((10_bytes).size_in_bytes() == 10);
  CHECK((2_kb).size_in_bytes() == 2000);
  CHECK((3_mb).size_in_bytes() == 3 * 1000 * 1000);
  CHECK((1_gb).size_in_bytes() == 1000ll * 1000 * 1000);
  CHECK((2_kib).size_in_bytes() == 2048);
  CHECK((3_mib).size_in_bytes() == 3 * 1024 * 1024);
  CHECK((1_gib).size_in_bytes() == 1024ll * 1024 * 1024);
}

TEST_CASE("memory size conversion")
{
  const rsl::memory_size size = rsl::memory_size::from_bytes(1536);
  CHECK(size.size_in_kib() == 1.5f);
  CHECK(size.size_in_kb() == 1.536f);

  const rsl::memory_size mib = 2_mib;
  CHECK(mib.size_in_mib() == 2.0f);
  CHECK(mib.size_in_kib() == 2048.0f);

  const rsl::memory_size gib = 1_gib;
  CHECK(gib.size_in_gib() == 1.0f);
  CHECK(gib.size_in_mib() == 1024.0f);

  const rsl::memory_size mb = 5_mb;
  CHECK(mb.size_in_mb() == 5.0f);
  CHECK(mb.size_in_kb() == 5000.0f);

  const rsl::memory_size gb = 2_gb;
  CHECK(gb.size_in_gb() == 2.0f);
}

TEST_CASE("memory size arithmetic")
{
  rsl::memory_size size = 1_kib;

  // the arguments need to be card64, otherwise the call is ambiguous with the builtin operators
  // because memory_size implicitly converts to card64
  rsl::memory_size bigger = size + 1024ll;
  CHECK(bigger.size_in_bytes() == 2048);
  CHECK(size.size_in_bytes() == 1024);

  rsl::memory_size smaller = size - 24ll;
  CHECK(smaller.size_in_bytes() == 1000);
  CHECK(size.size_in_bytes() == 1024);

  size += 1024;
  CHECK(size.size_in_bytes() == 2048);

  size -= 48;
  CHECK(size.size_in_bytes() == 2000);

  // memory sizes implicitly convert to their size in bytes
  CHECK(1_kib + 1_kib == 2048);
  CHECK(1_kib > 1_kb);
  CHECK(1_mib > 1_mb);
}

// NOLINTEND
