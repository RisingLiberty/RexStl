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

#include "rex_std_extra/containers/array.h"
#include "rex_std_extra/math/rad_angle.h"
#include "rex_std_extra/math/vec3.h"
#include "rex_std_extra/math/vec4.h"

REX_RSL_BEGIN_NAMESPACE

// Column major matrix
class Matrix44
{
public:
  Matrix44();
  Matrix44(float32 e00, float32 e10, float32 e20, float32 e30, float32 e01, float32 e11, float32 e21, float32 e31, float32 e02, float32 e12, float32 e22, float32 e32, float32 e03, float32 e13, float32 e23, float32 e33);

  float32& elem(const card32 row, const card32 column);
  float32 elem(const card32 row, const card32 column) const;

  Matrix44 operator*(const Matrix44& mat2) const;
  Matrix44& operator*=(const Matrix44& mat2);

  Matrix44& transpose();
  Matrix44& inverse();

  Matrix44 transposed() const;
  Matrix44 inversed() const;

  Vec3 operator*(const Vec3& v) const;
  Vec3 translation() const;
  Vec3 right() const;
  Vec3 up() const;
  Vec3 at() const;

  void set_right(const Vec3& right);
  void set_up(const Vec3& up);
  void set_at(const Vec3& at);

  void scale(const Vec3& scale);
  void scale(const float32 scale);

  static Matrix44 identity();
  static Matrix44 zero();

  void rotate_x(const RadAngle rot_x);
  void rotate_y(const RadAngle rot_y);
  void rotate_z(const RadAngle rot_z);

  Matrix44& set_rotate_x(const RadAngle angle);
  Matrix44& set_rotate_y(const RadAngle angle);
  Matrix44& set_rotate_z(const RadAngle angle);

  Matrix44& set_translation(const Vec3& translation);
  Matrix44& set_scale(const Vec3& scale);

private:
  void swap_elements(card32 row_idx, card32 column_idx);
  float32 mul_element(card32 row, card32 col, const Matrix44& m2);
  Matrix44 simd_mul(const Matrix44& m2);

private:
  using Column = Vec4;
  using Row    = Vec4;
  Array<Column, 4> m_elements;
};

REX_RSL_END_NAMESPACE