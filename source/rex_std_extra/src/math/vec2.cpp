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

#include "rex_std/format.h"
#include "rex_std/internal/math/cos.h"
#include "rex_std/internal/math/sin.h"
#include "rex_std/internal/math/sqrt.h"
#include "rex_std_extra/math/float.h"

rsl::vec2::vec2()
    : x(0.0f)
    , y(0.0f)
{
}

rsl::vec2::vec2(const float32 _x, const float32 _y)
    : x(_x)
    , y(_y)
{
}

rsl::vec2 rsl::vec2::operator+(const vec2& rhs) const
{
  return vec2(x + rhs.x, y + rhs.y);
}
rsl::vec2 rsl::vec2::operator-(const vec2& rhs) const
{
  return vec2(x - rhs.x, y - rhs.y);
}
rsl::vec2 rsl::vec2::operator*(const float32 scalar) const
{
  return vec2(x * scalar, y * scalar);
}
rsl::vec2 rsl::vec2::operator/(const float32 scalar) const
{
  return vec2(x / scalar, y / scalar);
}

rsl::vec2& rsl::vec2::operator+=(const vec2& rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}
rsl::vec2& rsl::vec2::operator-=(const vec2& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}
rsl::vec2& rsl::vec2::operator*=(const float32 scalar)
{
  x *= scalar;
  y *= scalar;
  return *this;
}
rsl::vec2& rsl::vec2::operator/=(const float32 scalar)
{
  x /= scalar;
  y /= scalar;
  return *this;
}

float32& rsl::vec2::operator[](card32 idx)
{
  float32* data = reinterpret_cast<float32*>(this);
  return *(data + idx);
}
float32 rsl::vec2::operator[](card32 idx) const
{
  const float32* data = reinterpret_cast<const float32*>(this);
  return *(data + idx);
}

float32 rsl::vec2::dot(const vec2& other) const
{
  return (x * other.x) + (y * other.y);
}

bool rsl::vec2::equals(const vec2& other, const float32 comparison_threshold) const
{
  return rsl::equals(x, other.x, comparison_threshold) && rsl::equals(y, other.y, comparison_threshold);
}

bool rsl::vec2::operator==(const vec2& other) const
{
  return equals(other);
}
bool rsl::vec2::operator!=(const vec2& other) const
{
  return !equals(other);
}

rsl::vec2 rsl::vec2::operator-() const
{
  return vec2(-x, -y);
}

rsl::vec2& rsl::vec2::set_length(const float32 length)
{
  return normalise() *= length;
}

rsl::vec2& rsl::vec2::normalise()
{
  float32 vec_inv_length = 1 / length();
  x *= vec_inv_length;
  y *= vec_inv_length;
  return *this;
}
rsl::vec2 rsl::vec2::normalised() const
{
  float32 vec_inv_length = 1 / length();
  return vec2(x * vec_inv_length, y * vec_inv_length);
}

float32 rsl::vec2::length() const
{
  return sqrtf(length_squared());
}
float32 rsl::vec2::length_squared() const
{
  return dot(*this);
}

rsl::vec2& rsl::vec2::rotate(const RadAngle angle)
{
  const float32 copy_x = x;

  const float32 cosz = cosf(angle.get());
  const float32 sinz = sinf(angle.get());

  x = x * cosz + y * sinz;
  y = copy_x * -sinz + y * cosz;

  return *this;
}
rsl::vec2 rsl::vec2::rotated(const RadAngle angle) const
{
  return vec2(*this).rotate(angle);
}

rsl::vec2& rsl::vec2::scale(const vec2& scale)
{
  x *= scale.x;
  y *= scale.y;
  return *this;
}
rsl::vec2 rsl::vec2::scaled(const vec2& scale) const
{
  return vec2(*this).scale(scale);
}

rsl::vec2& rsl::vec2::floor(const vec2& floor)
{
  x = min(x, floor.x);
  y = min(y, floor.y);
  return *this;
}
rsl::vec2& rsl::vec2::ceil(const vec2& ceil)
{
  x = max(x, ceil.x);
  y = max(y, ceil.y);
  return *this;
}

bool rsl::vec2::is_zero() const
{
  return equals(vec2(0.0f, 0.0f));
}

rsl::small_stack_string rsl::vec2::to_string() const
{
  return rsl::small_stack_string(rsl::format("(x: {}, y: {})", x, y));
}

rsl::vec2 rsl::operator*(const float32 scalar, const vec2& vec2)
{
  return rsl::vec2(vec2.x * scalar, vec2.y * scalar);
}