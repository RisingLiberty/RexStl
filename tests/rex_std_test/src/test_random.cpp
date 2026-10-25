// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_random.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/types.h"
#include "rex_std/bonus/random/rand.h"

TEST_CASE("rand determinism")
{
  // the same seed generates the same sequence
  rsl::rand rng1(1234);
  rsl::rand rng2(1234);
  for(int i = 0; i < 100; ++i)
  {
    CHECK(rng1.new_rand() == rng2.new_rand());
  }

  // default constructed generators use the same default seed
  rsl::rand rng3;
  rsl::rand rng4;
  for(int i = 0; i < 100; ++i)
  {
    CHECK(rng3.new_rand() == rng4.new_rand());
  }

  // reseeding restarts the sequence
  rsl::rand rng5(42);
  const card32 first  = rng5.new_rand();
  const card32 second = rng5.new_rand();
  rng5.set_rand(42);
  CHECK(rng5.new_rand() == first);
  CHECK(rng5.new_rand() == second);
}

TEST_CASE("rand seeds")
{
  rsl::rand rng(5);
  CHECK(rng.prev_rand() == 5);

  rng.set_rand(10);
  CHECK(rng.prev_rand() == 10);

  // different seeds generate different sequences
  rsl::rand rng1(1);
  rsl::rand rng2(2);
  bool any_different = false;
  for(int i = 0; i < 10; ++i)
  {
    if(rng1.new_rand() != rng2.new_rand())
    {
      any_different = true;
    }
  }
  CHECK(any_different);
}

TEST_CASE("rand produces varying numbers")
{
  // a random number generator shouldn't get stuck on a single value, regardless of its seed
  for(card32 seed : {0, 1, 0x1209, 12345})
  {
    rsl::rand rng(seed);
    const card32 first = rng.new_rand();
    bool any_different = false;
    for(int i = 0; i < 100; ++i)
    {
      if(rng.new_rand() != first)
      {
        any_different = true;
      }
    }
    CHECK(any_different);
  }
}

TEST_CASE("rand ranges")
{
  rsl::rand rng(98765);

  for(int i = 0; i < 1000; ++i)
  {
    const card32 val = rng.new_rand();
    CHECK(val >= 0);
    CHECK(val <= 0x7fff);
  }

  for(int i = 0; i < 1000; ++i)
  {
    const card32 percent = rng.precent();
    CHECK(percent >= 0);
    CHECK(percent <= 100);
  }

  for(int i = 0; i < 1000; ++i)
  {
    const float32 unary = rng.unary();
    CHECK(unary >= 0.0f);
    CHECK(unary <= 1.0f);
  }

  for(int i = 0; i < 1000; ++i)
  {
    const card32 val = rng.ranged(10);
    CHECK(val >= 0);
    CHECK(val <= 10);
  }

  for(int i = 0; i < 1000; ++i)
  {
    const card32 val = rng.ranged(5, 15);
    CHECK(val >= 5);
    CHECK(val <= 15);
  }
}

// NOLINTEND
