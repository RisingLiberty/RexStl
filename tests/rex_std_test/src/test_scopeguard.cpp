// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_scopeguard.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/utility/scopeguard.h"

namespace scopeguard_test
{
  int g_counter = 0;

  void increment_counter()
  {
    ++g_counter;
  }

  struct functor
  {
    int* value;

    void operator()()
    {
      *value = 42;
    }
  };
} // namespace scopeguard_test

TEST_CASE("scopeguard executes on scope exit")
{
  int x = 0;
  {
    rsl::scopeguard guard([&x]() { x = 1; });
    CHECK(x == 0);
  }
  CHECK(x == 1);
}

TEST_CASE("scopeguard release")
{
  int x = 0;
  {
    rsl::scopeguard guard([&x]() { x = 1; });
    guard.release();
  }
  CHECK(x == 0);

  // releasing multiple times is fine
  {
    rsl::scopeguard guard([&x]() { x = 2; });
    guard.release();
    guard.release();
  }
  CHECK(x == 0);
}

TEST_CASE("scopeguard with different callables")
{
  // function pointer
  {
    scopeguard_test::g_counter = 0;
    {
      rsl::scopeguard guard(&scopeguard_test::increment_counter);
    }
    CHECK(scopeguard_test::g_counter == 1);
  }

  // functor
  {
    int x = 0;
    {
      rsl::scopeguard guard(scopeguard_test::functor {&x});
    }
    CHECK(x == 42);
  }
}

TEST_CASE("scopeguard ordering")
{
  // guards are destroyed in reverse order of declaration
  int order[2] = {0, 0};
  int index    = 0;
  {
    rsl::scopeguard first([&]() { order[index++] = 1; });
    rsl::scopeguard second([&]() { order[index++] = 2; });
  }
  CHECK(index == 2);
  CHECK(order[0] == 2);
  CHECK(order[1] == 1);
}

TEST_CASE("scopeguard early return")
{
  int x = 0;
  auto func = [&x](bool return_early)
  {
    rsl::scopeguard guard([&x]() { ++x; });
    if(return_early)
    {
      return 1;
    }
    return 2;
  };

  CHECK(func(true) == 1);
  CHECK(x == 1);
  CHECK(func(false) == 2);
  CHECK(x == 2);
}

// NOLINTEND
