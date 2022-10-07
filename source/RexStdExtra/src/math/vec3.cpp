// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec3.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/math/vec3.h"

#include "rex_std_extra/math/float.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::Vec3::Vec3()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
{
}

rsl::Vec3::Vec3(float32 _x, float32 _y, float32 _z)
    : x(_x)
    , y(_y)
    , z(_z)
{
}

rsl::Vec3 rsl::Vec3::operator+(const Vec3& rhs) const
{
  return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}
rsl::Vec3 rsl::Vec3::operator-(const Vec3& rhs) const
{
  return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}
rsl::Vec3 rsl::Vec3::operator*(const float32 scalar) const
{
  return Vec3(x * scalar, y * scalar, z * scalar);
}
rsl::Vec3 rsl::Vec3::operator/(const float32 scalar) const
{
  return Vec3(x / scalar, y / scalar, z / scalar);
}

rsl::Vec3& rsl::Vec3::operator+=(const Vec3& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;

  return *this;
}
rsl::Vec3& rsl::Vec3::operator-=(const Vec3& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;

  return *this;
}
rsl::Vec3& rsl::Vec3::operator*=(const float32 scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;

  return *this;
}
rsl::Vec3& rsl::Vec3::operator/=(const float32 scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;

  return *this;
}

rsl::Vec3 rsl::Vec3::operator-() const
{
  return Vec3(-x, -y, -z);
}

float32& rsl::Vec3::operator[](card32 idx)
{
  float32* data = reinterpret_cast<float32*>(this);
  return *(data + idx);
}
float32 rsl::Vec3::operator[](card32 idx) const
{
  const float32* data = reinterpret_cast<const float32*>(this);
  return *(data + idx);
}

bool rsl::Vec3::equals(const Vec3& other, const float32 comparison_threshold) const
{
  return rsl::equals(x, other.x, comparison_threshold) && rsl::equals(y, other.y, comparison_threshold) && rsl::equals(z, other.z, comparison_threshold);
}

bool rsl::Vec3::operator==(const Vec3& other) const
{
  return equals(other);
}
bool rsl::Vec3::operator!=(const Vec3& other) const
{
  return !equals(other);
}

float32 rsl::Vec3::dot(const Vec3& other) const
{
  return x * other.x + y * other.y + z * other.z;
}
rsl::Vec3 rsl::Vec3::cross(const Vec3& other) const
{
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

rsl::Vec3 rsl::Vec3::up()
{
  return Vec3(0.0f, 1.0f, 0.0f);
}
rsl::Vec3 rsl::Vec3::forward()
{
  return Vec3(0.0f, 0.0f, 1.0f);
}
rsl::Vec3 rsl::Vec3::right()
{
  return Vec3(1.0f, 0.0f, 0.0f);
}
rsl::Vec3 rsl::Vec3::down()
{
  return -up();
}
rsl::Vec3 rsl::Vec3::backward()
{
  return -forward();
}
rsl::Vec3 rsl::Vec3::left()
{
  return -right();
}

float32 rsl::Vec3::length() const
{
  return sqrt(length_squared());
}
float32 rsl::Vec3::length_squared() const
{
  return dot(*this);
}

rsl::Vec3& rsl::Vec3::normalise()
{
  const float32 vec_inv_length = 1.0f / length();
  x *= vec_inv_length;
  y *= vec_inv_length;
  z *= vec_inv_length;
  return *this;
}
rsl::Vec3 rsl::Vec3::normalised() const
{
  const float32 vec_inv_length = 1.0f / length();
  return Vec3(x * vec_inv_length, y * vec_inv_length, z * vec_inv_length);
}

rsl::Vec3& rsl::Vec3::scale(const Vec3& scale)
{
  x *= scale.x;
  y *= scale.y;
  z *= scale.z;
  return *this;
}
rsl::Vec3 rsl::Vec3::scaled(const Vec3& scale) const
{
  return Vec3(*this).scale(scale);
}
rsl::Vec3& rsl::Vec3::floor(const Vec3& floor)
{
  x = min(x, floor.x);
  y = min(y, floor.y);
  z = min(z, floor.z);
  return *this;
}
rsl::Vec3 rsl::Vec3::floored(const Vec3& floor) const
{
  float32 new_x = min(x, floor.x);
  float32 new_y = min(y, floor.y);
  float32 new_z = min(z, floor.z);
  return Vec3(new_x, new_y, new_z);
}
rsl::Vec3& rsl::Vec3::ceil(const Vec3& ceil)
{
  x = max(x, ceil.x);
  y = max(y, ceil.y);
  z = max(z, ceil.z);
  return *this;
}
rsl::Vec3 rsl::Vec3::ceiled(const Vec3& ceil) const
{
  float32 new_x = max(x, ceil.x);
  float32 new_y = max(y, ceil.y);
  float32 new_z = max(z, ceil.z);
  return Vec3(new_x, new_y, new_z);
}

bool rsl::Vec3::is_zero() const
{
  return equals(Vec3(0.0f, 0.0f, 0.0f));
}

rsl::Vec3& rsl::Vec3::rotate_x(const RadAngle angle)
{
  const float32 copy_y = y;

  const float32 cosx = cos(angle.get());
  const float32 sinx = sin(angle.get());

  y = y * cosx - z * sinx;
  z = copy_y * sinx + z * cosx;

  return *this;
}
rsl::Vec3& rsl::Vec3::rotate_y(const RadAngle angle)
{
  const float32 copy_x = x;

  const float32 cosy = cos(angle.get());
  const float32 siny = sin(angle.get());

  x = x * cosy + z * siny;
  z = copy_x * -siny + z * cosy;
  return *this;
}
rsl::Vec3& rsl::Vec3::rotate_z(const RadAngle angle)
{
  const float32 copy_x = x;

  const float32 cosz = cos(angle.get());
  const float32 sinz = sin(angle.get());

  x = x * cosz - y * sinz;
  y = copy_x * sinz + y * cosz;

  return *this;
}

rsl::SmallStackString rsl::Vec3::to_string() const
{
  return stack_string_from_message<SmallStackString>("(x: ", x, ", y: ", y, ", z: ", z, ")");
}