// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: matrix_33.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/array.h"
#include "rex_std/bonus/types.h"
#include "rex_std_extra/math/rad_angle.h"
#include "rex_std_extra/math/vec3.h"

REX_RSL_BEGIN_NAMESPACE

// Column major matrix
class Matrix33
{
public:
  Matrix33();
  Matrix33(float32 e00, float32 e10, float32 e20, float32 e01, float32 e11, float32 e21, float32 e02, float32 e12, float32 e22);

  float32& elem(const card32 row, const card32 column);
  float32 elem(const card32 row, const card32 column) const;

  Matrix33 operator*(const Matrix33& mat2) const;
  Matrix33& operator*=(const Matrix33& mat2);

  Matrix33& transpose();
  Matrix33& inverse();

  Matrix33 transposed() const;
  Matrix33 inversed() const;

  Vec3 operator*(const Vec3& v) const;
  Vec3 right() const;
  Vec3 up() const;
  Vec3 at() const;

  void set_right(const Vec3& right);
  void set_up(const Vec3& up);
  void set_at(const Vec3& at);

  Matrix33& set_scale(const Vec3& scale);
  void scale(const Vec3& scale);
  void scale(const float32 scale);

  static Matrix33 identity();
  static Matrix33 zero();

  void rotate_x(const RadAngle rot_x);
  void rotate_y(const RadAngle rot_y);
  void rotate_z(const RadAngle rot_z);

  Matrix33& set_rotate_x(const RadAngle angle);
  Matrix33& set_rotate_y(const RadAngle angle);
  Matrix33& set_rotate_z(const RadAngle angle);

private:
  void swap_elements(card32 row_idx, card32 column_idx);

private:
  using Column = Vec3;
  using Row    = Vec3;
  Array<Column, 3> m_elements;
};

REX_RSL_END_NAMESPACE