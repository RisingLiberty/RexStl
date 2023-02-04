// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec4.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/math/vec4.h"

#include "rex_std/format.h"
#include "rex_std_extra/math/float.h"

rsl::vec4::vec4()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
    , w(1.0f)
{
}

rsl::vec4::vec4(const float32 x, const float32 y, const float32 z, const float32 w)
    : x(x)
    , y(y)
    , z(z)
    , w(w)
{
}

float32& rsl::vec4::operator[](card32 idx)
{
  float32* data = reinterpret_cast<float32*>(this);
  return *(data + idx);
}
float rsl::vec4::operator[](card32 idx) const
{
  const float32* data = reinterpret_cast<const float32*>(this);
  return *(data + idx);
}

rsl::vec4 rsl::vec4::operator+(const vec4& rhs) const
{
  return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}
rsl::vec4 rsl::vec4::operator-(const vec4& rhs) const
{
  return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}
rsl::vec4 rsl::vec4::operator*(const float32 scalar) const
{
  return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}
rsl::vec4 rsl::vec4::operator/(const float32 scalar) const
{
  return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

rsl::vec4& rsl::vec4::operator+=(const vec4& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  w += rhs.w;
  return *this;
}
rsl::vec4& rsl::vec4::operator-=(const vec4& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  w -= rhs.w;
  return *this;
}
rsl::vec4& rsl::vec4::operator*=(const float32 scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}
rsl::vec4& rsl::vec4::operator/=(const float32 scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
  return *this;
}

rsl::vec4 rsl::vec4::operator-() const
{
  return vec4(-x, -y, -z, -w);
}

bool rsl::vec4::operator==(const vec4& other) const
{
  return equals(other);
}
bool rsl::vec4::operator!=(const vec4& other) const
{
  return !equals(other);
}

bool rsl::vec4::equals(const vec4& other, const float32 comparisonThreshold) const
{
  return rsl::equals(x, other.x, comparisonThreshold) && rsl::equals(y, other.y, comparisonThreshold) && rsl::equals(z, other.z, comparisonThreshold) && rsl::equals(w, other.w, comparisonThreshold);
}

float32 rsl::vec4::dot(const vec4& other) const
{
  return x * other.x + y * other.y + z * other.z + w * other.w;
}

float32 rsl::vec4::length() const
{
  return sqrt(length_squared());
}
float32 rsl::vec4::length_squared() const
{
  return dot(*this);
}

rsl::small_stack_string rsl::vec4::to_string() const
{
  return rsl::small_stack_string(rsl::format("(x: {}, y: {}, z: {}, w: {})", x, y, z, w));
}