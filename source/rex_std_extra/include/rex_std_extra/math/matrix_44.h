// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: matrix_44.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/array.h"
#include "rex_std/bonus/types.h"
#include "rex_std_extra/math/rad_angle.h"
#include "rex_std_extra/math/vec3.h"
#include "rex_std_extra/math/vec4.h"

namespace rsl
{
  inline namespace v1
  {

    // Column major matrix
    class matrix44
    {
    public:
      matrix44();
      matrix44(float32 e00, float32 e10, float32 e20, float32 e30, float32 e01, float32 e11, float32 e21, float32 e31, float32 e02, float32 e12, float32 e22, float32 e32, float32 e03, float32 e13, float32 e23, float32 e33);

      float32& elem(card32 row, card32 column);
      float32 elem(card32 row, card32 column) const;

      matrix44 operator*(const matrix44& other) const;
      matrix44& operator*=(const matrix44& other);

      matrix44& transpose();
      matrix44& inverse();

      matrix44 transposed() const;
      matrix44 inversed() const;

      vec3 operator*(const vec3& v) const;
      vec3 translation() const;
      vec3 right() const;
      vec3 up() const;
      vec3 at() const;

      void set_right(const vec3& right);
      void set_up(const vec3& up);
      void set_at(const vec3& at);

      void scale(const vec3& scale);
      void scale(float32 scale);

      static matrix44 identity();
      static matrix44 zero();

      void rotate_x(rad_angle angle);
      void rotate_y(rad_angle angle);
      void rotate_z(rad_angle angle);

      matrix44& set_rotate_x(rad_angle angle);
      matrix44& set_rotate_y(rad_angle angle);
      matrix44& set_rotate_z(rad_angle angle);

      matrix44& set_translation(const vec3& translation);
      matrix44& set_scale(const vec3& scale);

    private:
      void swap_elements(card32 rowIdx, card32 columnIdx);
      float32 mul_element(card32 row, card32 col, const matrix44& m2);
      matrix44 simd_mul(const matrix44& m2);

    private:
      using Column = vec4;
      using Row    = vec4;
      rsl::array<Column, 4> m_elements;
    };

  } // namespace v1
} // namespace rsl