// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vec2.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std_extra/math/rad_angle.h"

namespace rsl
{
  inline namespace v1
  {

    class vec2
    {
    public:
      vec2();
      vec2(float32 x, float32 y);

      vec2 operator+(const vec2& rhs) const;
      vec2 operator-(const vec2& rhs) const;
      vec2 operator*(float32 scalar) const;
      vec2 operator/(float32 scalar) const;

      vec2& operator+=(const vec2& rhs);
      vec2& operator-=(const vec2& rhs);
      vec2& operator*=(float32 scalar);
      vec2& operator/=(float32 scalar);

      float32& operator[](card32 idx);
      float32 operator[](card32 idx) const;

      float32 dot(const vec2& other) const;

      bool equals(const vec2& other, float32 comparisonThreshold = s_comparison_threshold) const;

      bool operator==(const vec2& other) const;
      bool operator!=(const vec2& other) const;

      vec2 operator-() const;

      vec2& set_length(float32 length);

      vec2& normalise();
      vec2 normalised() const;

      float32 length() const;
      float32 length_squared() const;

      vec2& rotate(rad_angle angle);
      vec2 rotated(rad_angle angle) const;

      vec2& scale(const vec2& scale);
      vec2 scaled(const vec2& scale) const;

      vec2& floor(const vec2& floor);
      vec2& ceil(const vec2& ceil);

      bool is_zero() const;

      small_stack_string to_string() const;

    public:
      float32 x, y;

    private:
      static constexpr float32 s_comparison_threshold = 0.00005f;
    };

    vec2 operator*(float32 scalar, const vec2& vec2);

  } // namespace v1
} // namespace rsl