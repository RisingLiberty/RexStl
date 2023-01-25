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

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std_extra/math/rad_angle.h"

namespace rsl
{
  inline namespace v1
  {

    class vec3
    {
    public:
      vec3();
      vec3(float32 x, float32 y, float32 z);

      vec3 operator+(const vec3& rhs) const;
      vec3 operator-(const vec3& rhs) const;
      vec3 operator*(const float32 scalar) const;
      vec3 operator/(const float32 scalar) const;

      vec3& operator+=(const vec3& rhs);
      vec3& operator-=(const vec3& rhs);
      vec3& operator*=(const float32 scalar);
      vec3& operator/=(const float32 scalar);

      vec3 operator-() const;

      float32& operator[](card32 idx);
      float32 operator[](card32 idx) const;

      bool equals(const vec3& other, const float32 comparison_threshold = s_ComparisonThreshold) const;

      bool operator==(const vec3& other) const;
      bool operator!=(const vec3& other) const;

      float32 dot(const vec3& other) const;
      vec3 cross(const vec3& other) const;

      static vec3 up();
      static vec3 forward();
      static vec3 right();
      static vec3 down();
      static vec3 backward();
      static vec3 left();

      float32 length() const;
      float32 length_squared() const;

      vec3& normalise();
      vec3 normalised() const;

      vec3& scale(const vec3& scale);
      vec3 scaled(const vec3& scale) const;
      vec3& floor(const vec3& scale);
      vec3 floored(const vec3& scale) const;
      vec3& ceil(const vec3& scale);
      vec3 ceiled(const vec3& scale) const;

      bool is_zero() const;

      vec3& rotate_x(const RadAngle angle);
      vec3& rotate_y(const RadAngle angle);
      vec3& rotate_z(const RadAngle angle);

      small_stack_string to_string() const;

    public:
      float32 x, y, z;

    private:
      static constexpr float32 s_ComparisonThreshold = 0.00005f;
    };

  } // namespace v1
} // namespace rsl