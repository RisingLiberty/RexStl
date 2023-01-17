// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec3.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std_extra/math/rad_angle.h"

REX_RSL_BEGIN_NAMESPACE

class Vec3
{
public:
  Vec3();
  Vec3(float32 x, float32 y, float32 z);

  Vec3 operator+(const Vec3& rhs) const;
  Vec3 operator-(const Vec3& rhs) const;
  Vec3 operator*(const float32 scalar) const;
  Vec3 operator/(const float32 scalar) const;

  Vec3& operator+=(const Vec3& rhs);
  Vec3& operator-=(const Vec3& rhs);
  Vec3& operator*=(const float32 scalar);
  Vec3& operator/=(const float32 scalar);

  Vec3 operator-() const;

  float32& operator[](card32 idx);
  float32 operator[](card32 idx) const;

  bool equals(const Vec3& other, const float32 comparison_threshold = s_ComparisonThreshold) const;

  bool operator==(const Vec3& other) const;
  bool operator!=(const Vec3& other) const;

  float32 dot(const Vec3& other) const;
  Vec3 cross(const Vec3& other) const;

  static Vec3 up();
  static Vec3 forward();
  static Vec3 right();
  static Vec3 down();
  static Vec3 backward();
  static Vec3 left();

  float32 length() const;
  float32 length_squared() const;

  Vec3& normalise();
  Vec3 normalised() const;

  Vec3& scale(const Vec3& scale);
  Vec3 scaled(const Vec3& scale) const;
  Vec3& floor(const Vec3& scale);
  Vec3 floored(const Vec3& scale) const;
  Vec3& ceil(const Vec3& scale);
  Vec3 ceiled(const Vec3& scale) const;

  bool is_zero() const;

  Vec3& rotate_x(const RadAngle angle);
  Vec3& rotate_y(const RadAngle angle);
  Vec3& rotate_z(const RadAngle angle);

  SmallStackString to_string() const;

public:
  float32 x, y, z;

private:
  static constexpr float32 s_ComparisonThreshold = 0.00005f;
};

REX_RSL_END_NAMESPACE