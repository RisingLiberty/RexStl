// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_compressed_pair.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/utility/compressed_pair.h"
#include "rex_std/type_traits.h"

namespace compressed_pair_test
{
  struct empty
  {
    int get() const
    {
      return 42;
    }
  };

  struct other_empty
  {
  };

  struct non_empty
  {
    int value = 0;
  };
} // namespace compressed_pair_test

TEST_CASE("compressed pair size")
{
  using namespace compressed_pair_test;

  // an empty type doesn't take up any space
  CHECK(sizeof(rsl::compressed_pair<empty, int>) == sizeof(int));
  CHECK(sizeof(rsl::compressed_pair<int, empty>) == sizeof(int));
  CHECK(sizeof(rsl::compressed_pair<empty, non_empty>) == sizeof(non_empty));

  // two different empty types
  CHECK(sizeof(rsl::compressed_pair<empty, other_empty>) <= 2);

  // two non empty types
  // note: compressed_pair<T, T> (the same type twice) doesn't compile at the moment
  CHECK(sizeof(rsl::compressed_pair<char, int>) <= sizeof(int) * 2);
}

TEST_CASE("compressed pair construction")
{
  using namespace compressed_pair_test;

  // default construction
  {
    rsl::compressed_pair<int, float> pair;
    pair.first()  = 1;
    pair.second() = 2.0f;
    CHECK(pair.first() == 1);
    CHECK(pair.second() == 2.0f);
  }

  // construction with both values
  {
    rsl::compressed_pair<int, float> pair(5, 6.0f);
    CHECK(pair.first() == 5);
    CHECK(pair.second() == 6.0f);
  }

  // construction with only the first value
  {
    rsl::compressed_pair<int, empty> pair(5);
    CHECK(pair.first() == 5);
    CHECK(pair.second().get() == 42);
  }

  // construction with only the second value
  {
    rsl::compressed_pair<empty, int> pair(7);
    CHECK(pair.first().get() == 42);
    CHECK(pair.second() == 7);
  }

  // copy construction
  {
    rsl::compressed_pair<int, float> pair(5, 6.0f);
    rsl::compressed_pair<int, float> copy(pair);
    CHECK(copy.first() == 5);
    CHECK(copy.second() == 6.0f);
  }
}

TEST_CASE("compressed pair access")
{
  using namespace compressed_pair_test;

  rsl::compressed_pair<non_empty, int> pair;
  pair.first().value = 3;
  pair.second()      = 4;
  CHECK(pair.first().value == 3);
  CHECK(pair.second() == 4);

  const rsl::compressed_pair<non_empty, int>& const_pair = pair;
  CHECK(const_pair.first().value == 3);
  CHECK(const_pair.second() == 4);
  static_assert(rsl::is_const_v<rsl::remove_reference_t<decltype(const_pair.first())>>);

  // modifying one element doesn't affect the other
  pair.first().value = 10;
  CHECK(pair.second() == 4);
  pair.second() = 20;
  CHECK(pair.first().value == 10);

  // the empty element is still accessible
  rsl::compressed_pair<empty, int> empty_pair(1);
  CHECK(empty_pair.first().get() == 42);
}

TEST_CASE("compressed pair assignment")
{
  rsl::compressed_pair<int, float> pair1(1, 2.0f);
  rsl::compressed_pair<int, float> pair2(3, 4.0f);

  pair1 = pair2;
  CHECK(pair1.first() == 3);
  CHECK(pair1.second() == 4.0f);

  pair2.first() = 10;
  CHECK(pair1.first() == 3);
}

// NOLINTEND
