// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_flags.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/types.h"
#include "rex_std/bonus/utility/flags.h"
#include "rex_std/type_traits.h"

namespace flags_test
{
  enum class scoped_flags : uint32
  {
    none  = 0,
    read  = 1 << 0,
    write = 1 << 1,
    exec  = 1 << 2,
    all   = read | write | exec
  };

  enum unscoped_flags
  {
    unscoped_none = 0,
    unscoped_a    = 1 << 0,
    unscoped_b    = 1 << 1,
    unscoped_c    = 1 << 2
  };
} // namespace flags_test

TEST_CASE("no flags")
{
  CHECK(rsl::no_flags() == 0);
  static_assert(rsl::is_same_v<decltype(rsl::no_flags()), card32>);

  CHECK(rsl::no_flags<uint8>() == 0);
  static_assert(rsl::is_same_v<decltype(rsl::no_flags<uint8>()), uint8>);
}

TEST_CASE("has flag integral")
{
  CHECK(rsl::has_flag(0b0101, 0b0001));
  CHECK(rsl::has_flag(0b0101, 0b0100));
  CHECK(rsl::has_flag(0b0101, 0b0101));
  CHECK(!rsl::has_flag(0b0101, 0b0010));
  CHECK(!rsl::has_flag(0b0101, 0b0111));

  // every value has the empty flag
  CHECK(rsl::has_flag(0b0101, 0));
  CHECK(rsl::has_flag(0, 0));
  CHECK(!rsl::has_flag(0, 1));

  // mixing integer types
  CHECK(rsl::has_flag(static_cast<uint8>(0xF0), 0x10u));
  CHECK(rsl::has_flag(0xFFFFFFFFFFFFFFFFull, static_cast<uint8>(0x80)));
  CHECK(!rsl::has_flag(static_cast<uint16>(0x00FF), 0x0100));

  // constexpr usage
  static_assert(rsl::has_flag(0b11, 0b10));
  static_assert(!rsl::has_flag(0b01, 0b10));
}

TEST_CASE("has flag enums")
{
  using flags_test::scoped_flags;

  CHECK(rsl::has_flag(scoped_flags::all, scoped_flags::read));
  CHECK(rsl::has_flag(scoped_flags::all, scoped_flags::write));
  CHECK(rsl::has_flag(scoped_flags::all, scoped_flags::exec));
  CHECK(!rsl::has_flag(scoped_flags::read, scoped_flags::write));
  CHECK(!rsl::has_flag(scoped_flags::read, scoped_flags::all));

  CHECK(rsl::has_flag(flags_test::unscoped_a, flags_test::unscoped_a));
  CHECK(!rsl::has_flag(flags_test::unscoped_a, flags_test::unscoped_b));

  // mixing enums and integers
  CHECK(rsl::has_flag(scoped_flags::all, 1));
  CHECK(rsl::has_flag(7, scoped_flags::exec));
  CHECK(!rsl::has_flag(1, scoped_flags::exec));

  static_assert(rsl::has_flag(scoped_flags::all, scoped_flags::exec));
}

TEST_CASE("add flag to rvalue")
{
  using flags_test::scoped_flags;

  // adding to a temporary returns the combined value
  CHECK(rsl::add_flag(0b0001, 0b0100) == 0b0101);
  CHECK(rsl::add_flag(0b0101, 0b0100) == 0b0101);
  CHECK(rsl::add_flag(0, 0) == 0);

  // the return type matches the type of the value
  static_assert(rsl::is_same_v<decltype(rsl::add_flag(static_cast<uint8>(1), 2)), uint8>);

  // enums
  const scoped_flags read_write = rsl::add_flag(scoped_flags::read, scoped_flags::write);
  CHECK(rsl::has_flag(read_write, scoped_flags::read));
  CHECK(rsl::has_flag(read_write, scoped_flags::write));
  CHECK(!rsl::has_flag(read_write, scoped_flags::exec));

  // passing an lvalue would pick the lvalue overload, which only compiles for uint64, so we chain the calls
  const scoped_flags all = rsl::add_flag(rsl::add_flag(scoped_flags::read, scoped_flags::write), scoped_flags::exec);
  CHECK(all == scoped_flags::all);

  static_assert(rsl::add_flag(1, 2) == 3);
}

TEST_CASE("add flag to lvalue")
{
  // add_flag on an lvalue modifies the value in place and returns the new value
  // at the moment this only compiles for uint64 as add_flag uses static_cast<uint64&>(val)
  uint64 val = 0b0001;
  uint64 res = rsl::add_flag(val, 0b0100);
  CHECK(val == 0b0101);
  CHECK(res == 0b0101);

  rsl::add_flag(val, 0b0001);
  CHECK(val == 0b0101);

  rsl::add_flag(val, 1ull << 63);
  CHECK(rsl::has_flag(val, 1ull << 63));
  CHECK(rsl::has_flag(val, 0b0101));
}

// NOLINTEND
