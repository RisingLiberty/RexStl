// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: matrix_33.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/array.h"
#include "rex_std/bonus/math/rad_angle.h"
#include "rex_std/bonus/math/vec3.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {

    // Column major matrix
    class matrix33
    {
    public:
      matrix33();
      matrix33(float32 e00, float32 e10, float32 e20, float32 e01, float32 e11, float32 e21, float32 e02, float32 e12, float32 e22);

      float32& elem(card32 row, card32 column);
      float32 elem(card32 row, card32 column) const;

      matrix33 operator*(const matrix33& other) const;
      matrix33& operator*=(const matrix33& other);

      matrix33& transpose();
      matrix33& inverse();

      matrix33 transposed() const;
      matrix33 inversed() const;

      vec3 operator*(const vec3& v) const;
      vec3 right() const;
      vec3 up() const;
      vec3 at() const;

      void set_right(const vec3& right);
      void set_up(const vec3& up);
      void set_at(const vec3& at);

      matrix33& set_scale(const vec3& scale);
      void scale(const vec3& scale);
      void scale(float32 scale);

      static matrix33 identity();
      static matrix33 zero();

      void rotate_x(rad_angle angle);
      void rotate_y(rad_angle angle);
      void rotate_z(rad_angle angle);

      matrix33& set_rotate_x(rad_angle angle);
      matrix33& set_rotate_y(rad_angle angle);
      matrix33& set_rotate_z(rad_angle angle);

    private:
      void swap_elements(card32 rowIdx, card32 columnIdx);

    private:
      using Column = vec3;
      using Row    = vec3;
      rsl::array<Column, 3> m_elements;
    };

  } // namespace v1
} // namespace rsl