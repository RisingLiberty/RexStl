// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec4.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

class Vec4
{
public:
  Vec4();
  Vec4(const float32 x, const float32 y, const float32 z, const float32 w);

  float32& operator[](card32 idx);
  float32 operator[](card32 idx) const;

  Vec4 operator+(const Vec4& rhs) const;
  Vec4 operator-(const Vec4& rhs) const;
  Vec4 operator*(const float32 scalar) const;
  Vec4 operator/(const float32 scalar) const;

  Vec4& operator+=(const Vec4& rhs);
  Vec4& operator-=(const Vec4& rhs);
  Vec4& operator*=(const float32 scalar);
  Vec4& operator/=(const float32 scalar);

  Vec4 operator-() const;

  bool operator==(const Vec4& other) const;
  bool operator!=(const Vec4& other) const;

  bool equals(const Vec4& other, const float32 comparison_threshold = s_ComparisonThreshold) const;

  float32 dot(const Vec4& other) const;

  float32 length() const;
  float32 length_squared() const;

  SmallStackString to_string() const;

public:
  float32 x, y, z, w;

private:
  static constexpr float32 s_ComparisonThreshold = 0.00005f;
};

REX_RSL_END_NAMESPACE