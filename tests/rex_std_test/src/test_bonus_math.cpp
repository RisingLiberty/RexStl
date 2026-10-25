// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_bonus_math.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/math/deg_angle.h"
#include "rex_std/bonus/math/float.h"
#include "rex_std/bonus/math/is_posinf.h"
#include "rex_std/bonus/math/lerp.h"
#include "rex_std/bonus/math/normalise.h"
#include "rex_std/bonus/math/point.h"
#include "rex_std/bonus/math/rad_angle.h"
#include "rex_std/bonus/math/trunc.h"
#include "rex_std/limits.h"
#include "rex_std/numbers.h"

TEST_CASE("point construction")
{
  constexpr rsl::pointi32 zero;
  static_assert(zero.x == 0);
  static_assert(zero.y == 0);

  constexpr rsl::pointi32 p(3, 4);
  static_assert(p.x == 3);
  static_assert(p.y == 4);

  rsl::point<float32> pf(1.5f, 2.5f);
  CHECK(pf.x == 1.5f);
  CHECK(pf.y == 2.5f);
}

TEST_CASE("point arithmetic with points")
{
  constexpr rsl::pointi32 a(6, 8);
  constexpr rsl::pointi32 b(2, 4);

  static_assert(a + b == rsl::pointi32(8, 12));
  static_assert(a - b == rsl::pointi32(4, 4));
  static_assert(a * b == rsl::pointi32(12, 32));
  static_assert(a / b == rsl::pointi32(3, 2));
  static_assert(-a == rsl::pointi32(-6, -8));

  rsl::pointi32 c = a;
  c += b;
  CHECK(c == rsl::pointi32(8, 12));
  c -= b;
  CHECK(c == a);
  c *= b;
  CHECK(c == rsl::pointi32(12, 32));
  c /= b;
  CHECK(c == a);
}

TEST_CASE("point arithmetic with scalars")
{
  constexpr rsl::pointi32 a(6, 8);

  CHECK(a + int16(2) == rsl::pointi32(8, 10));
  CHECK(a - int16(2) == rsl::pointi32(4, 6));
  CHECK(a * int16(2) == rsl::pointi32(12, 16));
  CHECK(a / int16(2) == rsl::pointi32(3, 4));

  rsl::pointi32 c = a;
  c += int16(1);
  CHECK(c == rsl::pointi32(7, 9));
  c -= int16(1);
  CHECK(c == a);
  c *= int16(3);
  CHECK(c == rsl::pointi32(18, 24));
  c /= int16(3);
  CHECK(c == a);
}

TEST_CASE("point comparison")
{
  constexpr rsl::pointi16 a(1, 2);
  static_assert(a == rsl::pointi16(1, 2));
  static_assert(a != rsl::pointi16(2, 1));
  static_assert(a != rsl::pointi16(1, 3));
  CHECK(a == rsl::pointi16(1, 2));
  CHECK(a != rsl::pointi16(0, 2));
}

TEST_CASE("deg angle")
{
  constexpr rsl::deg_angle zero;
  static_assert(zero.get() == 0.0f);

  constexpr rsl::deg_angle a(90.0f);
  constexpr rsl::deg_angle b(45.0f);

  static_assert((a + b).get() == 135.0f);
  static_assert((a - b).get() == 45.0f);
  static_assert((a * rsl::deg_angle(2.0f)).get() == 180.0f);
  static_assert((a / rsl::deg_angle(2.0f)).get() == 45.0f);

  CHECK(a > b);
  CHECK(a >= b);
  CHECK(b < a);
  CHECK(b <= a);
  CHECK(a == rsl::deg_angle(90.0f));
  CHECK(a != b);

  rsl::deg_angle c = a;
  c += b;
  CHECK(c.get() == 135.0f);
  c -= b;
  CHECK(c.get() == 90.0f);
  c *= rsl::deg_angle(2.0f);
  CHECK(c.get() == 180.0f);
  c /= rsl::deg_angle(4.0f);
  CHECK(c.get() == 45.0f);
  c.set(30.0f);
  CHECK(c.get() == 30.0f);

  // conversion to radians
  CHECK(rsl::equals(rsl::deg_angle(180.0f).to_rad(), rsl::pi_v<float32>));
  CHECK(rsl::equals(rsl::deg_angle(90.0f).to_rad(), rsl::pi_v<float32> / 2));
  CHECK(rsl::equals(rsl::deg_angle(0.0f).to_rad(), 0.0f));

  // literal
  CHECK((90_deg).get() == 90.0f);
}

TEST_CASE("rad angle")
{
  constexpr float32 pi = rsl::pi_v<float32>;

  // note: default constructing a rad_angle is ambiguous at the moment (rad_angle() and rad_angle(float32 = 0))
  constexpr rsl::rad_angle zero(0.0f);
  static_assert(zero.get() == 0.0f);

  constexpr rsl::rad_angle a(2.0f);
  constexpr rsl::rad_angle b(0.5f);

  static_assert((a + b).get() == 2.5f);
  static_assert((a - b).get() == 1.5f);
  static_assert((a * b).get() == 1.0f);
  static_assert((a / b).get() == 4.0f);

  CHECK(a > b);
  CHECK(a >= b);
  CHECK(b < a);
  CHECK(b <= a);
  CHECK(a == rsl::rad_angle(2.0f));
  CHECK(a != b);

  rsl::rad_angle c = a;
  c += b;
  CHECK(c.get() == 2.5f);
  c -= b;
  CHECK(c.get() == 2.0f);
  c *= b;
  CHECK(c.get() == 1.0f);
  c /= b;
  CHECK(c.get() == 2.0f);
  c.set(1.0f);
  CHECK(c.get() == 1.0f);

  // conversion to degrees
  CHECK(rsl::equals(rsl::rad_angle(pi).to_deg(), 180.0f));
  CHECK(rsl::equals(rsl::rad_angle(pi / 2).to_deg(), 90.0f));

  // converting back and forth gives the same angle
  CHECK(rsl::equals(rsl::deg_angle(rsl::rad_angle(1.234f).to_deg()).to_rad(), 1.234f));

  // literal
  CHECK((2_rad).get() == 2.0f);
}

TEST_CASE("lerp")
{
  CHECK(rsl::lerp(0.0f, 10.0f, 0.0f) == 0.0f);
  CHECK(rsl::lerp(0.0f, 10.0f, 1.0f) == 10.0f);
  CHECK(rsl::lerp(0.0f, 10.0f, 0.5f) == 5.0f);
  CHECK(rsl::lerp(10.0f, 20.0f, 0.25f) == 12.5f);
  CHECK(rsl::lerp(10.0f, 0.0f, 0.25f) == 7.5f);

  // extrapolation
  CHECK(rsl::lerp(0.0f, 10.0f, 2.0f) == 20.0f);
  CHECK(rsl::lerp(0.0f, 10.0f, -1.0f) == -10.0f);

  static_assert(rsl::lerp(0.0f, 4.0f, 0.5f) == 2.0f);
}

TEST_CASE("unorm and snorm")
{
  static_assert(rsl::unorm_to_snorm(0.0f) == -1.0f);
  static_assert(rsl::unorm_to_snorm(0.5f) == 0.0f);
  static_assert(rsl::unorm_to_snorm(1.0f) == 1.0f);

  static_assert(rsl::snorm_to_unorm(-1.0f) == 0.0f);
  static_assert(rsl::snorm_to_unorm(0.0f) == 0.5f);
  static_assert(rsl::snorm_to_unorm(1.0f) == 1.0f);

  CHECK(rsl::snorm_to_unorm(rsl::unorm_to_snorm(0.3f)) == 0.3f);
}

TEST_CASE("trunc")
{
  CHECK(rsl::trunc<int>(2.7f) == 2);
  CHECK(rsl::trunc<int>(-2.7f) == -2);
  CHECK(rsl::trunc<int>(5.0) == 5);
  CHECK(rsl::trunc<uint8>(300) == 44);
  static_assert(rsl::trunc<int>(1.9) == 1);
}

TEST_CASE("float equals")
{
  CHECK(rsl::equals(1.0f, 1.0f));
  CHECK(rsl::equals(1.0f, 1.00001f));
  CHECK(!rsl::equals(1.0f, 1.001f));
  CHECK(rsl::equals(1.0f, 1.001f, 0.01f));
  CHECK(!rsl::equals(1.0f, -1.0f));
  CHECK(rsl::equals(-0.0f, 0.0f));
}

TEST_CASE("is posinf")
{
  CHECK(rsl::is_posinf(rsl::numeric_limits<float32>::infinity()));
  CHECK(rsl::is_posinf(rsl::numeric_limits<float64>::infinity()));
  CHECK(!rsl::is_posinf(-rsl::numeric_limits<float32>::infinity()));
  CHECK(!rsl::is_posinf(1.0f));
  CHECK(!rsl::is_posinf((rsl::numeric_limits<float32>::max)()));
}

// NOLINTEND
