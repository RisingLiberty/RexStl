// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec2.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/math/vec2.h"

#include "rex_std/internal/math/cos.h"
#include "rex_std/internal/math/sin.h"
#include "rex_std/internal/math/sqrt.h"
#include "rex_std_extra/math/float.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::Vec2::Vec2()
    : x(0.0f)
    , y(0.0f)
{
}

rsl::Vec2::Vec2(const float32 _x, const float32 _y)
    : x(_x)
    , y(_y)
{
}

rsl::Vec2 rsl::Vec2::operator+(const Vec2& rhs) const
{
  return Vec2(x + rhs.x, y + rhs.y);
}
rsl::Vec2 rsl::Vec2::operator-(const Vec2& rhs) const
{
  return Vec2(x - rhs.x, y - rhs.y);
}
rsl::Vec2 rsl::Vec2::operator*(const float32 scalar) const
{
  return Vec2(x * scalar, y * scalar);
}
rsl::Vec2 rsl::Vec2::operator/(const float32 scalar) const
{
  return Vec2(x / scalar, y / scalar);
}

rsl::Vec2& rsl::Vec2::operator+=(const Vec2& rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}
rsl::Vec2& rsl::Vec2::operator-=(const Vec2& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}
rsl::Vec2& rsl::Vec2::operator*=(const float32 scalar)
{
  x *= scalar;
  y *= scalar;
  return *this;
}
rsl::Vec2& rsl::Vec2::operator/=(const float32 scalar)
{
  x /= scalar;
  y /= scalar;
  return *this;
}

float32& rsl::Vec2::operator[](card32 idx)
{
  float32* data = reinterpret_cast<float32*>(this);
  return *(data + idx);
}
float32 rsl::Vec2::operator[](card32 idx) const
{
  const float32* data = reinterpret_cast<const float32*>(this);
  return *(data + idx);
}

float32 rsl::Vec2::dot(const Vec2& other) const
{
  return (x * other.x) + (y * other.y);
}

bool rsl::Vec2::equals(const Vec2& other, const float32 comparison_threshold) const
{
  return rsl::equals(x, other.x, comparison_threshold) && rsl::equals(y, other.y, comparison_threshold);
}

bool rsl::Vec2::operator==(const Vec2& other) const
{
  return equals(other);
}
bool rsl::Vec2::operator!=(const Vec2& other) const
{
  return !equals(other);
}

rsl::Vec2 rsl::Vec2::operator-() const
{
  return Vec2(-x, -y);
}

rsl::Vec2& rsl::Vec2::set_length(const float32 length)
{
  return normalise() *= length;
}

rsl::Vec2& rsl::Vec2::normalise()
{
  float32 vec_inv_length = 1 / length();
  x *= vec_inv_length;
  y *= vec_inv_length;
  return *this;
}
rsl::Vec2 rsl::Vec2::normalised() const
{
  float32 vec_inv_length = 1 / length();
  return Vec2(x * vec_inv_length, y * vec_inv_length);
}

float32 rsl::Vec2::length() const
{
  return sqrtf(length_squared());
}
float32 rsl::Vec2::length_squared() const
{
  return dot(*this);
}

rsl::Vec2& rsl::Vec2::rotate(const RadAngle angle)
{
  const float32 copy_x = x;

  const float32 cosz = cosf(angle.get());
  const float32 sinz = sinf(angle.get());

  x = x * cosz + y * sinz;
  y = copy_x * -sinz + y * cosz;

  return *this;
}
rsl::Vec2 rsl::Vec2::rotated(const RadAngle angle) const
{
  return Vec2(*this).rotate(angle);
}

rsl::Vec2& rsl::Vec2::scale(const Vec2& scale)
{
  x *= scale.x;
  y *= scale.y;
  return *this;
}
rsl::Vec2 rsl::Vec2::scaled(const Vec2& scale) const
{
  return Vec2(*this).scale(scale);
}

rsl::Vec2& rsl::Vec2::floor(const Vec2& floor)
{
  x = min(x, floor.x);
  y = min(y, floor.y);
  return *this;
}
rsl::Vec2& rsl::Vec2::ceil(const Vec2& ceil)
{
  x = max(x, ceil.x);
  y = max(y, ceil.y);
  return *this;
}

bool rsl::Vec2::is_zero() const
{
  return equals(Vec2(0.0f, 0.0f));
}

rsl::SmallStackString rsl::Vec2::to_string() const
{
  return stack_string_from_message<SmallStackString>("(x: ", x, ", y: ", y, ")");
}

rsl::Vec2 rsl::operator*(const float32 scalar, const Vec2& vec2)
{
  return Vec2(vec2.x * scalar, vec2.y * scalar);
}