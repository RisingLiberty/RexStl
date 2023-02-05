// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: matrix_33.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/math/matrix_33.h"

#include "rex_std/math.h"

rsl::matrix33::matrix33()
    : m_elements()
{
  m_elements[0].x = 1.0f;
  m_elements[1].y = 1.0f;
  m_elements[2].z = 1.0f;
}

rsl::matrix33::matrix33(float32 e00, float32 e10, float32 e20, float32 e01, float32 e11, float32 e21, float32 e02, float32 e12, float32 e22)
    : m_elements()
{
  m_elements[0] = {e00, e01, e02};
  m_elements[1] = {e10, e11, e12};
  m_elements[2] = {e20, e21, e22};
}

float32& rsl::matrix33::elem(card32 row, card32 column)
{
  return m_elements[column][row];
}
float32 rsl::matrix33::elem(card32 row, card32 column) const
{
  return m_elements[column][row];
}

rsl::matrix33 rsl::matrix33::operator*(const matrix33& other) const
{
  matrix33 res;

  res.elem(0, 0) = other.elem(0, 0) * elem(0, 0) + other.elem(1, 0) * elem(0, 1) + other.elem(2, 0) * elem(0, 2);
  res.elem(0, 1) = other.elem(0, 1) * elem(0, 0) + other.elem(1, 1) * elem(0, 1) + other.elem(2, 1) * elem(0, 2);
  res.elem(0, 2) = other.elem(0, 2) * elem(0, 0) + other.elem(1, 2) * elem(0, 1) + other.elem(2, 2) * elem(0, 2);

  res.elem(1, 0) = other.elem(0, 0) * elem(1, 0) + other.elem(1, 0) * elem(1, 1) + other.elem(2, 0) * elem(1, 2);
  res.elem(1, 1) = other.elem(0, 1) * elem(1, 0) + other.elem(1, 1) * elem(1, 1) + other.elem(2, 1) * elem(1, 2);
  res.elem(1, 2) = other.elem(0, 2) * elem(1, 0) + other.elem(1, 2) * elem(1, 1) + other.elem(2, 2) * elem(1, 2);

  res.elem(2, 0) = other.elem(0, 0) * elem(2, 0) + other.elem(1, 0) * elem(2, 1) + other.elem(2, 0) * elem(2, 2);
  res.elem(2, 1) = other.elem(0, 1) * elem(2, 0) + other.elem(1, 1) * elem(2, 1) + other.elem(2, 1) * elem(2, 2);
  res.elem(2, 2) = other.elem(0, 2) * elem(2, 0) + other.elem(1, 2) * elem(2, 1) + other.elem(2, 2) * elem(2, 2);

  return res;
}
rsl::matrix33& rsl::matrix33::operator*=(const matrix33& other)
{
  *this = *this * other;
  return *this;
}

rsl::matrix33& rsl::matrix33::transpose()
{
  swap_elements(1, 0);
  swap_elements(2, 0);
  swap_elements(1, 2);
  return *this;
}
rsl::matrix33& rsl::matrix33::inverse()
{
  matrix33 m((*this));
  float32 one_over_det =
      (m.elem(0, 0) * (m.elem(1, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(1, 2)) - m.elem(1, 0) * (m.elem(0, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(0, 2)) + m.elem(2, 0) * (m.elem(0, 1) * m.elem(1, 2) - m.elem(1, 1) * m.elem(0, 2)));

  if(one_over_det < 0.00001f)
    return *this;

  one_over_det = 1.0f / one_over_det;

  elem(0, 0) = one_over_det * (m.elem(1, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(1, 2));
  elem(0, 1) = -one_over_det * (m.elem(0, 1) * m.elem(2, 2) - m.elem(2, 1) * m.elem(0, 2));
  elem(0, 2) = one_over_det * (m.elem(0, 1) * m.elem(1, 2) - m.elem(1, 1) * m.elem(0, 2));

  elem(1, 0) = -one_over_det * (m.elem(1, 0) * m.elem(2, 2) - m.elem(2, 0) * m.elem(1, 2));
  elem(1, 1) = one_over_det * (m.elem(0, 0) * m.elem(2, 2) - m.elem(2, 0) * m.elem(0, 2));
  elem(1, 2) = -one_over_det * (m.elem(0, 0) * m.elem(1, 2) - m.elem(1, 0) * m.elem(0, 2));

  elem(2, 0) = one_over_det * (m.elem(1, 0) * m.elem(2, 1) - m.elem(2, 0) * m.elem(1, 1));
  elem(2, 1) = -one_over_det * (m.elem(0, 0) * m.elem(2, 1) - m.elem(2, 0) * m.elem(0, 1));
  elem(2, 2) = one_over_det * (m.elem(0, 0) * m.elem(1, 1) - m.elem(1, 0) * m.elem(0, 1));

  return *this;
}

rsl::matrix33 rsl::matrix33::transposed() const
{
  matrix33 tmp = *this;
  return tmp.transpose();
}
rsl::matrix33 rsl::matrix33::inversed() const
{
  matrix33 tmp = *this;
  return tmp.inverse();
}

rsl::vec3 rsl::matrix33::operator*(const vec3& v) const
{
  return vec3(elem(0, 0) * v.x + elem(0, 1) * v.y + elem(0, 2) * v.z, elem(1, 0) * v.x + elem(1, 1) * v.y + elem(1, 2) * v.z, elem(2, 0) * v.x + elem(2, 1) * v.y + elem(2, 2) * v.z);
}
rsl::vec3 rsl::matrix33::right() const
{
  return vec3(elem(0, 0), elem(1, 0), elem(2, 0));
}
rsl::vec3 rsl::matrix33::up() const
{
  return vec3(elem(0, 1), elem(1, 1), elem(2, 1));
}
rsl::vec3 rsl::matrix33::at() const
{
  return vec3(elem(0, 2), elem(1, 2), elem(2, 2));
}

void rsl::matrix33::set_right(const vec3& right)
{
  elem(0, 0) = right.x;
  elem(1, 0) = right.y;
  elem(2, 0) = right.z;
}
void rsl::matrix33::set_up(const vec3& up)
{
  elem(0, 1) = up.x;
  elem(1, 1) = up.y;
  elem(2, 1) = up.z;
}
void rsl::matrix33::set_at(const vec3& at)
{
  elem(0, 2) = at.x;
  elem(1, 2) = at.y;
  elem(2, 2) = at.z;
}

rsl::matrix33& rsl::matrix33::set_scale(const vec3& scale)
{
  elem(0, 0) = scale.x;
  elem(1, 1) = scale.y;
  elem(2, 2) = scale.z;

  elem(1, 0) = elem(2, 0) = 0;
  elem(0, 1) = elem(2, 1) = 0;
  elem(0, 2) = elem(1, 2) = 0;

  return *this;
}
void rsl::matrix33::scale(const vec3& scale)
{
  for(card32 i = 0; i < 2; ++i)
  {
    elem(i, 0) *= scale.x;
    elem(i, 1) *= scale.y;
    elem(i, 2) *= scale.z;
  }
}
void rsl::matrix33::scale(const float32 scale)
{
  for(card32 i = 0; i < 2; ++i)
  {
    elem(i, 0) *= scale;
    elem(i, 1) *= scale;
    elem(i, 2) *= scale;
  }
}

rsl::matrix33 rsl::matrix33::identity()
{
  return matrix33(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
rsl::matrix33 rsl::matrix33::zero()
{
  return matrix33(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void rsl::matrix33::rotate_x(const rad_angle angle)
{
  const float32 sa = rsl::sin(angle.get());
  const float32 ca = rsl::cos(angle.get());

  float32 temp_1i = 0.0f;

  for(card32 i = 0; i < 3; ++i)
  {
    temp_1i    = elem(1, i);
    elem(1, i) = temp_1i * ca - elem(2, i) * sa;
    elem(2, i) = temp_1i * sa + elem(2, i) * ca;
  }
}
void rsl::matrix33::rotate_y(const rad_angle angle)
{
  const float32 sa = rsl::sin(angle.get());
  const float32 ca = rsl::cos(angle.get());

  float32 temp_0i = 0.0f;

  for(card32 i = 0; i < 3; ++i)
  {
    temp_0i    = elem(0, i);
    elem(0, i) = temp_0i * ca - elem(2, i) * sa;
    elem(2, i) = elem(2, i) * ca - temp_0i * sa;
  }
}
void rsl::matrix33::rotate_z(const rad_angle angle)
{
  const float32 sa = rsl::sin(angle.get());
  const float32 ca = rsl::cos(angle.get());

  float32 temp_0i = 0.0f;

  for(card32 i = 0; i < 3; ++i)
  {
    temp_0i    = elem(0, i);
    elem(0, i) = temp_0i * ca - elem(1, i) * sa;
    elem(1, i) = temp_0i * sa + elem(1, i) * ca;
  }
}

rsl::matrix33& rsl::matrix33::set_rotate_x(const rad_angle angle)
{
  const float32 cosine = rsl::cos(angle.get());
  const float32 sine   = rsl::sin(angle.get());

  elem(1, 1) = cosine;
  elem(1, 2) = -sine;
  elem(2, 1) = sine;
  elem(2, 2) = cosine;

  return *this;
}
rsl::matrix33& rsl::matrix33::set_rotate_y(const rad_angle angle)
{
  const float32 cosine = rsl::cos(angle.get());
  const float32 sine   = rsl::sin(angle.get());

  elem(0, 0) = cosine;
  elem(0, 2) = sine;
  elem(2, 0) = -sine;
  elem(2, 2) = cosine;

  return *this;
}
rsl::matrix33& rsl::matrix33::set_rotate_z(const rad_angle angle)
{
  const float32 cosine = rsl::cos(angle.get());
  const float32 sine   = rsl::sin(angle.get());

  elem(0, 0) = cosine;
  elem(0, 1) = -sine;
  elem(1, 0) = sine;
  elem(1, 1) = cosine;

  return *this;
}

void rsl::matrix33::swap_elements(card32 rowIdx, card32 columnIdx)
{
  const float32 t         = elem(rowIdx, columnIdx);
  elem(rowIdx, columnIdx) = elem(columnIdx, rowIdx); // NOLINT(readability-suspicious-call-argument)
  elem(columnIdx, rowIdx) = t;                       // NOLINT(readability-suspicious-call-argument)
}