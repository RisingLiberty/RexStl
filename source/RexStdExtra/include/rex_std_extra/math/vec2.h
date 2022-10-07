// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec2.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std_extra/math/rad_angle.h"

REX_RSL_BEGIN_NAMESPACE

class Vec2
{
public:
  Vec2();
  Vec2(const float32 x, const float32 y);

  Vec2 operator+(const Vec2& rhs) const;
  Vec2 operator-(const Vec2& rhs) const;
  Vec2 operator*(const float32 scalar) const;
  Vec2 operator/(const float32 scalar) const;

  Vec2& operator+=(const Vec2& rhs);
  Vec2& operator-=(const Vec2& rhs);
  Vec2& operator*=(const float32 scalar);
  Vec2& operator/=(const float32 scalar);

  float32& operator[](card32 idx);
  float32 operator[](card32 idx) const;

  float32 dot(const Vec2& other) const;

  bool equals(const Vec2& other, const float32 comparison_threshold = s_ComparisonThreshold) const;

  bool operator==(const Vec2& other) const;
  bool operator!=(const Vec2& other) const;

  Vec2 operator-() const;

  Vec2& set_length(const float32 length);

  Vec2& normalise();
  Vec2 normalised() const;

  float32 length() const;
  float32 length_squared() const;

  Vec2& rotate(const RadAngle angle);
  Vec2 rotated(const RadAngle angle) const;

  Vec2& scale(const Vec2& scale);
  Vec2 scaled(const Vec2& scale) const;

  Vec2& floor(const Vec2& floor);
  Vec2& ceil(const Vec2& ceil);

  bool is_zero() const;

  SmallStackString to_string() const;

public:
  float32 x, y;

private:
  static constexpr float32 s_ComparisonThreshold = 0.00005f;
};

Vec2 operator*(const float32 scalar, const Vec2& vec2);

REX_RSL_END_NAMESPACE