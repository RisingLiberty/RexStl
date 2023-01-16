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

#include "rex_std_extra/math/float.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::Vec4::Vec4()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
    , w(1.0f)
{
}

rsl::Vec4::Vec4(const float32 _x, const float32 _y, const float32 _z, const float32 _w)
    : x(_x)
    , y(_y)
    , z(_z)
    , w(_w)
{
}

float32& rsl::Vec4::operator[](card32 idx)
{
  float32* data = reinterpret_cast<float32*>(this);
  return *(data + idx);
}
float rsl::Vec4::operator[](card32 idx) const
{
  const float32* data = reinterpret_cast<const float32*>(this);
  return *(data + idx);
}

rsl::Vec4 rsl::Vec4::operator+(const Vec4& rhs) const
{
  return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}
rsl::Vec4 rsl::Vec4::operator-(const Vec4& rhs) const
{
  return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}
rsl::Vec4 rsl::Vec4::operator*(const float32 scalar) const
{
  return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}
rsl::Vec4 rsl::Vec4::operator/(const float32 scalar) const
{
  return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

rsl::Vec4& rsl::Vec4::operator+=(const Vec4& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  w += rhs.w;
  return *this;
}
rsl::Vec4& rsl::Vec4::operator-=(const Vec4& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  w -= rhs.w;
  return *this;
}
rsl::Vec4& rsl::Vec4::operator*=(const float32 scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}
rsl::Vec4& rsl::Vec4::operator/=(const float32 scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
  return *this;
}

rsl::Vec4 rsl::Vec4::operator-() const
{
  return Vec4(-x, -y, -z, -w);
}

bool rsl::Vec4::operator==(const Vec4& other) const
{
  return equals(other);
}
bool rsl::Vec4::operator!=(const Vec4& other) const
{
  return !equals(other);
}

bool rsl::Vec4::equals(const Vec4& other, const float32 comparison_threshold) const
{
  return rsl::equals(x, other.x, comparison_threshold) && rsl::equals(y, other.y, comparison_threshold) && rsl::equals(z, other.z, comparison_threshold) && rsl::equals(w, other.w, comparison_threshold);
}

float32 rsl::Vec4::dot(const Vec4& other) const
{
  return x * other.x + y * other.y + z * other.z + w * other.w;
}

float32 rsl::Vec4::length() const
{
  return sqrt(length_squared());
}
float32 rsl::Vec4::length_squared() const
{
  return dot(*this);
}

rsl::SmallStackString rsl::Vec4::to_string() const
{
  return stack_string_from_message<SmallStackString>("(x: ", x, ", y: ", y, "z: ", z, ", w: ", w, ")");
}