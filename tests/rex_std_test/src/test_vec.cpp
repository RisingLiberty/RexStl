// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_vec.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/math/float.h"
#include "rex_std/bonus/math/vec2.h"
#include "rex_std/bonus/math/vec3.h"
#include "rex_std/bonus/math/vec4.h"
#include "rex_std/numbers.h"

TEST_CASE("vec2 construction")
{
  rsl::vec2 zero;
  CHECK(zero.x == 0.0f);
  CHECK(zero.y == 0.0f);
  CHECK(zero.is_zero());

  rsl::vec2 v(1.0f, 2.0f);
  CHECK(v.x == 1.0f);
  CHECK(v.y == 2.0f);
  CHECK(v[0] == 1.0f);
  CHECK(v[1] == 2.0f);
  CHECK(!v.is_zero());

  v[0] = 3.0f;
  CHECK(v.x == 3.0f);

  const rsl::vec2 const_v(4.0f, 5.0f);
  CHECK(const_v[1] == 5.0f);
}

TEST_CASE("vec2 arithmetic")
{
  const rsl::vec2 a(1.0f, 2.0f);
  const rsl::vec2 b(3.0f, 5.0f);

  CHECK(a + b == rsl::vec2(4.0f, 7.0f));
  CHECK(b - a == rsl::vec2(2.0f, 3.0f));
  CHECK(a * 2.0f == rsl::vec2(2.0f, 4.0f));
  CHECK(2.0f * a == rsl::vec2(2.0f, 4.0f));
  CHECK(b / 2.0f == rsl::vec2(1.5f, 2.5f));
  CHECK(-a == rsl::vec2(-1.0f, -2.0f));

  rsl::vec2 c = a;
  c += b;
  CHECK(c == rsl::vec2(4.0f, 7.0f));
  c -= a;
  CHECK(c == b);
  c *= 2.0f;
  CHECK(c == rsl::vec2(6.0f, 10.0f));
  c /= 2.0f;
  CHECK(c == b);
}

TEST_CASE("vec2 comparison")
{
  const rsl::vec2 a(1.0f, 2.0f);
  CHECK(a == rsl::vec2(1.0f, 2.0f));
  CHECK(a != rsl::vec2(1.0f, 2.1f));

  // comparison uses a small threshold
  CHECK(a == rsl::vec2(1.000001f, 2.0f));
  CHECK(a.equals(rsl::vec2(1.05f, 2.0f), 0.1f));
  CHECK(!a.equals(rsl::vec2(1.05f, 2.0f), 0.01f));
}

TEST_CASE("vec2 geometry")
{
  const rsl::vec2 a(3.0f, 4.0f);

  CHECK(a.dot(rsl::vec2(1.0f, 0.0f)) == 3.0f);
  CHECK(a.dot(rsl::vec2(2.0f, 1.0f)) == 10.0f);
  CHECK(rsl::vec2(1.0f, 0.0f).dot(rsl::vec2(0.0f, 1.0f)) == 0.0f);

  CHECK(a.length_squared() == 25.0f);
  CHECK(rsl::equals(a.length(), 5.0f));

  // normalised returns a copy, normalise modifies in place
  const rsl::vec2 n = a.normalised();
  CHECK(rsl::equals(n.length(), 1.0f));
  CHECK(n == rsl::vec2(0.6f, 0.8f));
  CHECK(a == rsl::vec2(3.0f, 4.0f));

  rsl::vec2 b = a;
  b.normalise();
  CHECK(b == n);

  // set_length keeps the direction
  rsl::vec2 c = a;
  c.set_length(10.0f);
  CHECK(c == rsl::vec2(6.0f, 8.0f));

  // scale multiplies component wise
  CHECK(a.scaled(rsl::vec2(2.0f, 3.0f)) == rsl::vec2(6.0f, 12.0f));
  rsl::vec2 d = a;
  d.scale(rsl::vec2(0.5f, 0.25f));
  CHECK(d == rsl::vec2(1.5f, 1.0f));
}

TEST_CASE("vec2 rotation")
{
  constexpr float32 pi = rsl::pi_v<float32>;
  const rsl::vec2 v(1.0f, 0.0f);

  // rotation preserves the length
  const rsl::vec2 rotated = v.rotated(rsl::rad_angle(pi / 2));
  CHECK(rsl::equals(rotated.length(), 1.0f));
  CHECK(rsl::equals(rotated.dot(v), 0.0f));

  // a full rotation gives back the original vector
  CHECK(v.rotated(rsl::rad_angle(2 * pi)) == v);

  // rotating back and forth gives back the original vector
  rsl::vec2 w(2.0f, 3.0f);
  w.rotate(rsl::rad_angle(0.7f));
  w.rotate(rsl::rad_angle(-0.7f));
  CHECK(w == rsl::vec2(2.0f, 3.0f));

  // rotating by 0 doesn't do anything
  CHECK(v.rotated(rsl::rad_angle(0.0f)) == v);
}

TEST_CASE("vec3 construction")
{
  rsl::vec3 zero;
  CHECK(zero.x == 0.0f);
  CHECK(zero.y == 0.0f);
  CHECK(zero.z == 0.0f);
  CHECK(zero.is_zero());

  rsl::vec3 v(1.0f, 2.0f, 3.0f);
  CHECK(v[0] == 1.0f);
  CHECK(v[1] == 2.0f);
  CHECK(v[2] == 3.0f);
  CHECK(!v.is_zero());

  v[2] = 5.0f;
  CHECK(v.z == 5.0f);
}

TEST_CASE("vec3 arithmetic")
{
  const rsl::vec3 a(1.0f, 2.0f, 3.0f);
  const rsl::vec3 b(4.0f, 6.0f, 8.0f);

  CHECK(a + b == rsl::vec3(5.0f, 8.0f, 11.0f));
  CHECK(b - a == rsl::vec3(3.0f, 4.0f, 5.0f));
  CHECK(a * 2.0f == rsl::vec3(2.0f, 4.0f, 6.0f));
  CHECK(b / 2.0f == rsl::vec3(2.0f, 3.0f, 4.0f));
  CHECK(-a == rsl::vec3(-1.0f, -2.0f, -3.0f));

  rsl::vec3 c = a;
  c += b;
  CHECK(c == rsl::vec3(5.0f, 8.0f, 11.0f));
  c -= b;
  CHECK(c == a);
  c *= 3.0f;
  CHECK(c == rsl::vec3(3.0f, 6.0f, 9.0f));
  c /= 3.0f;
  CHECK(c == a);

  CHECK(a != b);
}

TEST_CASE("vec3 geometry")
{
  const rsl::vec3 a(1.0f, 2.0f, 2.0f);

  CHECK(a.dot(rsl::vec3(1.0f, 1.0f, 1.0f)) == 5.0f);
  CHECK(a.length_squared() == 9.0f);
  CHECK(rsl::equals(a.length(), 3.0f));

  const rsl::vec3 n = a.normalised();
  CHECK(rsl::equals(n.length(), 1.0f));
  rsl::vec3 b = a;
  b.normalise();
  CHECK(b == n);

  // cross product of the basis vectors
  CHECK(rsl::vec3::right().cross(rsl::vec3::up()) == rsl::vec3::forward());
  CHECK(rsl::vec3::up().cross(rsl::vec3::forward()) == rsl::vec3::right());
  CHECK(rsl::vec3::forward().cross(rsl::vec3::right()) == rsl::vec3::up());

  // the cross product is perpendicular to both inputs
  const rsl::vec3 c(3.0f, -1.0f, 2.0f);
  const rsl::vec3 cross = a.cross(c);
  CHECK(rsl::equals(cross.dot(a), 0.0f));
  CHECK(rsl::equals(cross.dot(c), 0.0f));
  CHECK(a.cross(a).is_zero());

  // scale
  CHECK(a.scaled(rsl::vec3(2.0f, 3.0f, 4.0f)) == rsl::vec3(2.0f, 6.0f, 8.0f));

  // floor and ceil take the component wise min and max
  CHECK(a.floored(rsl::vec3(0.0f, 5.0f, 1.0f)) == rsl::vec3(0.0f, 2.0f, 1.0f));
  CHECK(a.ceiled(rsl::vec3(0.0f, 5.0f, 1.0f)) == rsl::vec3(1.0f, 5.0f, 2.0f));
}

TEST_CASE("vec3 directions")
{
  CHECK(rsl::vec3::up() == rsl::vec3(0.0f, 1.0f, 0.0f));
  CHECK(rsl::vec3::down() == rsl::vec3(0.0f, -1.0f, 0.0f));
  CHECK(rsl::vec3::right() == rsl::vec3(1.0f, 0.0f, 0.0f));
  CHECK(rsl::vec3::left() == rsl::vec3(-1.0f, 0.0f, 0.0f));
  CHECK(rsl::vec3::forward() == rsl::vec3(0.0f, 0.0f, 1.0f));
  CHECK(rsl::vec3::backward() == rsl::vec3(0.0f, 0.0f, -1.0f));
}

TEST_CASE("vec3 rotation")
{
  constexpr float32 pi = rsl::pi_v<float32>;

  // rotating around an axis leaves the component along that axis untouched and preserves the length
  rsl::vec3 v(1.0f, 2.0f, 3.0f);
  v.rotate_x(rsl::rad_angle(pi / 3));
  CHECK(rsl::equals(v.x, 1.0f));
  CHECK(rsl::equals(v.length(), rsl::vec3(1.0f, 2.0f, 3.0f).length()));

  rsl::vec3 w(1.0f, 2.0f, 3.0f);
  w.rotate_y(rsl::rad_angle(pi / 3));
  CHECK(rsl::equals(w.y, 2.0f));
  CHECK(rsl::equals(w.length(), rsl::vec3(1.0f, 2.0f, 3.0f).length()));

  rsl::vec3 u(1.0f, 2.0f, 3.0f);
  u.rotate_z(rsl::rad_angle(pi / 3));
  CHECK(rsl::equals(u.z, 3.0f));
  CHECK(rsl::equals(u.length(), rsl::vec3(1.0f, 2.0f, 3.0f).length()));

  // a full rotation gives back the original vector
  rsl::vec3 full(1.0f, 2.0f, 3.0f);
  full.rotate_x(rsl::rad_angle(2 * pi));
  full.rotate_y(rsl::rad_angle(2 * pi));
  full.rotate_z(rsl::rad_angle(2 * pi));
  CHECK(full == rsl::vec3(1.0f, 2.0f, 3.0f));
}

TEST_CASE("vec4")
{
  // the default vec4 is the homogeneous origin (0, 0, 0, 1)
  rsl::vec4 origin;
  CHECK(origin.x == 0.0f);
  CHECK(origin.y == 0.0f);
  CHECK(origin.z == 0.0f);
  CHECK(origin.w == 1.0f);

  const rsl::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
  const rsl::vec4 b(2.0f, 2.0f, 2.0f, 2.0f);
  CHECK(a[0] == 1.0f);
  CHECK(a[3] == 4.0f);

  CHECK(a + b == rsl::vec4(3.0f, 4.0f, 5.0f, 6.0f));
  CHECK(a - b == rsl::vec4(-1.0f, 0.0f, 1.0f, 2.0f));
  CHECK(a * 2.0f == rsl::vec4(2.0f, 4.0f, 6.0f, 8.0f));
  CHECK(a / 2.0f == rsl::vec4(0.5f, 1.0f, 1.5f, 2.0f));
  CHECK(-a == rsl::vec4(-1.0f, -2.0f, -3.0f, -4.0f));

  rsl::vec4 c = a;
  c += b;
  c -= b;
  CHECK(c == a);
  c *= 2.0f;
  c /= 2.0f;
  CHECK(c == a);
  CHECK(c != b);

  CHECK(a.dot(b) == 20.0f);
  CHECK(a.length_squared() == 30.0f);
  CHECK(rsl::equals(b.length(), 4.0f));
  CHECK(a.equals(rsl::vec4(1.05f, 2.0f, 3.0f, 4.0f), 0.1f));
}

// NOLINTEND
