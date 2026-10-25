// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_hash.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/functional/hash_lower.h"
#include "rex_std/bonus/utility/hash.h"
#include "rex_std/functional.h"
#include "rex_std/string.h"
#include "rex_std/string_view.h"

namespace hash_test
{
  enum class color
  {
    red   = 1,
    green = 2,
    blue  = 3
  };

  enum plain_enum
  {
    plain_a = 10,
    plain_b = 20
  };
} // namespace hash_test

TEST_CASE("hash integral types")
{
  // integral types hash to their own value
  CHECK(rsl::hash<int8>()(5) == 5);
  CHECK(rsl::hash<int16>()(300) == 300);
  CHECK(rsl::hash<int32>()(70000) == 70000);
  CHECK(rsl::hash<uint8>()(200) == 200);
  CHECK(rsl::hash<uint16>()(60000) == 60000);
  CHECK(rsl::hash<uint32>()(4000000000u) == static_cast<rsl::hash_result>(4000000000u));
  CHECK(rsl::hash<bool>()(true) == 1);
  CHECK(rsl::hash<bool>()(false) == 0);
  CHECK(rsl::hash<char8>()('a') == static_cast<rsl::hash_result>('a'));

  // equal values give equal hashes
  CHECK(rsl::hash<int64>()(123456789) == rsl::hash<int64>()(123456789));
  CHECK(rsl::hash<uint64>()(123456789) == rsl::hash<uint64>()(123456789));

  // different small values give different hashes
  CHECK(rsl::hash<int32>()(1) != rsl::hash<int32>()(2));

  // hashes are constexpr
  static_assert(rsl::hash<int32>()(42) == 42);
}

TEST_CASE("hash floating point types")
{
  CHECK(rsl::hash<float32>()(1.0f) == rsl::hash<float32>()(1.0f));
  CHECK(rsl::hash<float64>()(2.0) == rsl::hash<float64>()(2.0));
  CHECK(rsl::hash<float32>()(1.0f) != rsl::hash<float32>()(2.0f));
}

TEST_CASE("hash enums")
{
  CHECK(rsl::hash<hash_test::color>()(hash_test::color::red) == 1);
  CHECK(rsl::hash<hash_test::color>()(hash_test::color::blue) == 3);
  CHECK(rsl::hash<hash_test::plain_enum>()(hash_test::plain_b) == 20);
  CHECK(rsl::hash<hash_test::color>()(hash_test::color::red) != rsl::hash<hash_test::color>()(hash_test::color::green));
}

TEST_CASE("hash pointers")
{
  int x = 0;
  int y = 0;

  int* px = &x;
  int* py = &y;

  CHECK(rsl::hash<int*>()(px) == rsl::hash<int*>()(&x));
  CHECK(rsl::hash<int*>()(px) != rsl::hash<int*>()(py));
  CHECK(rsl::hash<int*>()(nullptr) == 0);
  CHECK(rsl::hash<rsl::nullptr_t>()(nullptr) == 0);
}

TEST_CASE("hash combine")
{
  const rsl::hash_result a = rsl::hash<int32>()(1);
  const rsl::hash_result b = rsl::hash<int32>()(2);

  // deterministic
  CHECK(rsl::hash_combine(a, b) == rsl::hash_combine(a, b));

  // the order of combination matters
  CHECK(rsl::hash_combine(a, b) != rsl::hash_combine(b, a));

  // combining changes the hash
  CHECK(rsl::hash_combine(a, b) != a);
  CHECK(rsl::hash_combine(a, b) != b);

  static_assert(rsl::hash_combine(1, 2) == rsl::hash_combine(1, 2));
}

TEST_CASE("comp hash")
{
  CHECK(rsl::comp_hash(42) == rsl::hash<int32>()(42));
  CHECK(rsl::comp_hash(hash_test::color::green) == 2);
}

TEST_CASE("hash strings")
{
  rsl::string str1("hello world");
  rsl::string str2("hello world");
  rsl::string str3("Hello World");
  rsl::string empty("");

  // equal strings have equal hashes
  CHECK(rsl::hash<rsl::string>()(str1) == rsl::hash<rsl::string>()(str2));

  // hashing is case sensitive
  CHECK(rsl::hash<rsl::string>()(str1) != rsl::hash<rsl::string>()(str3));

  // different strings have different hashes
  CHECK(rsl::hash<rsl::string>()(str1) != rsl::hash<rsl::string>()(empty));
  CHECK(rsl::hash<rsl::string>()(rsl::string("a")) != rsl::hash<rsl::string>()(rsl::string("b")));

  // strings and string views of the same characters have the same hash
  rsl::string_view view1 = "hello world";
  CHECK(rsl::hash<rsl::string_view>()(view1) == rsl::hash<rsl::string>()(str1));

  // a sub view hashes only the characters it views
  rsl::string_view sub_view = rsl::string_view(str1).substr(0, 5);
  CHECK(rsl::hash<rsl::string_view>()(sub_view) == rsl::hash<rsl::string_view>()(rsl::string_view("hello")));
}

TEST_CASE("hash lower")
{
  rsl::string_view lower = "hello world";
  rsl::string_view upper = "HELLO WORLD";
  rsl::string_view mixed = "HeLLo WoRLd";
  rsl::string_view other = "goodbye world";

  rsl::hash_lower<rsl::string_view> hasher;
  CHECK(hasher(lower) == hasher(upper));
  CHECK(hasher(lower) == hasher(mixed));
  CHECK(hasher(lower) != hasher(other));

  // hashing as lower case gives the same hash as hashing the lower case string
  CHECK(hasher(upper) == rsl::hash<rsl::string_view>()(lower));
}

TEST_CASE("crc32")
{
  // the same input always gives the same output
  CHECK(rsl::crc32::compute("abc", 3) == rsl::crc32::compute("abc", 3));
  CHECK(rsl::crc32::compute("abc", 3) != rsl::crc32::compute("abd", 3));

  // only the first 'len' characters are processed
  CHECK(rsl::crc32::compute("abcdef", 3) == rsl::crc32::compute("abcxyz", 3));

  // case insensitive computation
  CHECK(rsl::crc32::compute_as_lower("ABC", 3) == rsl::crc32::compute("abc", 3));
  CHECK(rsl::crc32::compute_as_lower("aBc", 3) == rsl::crc32::compute_as_lower("AbC", 3));

  // the CRC32 of an empty buffer is 0
  CHECK(rsl::crc32::compute("", 0) == 0);

  // standard CRC-32 (ISO-HDLC) check value
  CHECK(rsl::crc32::compute("123456789", 9) == 0xCBF43926u);
}

TEST_CASE("hash val")
{
  constexpr rsl::hash_val val1(5);
  constexpr rsl::hash_val val2(5);
  constexpr rsl::hash_val val3(6);

  static_assert(val1.value() == 5);
  CHECK(val1 == val2);
  CHECK(val1 != val3);

  CHECK(rsl::hash_val::invalid().value() == (rsl::numeric_limits<card64>::max)());
  CHECK(rsl::hash_val::invalid() != val1);
}

// NOLINTEND
