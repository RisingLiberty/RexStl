// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: matrix_44.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/math/matrix_44.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::matrix44::matrix44()
    : m_elements({{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}})
{
}
rsl::matrix44::matrix44(float32 e00, float32 e10, float32 e20, float32 e30, float32 e01, float32 e11, float32 e21, float32 e31, float32 e02, float32 e12, float32 e22, float32 e32, float32 e03, float32 e13, float32 e23, float32 e33)
    : m_elements({{{e00, e01, e02, e03}, {e10, e11, e12, e13}, {e20, e21, e22, e23}, {e30, e31, e32, e33}}})
{
}

float32& rsl::matrix44::elem(const card32 row, const card32 column)
{
  return m_elements[column][row];
}
float32 rsl::matrix44::elem(const card32 row, const card32 column) const
{
  return m_elements[column][row];
}

rsl::matrix44 rsl::matrix44::operator*(const matrix44& other) const
{
  rsl::matrix44 tmp;
  tmp.simd_mul(other);
  return tmp;
}
rsl::matrix44& rsl::matrix44::operator*=(const matrix44& other)
{
  simd_mul(other);
  return *this;
}

rsl::matrix44& rsl::matrix44::transpose()
{
  swap_elements(0, 1);
  swap_elements(0, 2);
  swap_elements(0, 3);
  swap_elements(1, 2);
  swap_elements(1, 3);
  swap_elements(2, 3);

  return *this;
}
rsl::matrix44& rsl::matrix44::inverse()
{
  if(abs(elem(3, 3) - 1.0f) > 0.001f)
    return *this;
  if((abs(elem(3, 0)) > 0.001f) || (abs(elem(3, 1)) > 0.001f) || (abs(elem(3, 2)) > 0.001f))
    return *this;

  matrix44 m((*this));
  float32 one_over_det =
      (m.elem(0, 0) * (m.elem(1, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(1, 2)) - m.elem(1, 0) * (m.elem(0, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(0, 2)) + m.elem(2, 0) * (m.elem(0, 1) * m.elem(1, 2) - m.elem(1, 1) * m.elem(0, 2)));

  if(one_over_det < 0.00001f)
    return (*this);

  one_over_det = 1.0f / one_over_det;

  elem(0, 0) = one_over_det * (m.elem(1, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(1, 2));
  elem(0, 1) = -one_over_det * (m.elem(0, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(0, 2));
  elem(0, 2) = one_over_det * (m.elem(0, 1) * m.elem(1, 2) - m.elem(1, 1) * m.elem(0, 2));
  elem(0, 3) = -(elem(0, 0) * m.elem(0, 3) + elem(0, 1) * m.elem(1, 3) + elem(0, 2) * m.elem(2, 3));

  elem(1, 0) = -one_over_det * (m.elem(1, 0) * m.elem(2, 2) - m.elem(2, 0) * m.elem(1, 2));
  elem(1, 1) = one_over_det * (m.elem(0, 0) * m.elem(2, 2) - m.elem(2, 0) * m.elem(0, 2));
  elem(1, 2) = -one_over_det * (m.elem(0, 0) * m.elem(1, 2) - m.elem(1, 0) * m.elem(0, 2));
  elem(1, 3) = -(elem(1, 0) * m.elem(0, 3) + elem(1, 1) * m.elem(1, 3) + elem(1, 2) * m.elem(2, 3));

  elem(2, 0) = one_over_det * (m.elem(1, 0) * m.elem(2, 1) - m.elem(2, 0) * m.elem(1, 1));
  elem(2, 1) = -one_over_det * (m.elem(0, 0) * m.elem(2, 1) - m.elem(2, 0) * m.elem(0, 1));
  elem(2, 2) = one_over_det * (m.elem(0, 0) * m.elem(1, 1) - m.elem(1, 0) * m.elem(0, 1));
  elem(2, 3) = -(elem(2, 0) * m.elem(0, 3) + elem(2, 1) * m.elem(1, 3) + elem(2, 2) * m.elem(2, 3));

  elem(3, 0) = 0;
  elem(3, 1) = 0;
  elem(3, 2) = 0;
  elem(3, 3) = 1.0f;

  return *this;
}

rsl::matrix44 rsl::matrix44::transposed() const
{
  matrix44 tmp = *this;

  tmp.swap_elements(0, 1);
  tmp.swap_elements(0, 2);
  tmp.swap_elements(0, 3);
  tmp.swap_elements(1, 2);
  tmp.swap_elements(1, 3);
  tmp.swap_elements(2, 3);

  return tmp;
}
rsl::matrix44 rsl::matrix44::inversed() const
{
  matrix44 tmp = *this;
  return tmp.inverse();
}

rsl::vec3 rsl::matrix44::operator*(const vec3& vec) const
{
  return vec3(elem(0, 0) * vec.x + elem(0, 1) * vec.y + elem(0, 2) * vec.z + elem(0, 3), elem(1, 0) * vec.x + elem(1, 1) * vec.y + elem(1, 2) * vec.z + elem(1, 3), elem(2, 0) * vec.x + elem(2, 1) * vec.y + elem(2, 2) * vec.z + elem(2, 3));
}
rsl::vec3 rsl::matrix44::translation() const
{
  const float32 x = elem(3, 0);
  const float32 y = elem(3, 1);
  const float32 z = elem(3, 2);

  return vec3(x, y, z);
}
rsl::vec3 rsl::matrix44::right() const
{
  const float32 x = elem(0, 0);
  const float32 y = elem(0, 1);
  const float32 z = elem(0, 2);

  return vec3(x, y, z);
}
rsl::vec3 rsl::matrix44::up() const
{
  const float32 x = elem(1, 0);
  const float32 y = elem(1, 1);
  const float32 z = elem(1, 2);

  return vec3(x, y, z);
}
rsl::vec3 rsl::matrix44::at() const
{
  const float32 x = elem(2, 0);
  const float32 y = elem(2, 1);
  const float32 z = elem(2, 2);

  return vec3(x, y, z);
}

void rsl::matrix44::set_right(const vec3& right)
{
  elem(0, 0) = right.x;
  elem(0, 1) = right.y;
  elem(0, 2) = right.z;
}
void rsl::matrix44::set_up(const vec3& up)
{
  elem(1, 0) = up.x;
  elem(1, 1) = up.y;
  elem(1, 2) = up.z;
}
void rsl::matrix44::set_at(const vec3& at)
{
  elem(2, 0) = at.x;
  elem(2, 1) = at.y;
  elem(2, 2) = at.z;
}

void rsl::matrix44::scale(const vec3& scale)
{
  for(card32 i = 0; i < 3; ++i)
  {
    elem(0, i) *= scale.x;
    elem(1, i) *= scale.y;
    elem(2, i) *= scale.z;
  }
}
void rsl::matrix44::scale(const float32 scale)
{
  for(card32 i = 0; i < 3; ++i)
  {
    elem(0, i) *= scale;
    elem(1, i) *= scale;
    elem(2, i) *= scale;
  }
}

rsl::matrix44 rsl::matrix44::identity()
{
  return matrix44(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
rsl::matrix44 rsl::matrix44::zero()
{
  return matrix44(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void rsl::matrix44::rotate_x(const RadAngle angle)
{
  const float32 sa = sinf(angle.get());
  const float32 ca = cosf(angle.get());

  float32 temp_1i = 0.0f;

  for(card32 i = 0; i < 4; ++i)
  {
    temp_1i    = elem(1, i);
    elem(1, i) = temp_1i * ca - elem(2, i) * sa;
    elem(2, i) = temp_1i * sa + elem(2, i) * ca;
  }
}
void rsl::matrix44::rotate_y(const RadAngle angle)
{
  const float32 sa = sinf(angle.get());
  const float32 ca = cosf(angle.get());

  float32 temp_0i = 0.0f;

  for(card32 i = 0; i < 4; ++i)
  {
    temp_0i    = elem(0, i);
    elem(0, i) = temp_0i * ca + elem(2, i) * sa;
    elem(2, i) = elem(2, i) * ca - temp_0i * sa;
  }
}
void rsl::matrix44::rotate_z(const RadAngle angle)
{
  const float32 sa = sinf(angle.get());
  const float32 ca = cosf(angle.get());

  float32 temp_0i = 0.0f;

  for(card32 i = 0; i < 4; ++i)
  {
    temp_0i    = elem(0, i);
    elem(0, i) = temp_0i * ca - elem(1, i) * sa;
    elem(1, i) = temp_0i * sa + elem(1, i) * ca;
  }
}

rsl::matrix44& rsl::matrix44::set_rotate_x(const RadAngle angle)
{
  const float32 sine   = sinf(angle.get());
  const float32 cosine = cosf(angle.get());

  elem(1, 1) = cosine;
  elem(1, 2) = -sine;
  elem(2, 1) = sine;
  elem(2, 2) = cosine;

  return *this;
}
rsl::matrix44& rsl::matrix44::set_rotate_y(const RadAngle angle)
{
  const float32 sine   = sinf(angle.get());
  const float32 cosine = cosf(angle.get());

  elem(0, 0) = cosine;
  elem(0, 2) = sine;
  elem(2, 0) = -sine;
  elem(2, 2) = cosine;

  return *this;
}
rsl::matrix44& rsl::matrix44::set_rotate_z(const RadAngle angle)
{
  const float32 sine   = sinf(angle.get());
  const float32 cosine = cosf(angle.get());

  elem(0, 0) = cosine;
  elem(0, 1) = -sine;
  elem(1, 0) = sine;
  elem(1, 1) = cosine;

  return *this;
}

rsl::matrix44& rsl::matrix44::set_translation(const vec3& translation)
{
  elem(0, 3) = translation.x;
  elem(1, 3) = translation.y;
  elem(2, 3) = translation.z;

  return *this;
}
rsl::matrix44& rsl::matrix44::set_scale(const vec3& scale)
{
  elem(0, 0) = scale.x;
  elem(1, 1) = scale.y;
  elem(2, 2) = scale.z;

  return *this;
}

float32 rsl::matrix44::mul_element(card32 row, card32 col, const matrix44& m2)
{
  return elem(row, 0) * m2.elem(0, col) + elem(row, 1) * m2.elem(1, col) + elem(row, 2) * m2.elem(2, col) + elem(row, 3) * m2.elem(3, col);
}

rsl::matrix44 rsl::matrix44::simd_mul(const matrix44& m2)
{
  float32 e00 = mul_element(0, 0, m2);
  float32 e01 = mul_element(0, 1, m2);
  float32 e02 = mul_element(0, 2, m2);
  float32 e03 = mul_element(0, 3, m2);

  float32 e10 = mul_element(1, 0, m2);
  float32 e11 = mul_element(1, 1, m2);
  float32 e12 = mul_element(1, 2, m2);
  float32 e13 = mul_element(1, 3, m2);

  float32 e20 = mul_element(2, 0, m2);
  float32 e21 = mul_element(2, 1, m2);
  float32 e22 = mul_element(2, 2, m2);
  float32 e23 = mul_element(2, 3, m2);

  float32 e30 = mul_element(3, 0, m2);
  float32 e31 = mul_element(3, 1, m2);
  float32 e32 = mul_element(3, 2, m2);
  float32 e33 = mul_element(3, 3, m2);

  return matrix44(e00, e01, e02, e03, e10, e11, e12, e13, e20, e21, e22, e23, e30, e31, e32, e33);
}

void rsl::matrix44::swap_elements(card32 row_idx, card32 column_idx)
{
  float32 t                 = elem(row_idx, column_idx);
  elem(row_idx, column_idx) = elem(column_idx, row_idx);
  elem(column_idx, row_idx) = t;
}