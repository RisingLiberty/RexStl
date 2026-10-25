// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_bonus_utility.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/algorithm.h"
#include "rex_std/assert.h"
#include "rex_std/bonus/utility/casting.h"
#include "rex_std/bonus/utility/conditional_static_cast.h"
#include "rex_std/bonus/utility/high_water_mark.h"
#include "rex_std/bonus/utility/id_generator.h"
#include "rex_std/bonus/utility/key_value.h"
#include "rex_std/bonus/utility/nand.h"
#include "rex_std/bonus/utility/not_null.h"
#include "rex_std/bonus/utility/use_self.h"
#include "rex_std/bonus/utility/version.h"
#include "rex_std/bonus/utility/wrapped_index.h"
#include "rex_std/bonus/utility/yes_no.h"
#include "rex_std/string.h"
#include "rex_std/type_traits.h"

namespace bonus_utility_test
{
  DEFINE_YES_NO_ENUM(enable_feature);

  struct id_tag_a
  {
  };
  struct id_tag_b
  {
  };
} // namespace bonus_utility_test

TEST_CASE("version")
{
  // construction from numbers
  rsl::version v(1, 2, 3);
  CHECK(v.major() == 1);
  CHECK(v.minor() == 2);
  CHECK(v.patch() == 3);

  // construction from a string
  rsl::version parsed(rsl::string_view("4.5.6"));
  CHECK(parsed.major() == 4);
  CHECK(parsed.minor() == 5);
  CHECK(parsed.patch() == 6);

  rsl::version parsed_big(rsl::string_view("10.20.12345"));
  CHECK(parsed_big.major() == 10);
  CHECK(parsed_big.minor() == 20);
  CHECK(parsed_big.patch() == 12345);

  // a missing patch number defaults to 0
  rsl::version no_patch(rsl::string_view("1.2"));
  CHECK(no_patch.major() == 1);
  CHECK(no_patch.minor() == 2);
  CHECK(no_patch.patch() == 0);

  // comparison
  CHECK(v == rsl::version(1, 2, 3));
  CHECK(v != rsl::version(1, 2, 4));
  CHECK(v != rsl::version(1, 3, 3));
  CHECK(v != rsl::version(2, 2, 3));
  CHECK(parsed == rsl::version(4, 5, 6));

  // conversion to string
  CHECK(rsl::to_string(v) == "1.2.3");
  CHECK(rsl::to_string(parsed_big) == "10.20.12345");
}

TEST_CASE("wrapped index")
{
  // incrementing wraps around to the min value
  rsl::wrapped_index idx(0, 0, 3);
  CHECK(idx == 0);
  idx.increment();
  CHECK(idx == 1);
  idx.increment();
  CHECK(idx == 2);
  idx.increment();
  CHECK(idx == 0);

  // decrementing wraps around to the max value - 1
  idx.decrement();
  CHECK(idx == 2);
  idx.decrement();
  CHECK(idx == 1);

  // custom range
  rsl::wrapped_index range_idx(5, 5, 8);
  range_idx.increment();
  range_idx.increment();
  CHECK(range_idx == 7);
  range_idx.increment();
  CHECK(range_idx == 5);
  range_idx.decrement();
  CHECK(range_idx == 7);

  // a wrapped index without a start value starts at the min value
  rsl::wrapped_index default_idx(2, 6);
  CHECK(default_idx == 2);
}

TEST_CASE("yes no")
{
  rsl::yes_no yes = rsl::yes_no::yes;
  rsl::yes_no no  = rsl::yes_no::no;
  CHECK(yes);
  CHECK(!no);

  bonus_utility_test::enable_feature enabled  = bonus_utility_test::enable_feature::yes;
  bonus_utility_test::enable_feature disabled = bonus_utility_test::enable_feature::no;
  CHECK(enabled);
  CHECK(!disabled);

  const bool true_value  = true;
  const bool false_value = false;
  bonus_utility_test::enable_feature from_true(true_value);
  bonus_utility_test::enable_feature from_false(false_value);
  CHECK(from_true);
  CHECK(!from_false);

  // constructing from a bool rvalue is disallowed to force the use of the named values
  static_assert(!rsl::is_constructible_v<bonus_utility_test::enable_feature, bool&&>);
}

TEST_CASE("not null")
{
  int x = 5;
  rsl::not_null<int> ptr(&x);
  CHECK(ptr.get() == &x);
  CHECK(*ptr == 5);

  *ptr = 6;
  CHECK(x == 6);

  const rsl::not_null<int>& const_ptr = ptr;
  CHECK(const_ptr.get() == &x);
  CHECK(*const_ptr == 6);

  // a not_null can't be created from a nullptr
  static_assert(!rsl::is_constructible_v<rsl::not_null<int>, rsl::nullptr_t>);
}

TEST_CASE("numeric cast")
{
  CHECK(rsl::numeric_cast<int>(5.7f) == 5);
  CHECK(rsl::numeric_cast<float32>(3) == 3.0f);
  CHECK(rsl::numeric_cast<uint8>(255) == 255);
  CHECK(rsl::safe_numeric_cast<int>(42.0) == 42);
  CHECK(rsl::safe_numeric_cast<card8>(100) == 100);

  static_assert(rsl::numeric_cast<int>(2.9) == 2);
}

TEST_CASE("conditional static cast")
{
  static_assert(rsl::conditional_static_cast<int>(5.5f) == 5);
  static_assert(rsl::conditional_static_cast<int>(5) == 5);
  static_assert(rsl::is_same_v<decltype(rsl::conditional_static_cast<int>(5.5f)), int>);
  static_assert(rsl::is_same_v<decltype(rsl::conditional_static_cast<float>(5.5f)), float>);
}

TEST_CASE("high water mark")
{
  rsl::high_water_mark<card32> hwm;
  CHECK(hwm.value() == 0);
  CHECK(hwm.max_value() == 0);

  ++hwm;
  ++hwm;
  CHECK(hwm.value() == 2);
  CHECK(hwm.max_value() == 2);

  --hwm;
  CHECK(hwm.value() == 1);
  CHECK(hwm.max_value() == 2);

  hwm += 5;
  CHECK(hwm.value() == 6);
  CHECK(hwm.max_value() == 6);

  hwm -= 4;
  CHECK(hwm.value() == 2);
  CHECK(hwm.max_value() == 6);

  hwm *= 4;
  CHECK(hwm.value() == 8);
  CHECK(hwm.max_value() == 8);

  hwm /= 2;
  CHECK(hwm.value() == 4);
  CHECK(hwm.max_value() == 8);

  hwm %= 3;
  CHECK(hwm.value() == 1);
  CHECK(hwm.max_value() == 8);

  // post increment returns the old value
  auto old = hwm++;
  CHECK(old.value() == 1);
  CHECK(hwm.value() == 2);

  old = hwm--;
  CHECK(old.value() == 2);
  CHECK(hwm.value() == 1);
  CHECK(hwm.max_value() == 8);

  // implicit conversion to the underlying type
  card32 value = hwm;
  CHECK(value == 1);

  // initial values
  rsl::high_water_mark<card32> hwm2(5);
  CHECK(hwm2.value() == 5);
  CHECK(hwm2.max_value() == 5);
  rsl::high_water_mark<card32> hwm3(5, 10);
  CHECK(hwm3.value() == 5);
  CHECK(hwm3.max_value() == 10);

  // arithmetic operators return a new object
  CHECK((hwm2 + 3).value() == 8);
  CHECK((hwm2 - 3).value() == 2);
  CHECK((hwm2 * 3).value() == 15);
  CHECK((hwm2 / 5).value() == 1);
  CHECK((hwm2 % 3).value() == 2);
  CHECK(hwm2.value() == 5);
}

TEST_CASE("id generator")
{
  // every new id is unique and incrementing
  const rsl::ID id1 = rsl::id_generator::new_id();
  const rsl::ID id2 = rsl::id_generator::new_id();
  CHECK(id2 == id1 + 1);

  // typed ids have their own counter per type
  const rsl::ID a1 = rsl::id_generator::new_id<bonus_utility_test::id_tag_a>();
  const rsl::ID a2 = rsl::id_generator::new_id<bonus_utility_test::id_tag_a>();
  const rsl::ID b1 = rsl::id_generator::new_id<bonus_utility_test::id_tag_b>();
  CHECK(a2 == a1 + 1);
  CHECK(b1 == 0);
}

TEST_CASE("nand")
{
  static_assert(rsl::nand(false, false));
  static_assert(rsl::nand(true, false));
  static_assert(rsl::nand(false, true));
  static_assert(!rsl::nand(true, true));
  CHECK(rsl::nand(0, 1));
  CHECK(!rsl::nand(1, 2));
}

TEST_CASE("key value")
{
  rsl::key_value<int, float> kv(1, 2.0f);
  CHECK(kv.key == 1);
  CHECK(kv.value == 2.0f);
  CHECK(kv.first() == 1);
  CHECK(kv.second() == 2.0f);

  kv.first()  = 5;
  kv.second() = 6.0f;
  CHECK(kv.key == 5);
  CHECK(kv.value == 6.0f);

  const rsl::key_value<int, float>& const_kv = kv;
  CHECK(const_kv.first() == 5);
  CHECK(const_kv.second() == 6.0f);

  // the value is constructed in place with the remaining arguments
  rsl::key_value<int, rsl::string> kv_string(1, "hello");
  CHECK(kv_string.value == "hello");

  // default construction
  rsl::key_value<int, int> default_kv {};
  CHECK(default_kv.key == 0);
  CHECK(default_kv.value == 0);

  static_assert(rsl::is_same_v<rsl::key_value<int, float>::key_type, int>);
  static_assert(rsl::is_same_v<rsl::key_value<int, float>::value_type, float>);
}

TEST_CASE("use self")
{
  rsl::use_self<int> self;
  const int x = 5;
  CHECK(self(x) == 5);
  CHECK(&self(x) == &x);
}

// NOLINTEND
