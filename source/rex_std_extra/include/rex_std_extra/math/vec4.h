// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec4.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/types.h"

namespace rsl { inline namespace v1 {

class vec4
{
public:
  vec4();
  vec4(const float32 x, const float32 y, const float32 z, const float32 w);

  float32& operator[](card32 idx);
  float32 operator[](card32 idx) const;

  vec4 operator+(const vec4& rhs) const;
  vec4 operator-(const vec4& rhs) const;
  vec4 operator*(const float32 scalar) const;
  vec4 operator/(const float32 scalar) const;

  vec4& operator+=(const vec4& rhs);
  vec4& operator-=(const vec4& rhs);
  vec4& operator*=(const float32 scalar);
  vec4& operator/=(const float32 scalar);

  vec4 operator-() const;

  bool operator==(const vec4& other) const;
  bool operator!=(const vec4& other) const;

  bool equals(const vec4& other, const float32 comparison_threshold = s_ComparisonThreshold) const;

  float32 dot(const vec4& other) const;

  float32 length() const;
  float32 length_squared() const;

  small_stack_string to_string() const;

public:
  float32 x, y, z, w;

private:
  static constexpr float32 s_ComparisonThreshold = 0.00005f;
};

}}