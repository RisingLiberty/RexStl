// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_strong_type.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/utility/strong_type.h"
#include "rex_std/type_traits.h"

namespace strong_type_test
{
  RSL_CREATE_STRONG_TYPE(meters, float);
  RSL_CREATE_STRONG_TYPE(entity_id, int);
  RSL_CREATE_STRONG_TYPE(other_id, int);

  RSL_CREATE_LITERAL_FOR_STRONG_TYPE(meters, m);
  RSL_CREATE_LITERAL_FOR_STRONG_TYPE(entity_id, id);
} // namespace strong_type_test

TEST_CASE("strong type construction")
{
  using namespace strong_type_test;

  // default construction value initializes the underlying value
  constexpr entity_id default_id;
  static_assert(default_id.get() == 0);
  CHECK(default_id.get() == 0);

  constexpr meters default_meters;
  CHECK(default_meters.get() == 0.0f);

  // explicit construction from the underlying value
  constexpr entity_id id(5);
  static_assert(id.get() == 5);
  CHECK(id.get() == 5);

  // strong types are not implicitly convertible from their underlying type
  static_assert(!rsl::is_convertible_v<int, entity_id>);
  static_assert(rsl::is_constructible_v<entity_id, int>);

  // different strong types with the same underlying type are distinct types
  static_assert(!rsl::is_same_v<entity_id, other_id>);
  static_assert(!rsl::is_convertible_v<entity_id, other_id>);

  static_assert(rsl::is_same_v<entity_id::underlying_type, int>);
  static_assert(rsl::is_same_v<meters::underlying_type, float>);
}

TEST_CASE("strong type access")
{
  using namespace strong_type_test;

  entity_id id(1);
  CHECK(id.get() == 1);

  id.get() = 10;
  CHECK(id.get() == 10);

  const entity_id& const_id = id;
  CHECK(const_id.get() == 10);
  static_assert(rsl::is_same_v<decltype(const_id.get()), const int&>);
}

TEST_CASE("strong type comparison")
{
  using namespace strong_type_test;

  constexpr entity_id id1(1);
  constexpr entity_id id2(1);
  constexpr entity_id id3(2);

  CHECK(id1 == id2);
  CHECK(!(id1 != id2));
  CHECK(id1 != id3);
  CHECK(!(id1 == id3));

  static_assert(id1 == id2);
  static_assert(id1 != id3);
}

TEST_CASE("strong type copy")
{
  using namespace strong_type_test;

  meters a(1.5f);
  meters b = a;
  CHECK(b.get() == 1.5f);

  b = meters(3.0f);
  CHECK(b.get() == 3.0f);
  CHECK(a.get() == 1.5f);
}

TEST_CASE("strong type literals")
{
  using namespace strong_type_test;

  constexpr entity_id id = 42_id;
  static_assert(id.get() == 42);
  CHECK(id == entity_id(42));

  constexpr meters distance = 2.5_m;
  CHECK(distance.get() == 2.5f);
  CHECK(distance == meters(2.5f));
}

// NOLINTEND
