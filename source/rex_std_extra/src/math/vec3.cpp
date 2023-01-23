// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec3.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/math/vec3.h"

#include "rex_std_extra/math/float.h"
#include "rex_std/math.h"
#include "rex_std/format.h"

rsl::vec3::vec3()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
{
}

rsl::vec3::vec3(float32 _x, float32 _y, float32 _z)
    : x(_x)
    , y(_y)
    , z(_z)
{
}

rsl::vec3 rsl::vec3::operator+(const vec3& rhs) const
{
  return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}
rsl::vec3 rsl::vec3::operator-(const vec3& rhs) const
{
  return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}
rsl::vec3 rsl::vec3::operator*(const float32 scalar) const
{
  return vec3(x * scalar, y * scalar, z * scalar);
}
rsl::vec3 rsl::vec3::operator/(const float32 scalar) const
{
  return vec3(x / scalar, y / scalar, z / scalar);
}

rsl::vec3& rsl::vec3::operator+=(const vec3& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;

  return *this;
}
rsl::vec3& rsl::vec3::operator-=(const vec3& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;

  return *this;
}
rsl::vec3& rsl::vec3::operator*=(const float32 scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;

  return *this;
}
rsl::vec3& rsl::vec3::operator/=(const float32 scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;

  return *this;
}

rsl::vec3 rsl::vec3::operator-() const
{
  return vec3(-x, -y, -z);
}

float32& rsl::vec3::operator[](card32 idx)
{
  float32* data = reinterpret_cast<float32*>(this);
  return *(data + idx);
}
float32 rsl::vec3::operator[](card32 idx) const
{
  const float32* data = reinterpret_cast<const float32*>(this);
  return *(data + idx);
}

bool rsl::vec3::equals(const vec3& other, const float32 comparison_threshold) const
{
  return rsl::equals(x, other.x, comparison_threshold) && rsl::equals(y, other.y, comparison_threshold) && rsl::equals(z, other.z, comparison_threshold);
}

bool rsl::vec3::operator==(const vec3& other) const
{
  return equals(other);
}
bool rsl::vec3::operator!=(const vec3& other) const
{
  return !equals(other);
}

float32 rsl::vec3::dot(const vec3& other) const
{
  return x * other.x + y * other.y + z * other.z;
}
rsl::vec3 rsl::vec3::cross(const vec3& other) const
{
  return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

rsl::vec3 rsl::vec3::up()
{
  return vec3(0.0f, 1.0f, 0.0f);
}
rsl::vec3 rsl::vec3::forward()
{
  return vec3(0.0f, 0.0f, 1.0f);
}
rsl::vec3 rsl::vec3::right()
{
  return vec3(1.0f, 0.0f, 0.0f);
}
rsl::vec3 rsl::vec3::down()
{
  return -up();
}
rsl::vec3 rsl::vec3::backward()
{
  return -forward();
}
rsl::vec3 rsl::vec3::left()
{
  return -right();
}

float32 rsl::vec3::length() const
{
  return sqrt(length_squared());
}
float32 rsl::vec3::length_squared() const
{
  return dot(*this);
}

rsl::vec3& rsl::vec3::normalise()
{
  const float32 vec_inv_length = 1.0f / length();
  x *= vec_inv_length;
  y *= vec_inv_length;
  z *= vec_inv_length;
  return *this;
}
rsl::vec3 rsl::vec3::normalised() const
{
  const float32 vec_inv_length = 1.0f / length();
  return vec3(x * vec_inv_length, y * vec_inv_length, z * vec_inv_length);
}

rsl::vec3& rsl::vec3::scale(const vec3& scale)
{
  x *= scale.x;
  y *= scale.y;
  z *= scale.z;
  return *this;
}
rsl::vec3 rsl::vec3::scaled(const vec3& scale) const
{
  return vec3(*this).scale(scale);
}
rsl::vec3& rsl::vec3::floor(const vec3& floor)
{
  x = min(x, floor.x);
  y = min(y, floor.y);
  z = min(z, floor.z);
  return *this;
}
rsl::vec3 rsl::vec3::floored(const vec3& floor) const
{
  float32 new_x = min(x, floor.x);
  float32 new_y = min(y, floor.y);
  float32 new_z = min(z, floor.z);
  return vec3(new_x, new_y, new_z);
}
rsl::vec3& rsl::vec3::ceil(const vec3& ceil)
{
  x = max(x, ceil.x);
  y = max(y, ceil.y);
  z = max(z, ceil.z);
  return *this;
}
rsl::vec3 rsl::vec3::ceiled(const vec3& ceil) const
{
  float32 new_x = max(x, ceil.x);
  float32 new_y = max(y, ceil.y);
  float32 new_z = max(z, ceil.z);
  return vec3(new_x, new_y, new_z);
}

bool rsl::vec3::is_zero() const
{
  return equals(vec3(0.0f, 0.0f, 0.0f));
}

rsl::vec3& rsl::vec3::rotate_x(const RadAngle angle)
{
  const float32 copy_y = y;

  const float32 cosx = rsl::cos(angle.get());
  const float32 sinx = rsl::sin(angle.get());

  y = y * cosx - z * sinx;
  z = copy_y * sinx + z * cosx;

  return *this;
}
rsl::vec3& rsl::vec3::rotate_y(const RadAngle angle)
{
  const float32 copy_x = x;

  const float32 cosy = rsl::cos(angle.get());
  const float32 siny = rsl::sin(angle.get());

  x = x * cosy + z * siny;
  z = copy_x * -siny + z * cosy;
  return *this;
}
rsl::vec3& rsl::vec3::rotate_z(const RadAngle angle)
{
  const float32 copy_x = x;

  const float32 cosz = rsl::cos(angle.get());
  const float32 sinz = rsl::sin(angle.get());

  x = x * cosz - y * sinz;
  y = copy_x * sinz + y * cosz;

  return *this;
}

rsl::small_stack_string rsl::vec3::to_string() const
{
  return rsl::small_stack_string(rsl::format("(x: {}, y: {}, z: {})", x, y, z));
}