// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_matrix.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/math/float.h"
#include "rex_std/bonus/math/matrix_33.h"
#include "rex_std/bonus/math/matrix_44.h"
#include "rex_std/numbers.h"

namespace matrix_test
{
  template <typename Matrix>
  bool equals(const Matrix& lhs, const Matrix& rhs, card32 size)
  {
    for(card32 row = 0; row < size; ++row)
    {
      for(card32 col = 0; col < size; ++col)
      {
        if(!rsl::equals(lhs.elem(row, col), rhs.elem(row, col), 0.001f))
        {
          return false;
        }
      }
    }
    return true;
  }

  bool equals(const rsl::matrix33& lhs, const rsl::matrix33& rhs)
  {
    return equals(lhs, rhs, 3);
  }
  bool equals(const rsl::matrix44& lhs, const rsl::matrix44& rhs)
  {
    return equals(lhs, rhs, 4);
  }

  rsl::matrix33 create_matrix33()
  {
    rsl::matrix33 m;
    float32 val = 1.0f;
    for(card32 row = 0; row < 3; ++row)
    {
      for(card32 col = 0; col < 3; ++col)
      {
        m.elem(row, col) = val * val - row;
        val += 1.0f;
      }
    }
    return m;
  }

  rsl::matrix44 create_matrix44()
  {
    rsl::matrix44 m;
    float32 val = 1.0f;
    for(card32 row = 0; row < 4; ++row)
    {
      for(card32 col = 0; col < 4; ++col)
      {
        m.elem(row, col) = (row == col) ? val + 5.0f : val * 0.5f;
        val += 1.0f;
      }
    }
    return m;
  }
} // namespace matrix_test

TEST_CASE("matrix33 construction")
{
  // the default matrix is the identity matrix
  rsl::matrix33 m;
  CHECK(matrix_test::equals(m, rsl::matrix33::identity()));

  for(card32 row = 0; row < 3; ++row)
  {
    for(card32 col = 0; col < 3; ++col)
    {
      CHECK(m.elem(row, col) == (row == col ? 1.0f : 0.0f));
      CHECK(rsl::matrix33::zero().elem(row, col) == 0.0f);
    }
  }

  m.elem(1, 2) = 5.0f;
  CHECK(m.elem(1, 2) == 5.0f);
  CHECK(m.elem(2, 1) == 0.0f);
}

TEST_CASE("matrix33 multiplication")
{
  const rsl::matrix33 m        = matrix_test::create_matrix33();
  const rsl::matrix33 identity = rsl::matrix33::identity();

  CHECK(matrix_test::equals(m * identity, m));
  CHECK(matrix_test::equals(identity * m, m));
  CHECK(matrix_test::equals(m * rsl::matrix33::zero(), rsl::matrix33::zero()));

  // compare against a manual multiplication
  const rsl::matrix33 product = m * m;
  for(card32 row = 0; row < 3; ++row)
  {
    for(card32 col = 0; col < 3; ++col)
    {
      float32 expected = 0.0f;
      for(card32 k = 0; k < 3; ++k)
      {
        expected += m.elem(row, k) * m.elem(k, col);
      }
      CHECK(rsl::equals(product.elem(row, col), expected, 0.001f));
    }
  }

  rsl::matrix33 copy = m;
  copy *= m;
  CHECK(matrix_test::equals(copy, product));

  // multiplying a vector
  const rsl::vec3 v(1.0f, 2.0f, 3.0f);
  CHECK(identity * v == v);
  const rsl::vec3 res = m * v;
  for(card32 row = 0; row < 3; ++row)
  {
    const float32 expected = m.elem(row, 0) * v.x + m.elem(row, 1) * v.y + m.elem(row, 2) * v.z;
    CHECK(rsl::equals(res[row], expected, 0.001f));
  }
}

TEST_CASE("matrix33 transpose")
{
  const rsl::matrix33 m = matrix_test::create_matrix33();
  const rsl::matrix33 t = m.transposed();

  for(card32 row = 0; row < 3; ++row)
  {
    for(card32 col = 0; col < 3; ++col)
    {
      CHECK(t.elem(row, col) == m.elem(col, row));
    }
  }

  rsl::matrix33 copy = m;
  copy.transpose().transpose();
  CHECK(matrix_test::equals(copy, m));
}

TEST_CASE("matrix33 inverse")
{
  // a matrix multiplied by its inverse gives the identity matrix (determinant of 25)
  rsl::matrix33 m = rsl::matrix33::zero();
  m.elem(0, 0) = 2.0f;
  m.elem(0, 2) = 1.0f;
  m.elem(1, 0) = 1.0f;
  m.elem(1, 1) = 3.0f;
  m.elem(2, 1) = 1.0f;
  m.elem(2, 2) = 4.0f;
  CHECK(matrix_test::equals(m * m.inversed(), rsl::matrix33::identity()));
  CHECK(matrix_test::equals(m.inversed() * m, rsl::matrix33::identity()));

  // a matrix with a negative determinant (-216)
  const rsl::matrix33 negative_det = matrix_test::create_matrix33();
  CHECK(matrix_test::equals(negative_det * negative_det.inversed(), rsl::matrix33::identity()));

  // the inverse of the identity matrix is the identity matrix
  CHECK(matrix_test::equals(rsl::matrix33::identity().inversed(), rsl::matrix33::identity()));

  // a scale matrix with a negative determinant
  rsl::matrix33 scale;
  scale.set_scale(rsl::vec3(-2.0f, 1.0f, 1.0f));
  rsl::matrix33 expected;
  expected.set_scale(rsl::vec3(-0.5f, 1.0f, 1.0f));
  CHECK(matrix_test::equals(scale.inversed(), expected));
}

TEST_CASE("matrix33 axes and scale")
{
  rsl::matrix33 m;
  CHECK(m.right() == rsl::vec3(1.0f, 0.0f, 0.0f));
  CHECK(m.up() == rsl::vec3(0.0f, 1.0f, 0.0f));
  CHECK(m.at() == rsl::vec3(0.0f, 0.0f, 1.0f));

  m.set_right(rsl::vec3(1.0f, 2.0f, 3.0f));
  m.set_up(rsl::vec3(4.0f, 5.0f, 6.0f));
  m.set_at(rsl::vec3(7.0f, 8.0f, 9.0f));
  CHECK(m.right() == rsl::vec3(1.0f, 2.0f, 3.0f));
  CHECK(m.up() == rsl::vec3(4.0f, 5.0f, 6.0f));
  CHECK(m.at() == rsl::vec3(7.0f, 8.0f, 9.0f));

  rsl::matrix33 scale;
  scale.set_scale(rsl::vec3(2.0f, 3.0f, 4.0f));
  CHECK(scale * rsl::vec3(1.0f, 1.0f, 1.0f) == rsl::vec3(2.0f, 3.0f, 4.0f));
}

TEST_CASE("matrix33 rotation")
{
  constexpr float32 pi = rsl::pi_v<float32>;

  // rotating around an axis leaves that axis untouched and preserves lengths
  rsl::matrix33 rot_z;
  rot_z.set_rotate_z(rsl::rad_angle(pi / 2));
  CHECK(rot_z * rsl::vec3::forward() == rsl::vec3::forward());
  const rsl::vec3 rotated = rot_z * rsl::vec3::right();
  CHECK(rsl::equals(rotated.length(), 1.0f));
  CHECK(rsl::equals(rotated.dot(rsl::vec3::right()), 0.0f));

  rsl::matrix33 rot_x;
  rot_x.set_rotate_x(rsl::rad_angle(pi / 3));
  CHECK(rot_x * rsl::vec3::right() == rsl::vec3::right());

  rsl::matrix33 rot_y;
  rot_y.set_rotate_y(rsl::rad_angle(pi / 3));
  CHECK(rot_y * rsl::vec3::up() == rsl::vec3::up());

  // a rotation matrix multiplied with its transpose gives the identity matrix
  CHECK(matrix_test::equals(rot_z * rot_z.transposed(), rsl::matrix33::identity()));
  CHECK(matrix_test::equals(rot_x * rot_x.transposed(), rsl::matrix33::identity()));
  CHECK(matrix_test::equals(rot_y * rot_y.transposed(), rsl::matrix33::identity()));
}

TEST_CASE("matrix44 construction")
{
  rsl::matrix44 m;
  CHECK(matrix_test::equals(m, rsl::matrix44::identity()));

  for(card32 row = 0; row < 4; ++row)
  {
    for(card32 col = 0; col < 4; ++col)
    {
      CHECK(m.elem(row, col) == (row == col ? 1.0f : 0.0f));
      CHECK(rsl::matrix44::zero().elem(row, col) == 0.0f);
    }
  }
}

TEST_CASE("matrix44 multiplication")
{
  const rsl::matrix44 m        = matrix_test::create_matrix44();
  const rsl::matrix44 identity = rsl::matrix44::identity();

  CHECK(matrix_test::equals(m * identity, m));
  CHECK(matrix_test::equals(identity * m, m));

  const rsl::matrix44 product = m * m;
  for(card32 row = 0; row < 4; ++row)
  {
    for(card32 col = 0; col < 4; ++col)
    {
      float32 expected = 0.0f;
      for(card32 k = 0; k < 4; ++k)
      {
        expected += m.elem(row, k) * m.elem(k, col);
      }
      CHECK(rsl::equals(product.elem(row, col), expected, 0.01f));
    }
  }

  rsl::matrix44 copy = m;
  copy *= m;
  CHECK(matrix_test::equals(copy, product));
}

TEST_CASE("matrix44 transpose and inverse")
{
  const rsl::matrix44 m = matrix_test::create_matrix44();
  const rsl::matrix44 t = m.transposed();
  for(card32 row = 0; row < 4; ++row)
  {
    for(card32 col = 0; col < 4; ++col)
    {
      CHECK(t.elem(row, col) == m.elem(col, row));
    }
  }

  CHECK(matrix_test::equals(m * m.inversed(), rsl::matrix44::identity()));
  CHECK(matrix_test::equals(rsl::matrix44::identity().inversed(), rsl::matrix44::identity()));
}

TEST_CASE("matrix44 translation and scale")
{
  rsl::matrix44 m;
  m.set_translation(rsl::vec3(1.0f, 2.0f, 3.0f));
  CHECK(m.translation() == rsl::vec3(1.0f, 2.0f, 3.0f));

  // translating a point
  CHECK(m * rsl::vec3(1.0f, 1.0f, 1.0f) == rsl::vec3(2.0f, 3.0f, 4.0f));

  // the inverse of a translation translates in the opposite direction
  CHECK(m.inversed().translation() == rsl::vec3(-1.0f, -2.0f, -3.0f));

  rsl::matrix44 scale;
  scale.set_scale(rsl::vec3(2.0f, 3.0f, 4.0f));
  CHECK(scale * rsl::vec3(1.0f, 1.0f, 1.0f) == rsl::vec3(2.0f, 3.0f, 4.0f));

  CHECK(rsl::matrix44::identity().right() == rsl::vec3::right());
  CHECK(rsl::matrix44::identity().up() == rsl::vec3::up());
  CHECK(rsl::matrix44::identity().at() == rsl::vec3::forward());
}

TEST_CASE("matrix44 rotation")
{
  constexpr float32 pi = rsl::pi_v<float32>;

  rsl::matrix44 rot_z;
  rot_z.set_rotate_z(rsl::rad_angle(pi / 2));
  CHECK(rot_z * rsl::vec3::forward() == rsl::vec3::forward());
  CHECK(matrix_test::equals(rot_z * rot_z.transposed(), rsl::matrix44::identity()));

  rsl::matrix44 rot_x;
  rot_x.set_rotate_x(rsl::rad_angle(pi / 3));
  CHECK(rot_x * rsl::vec3::right() == rsl::vec3::right());

  rsl::matrix44 rot_y;
  rot_y.set_rotate_y(rsl::rad_angle(pi / 3));
  CHECK(rot_y * rsl::vec3::up() == rsl::vec3::up());
}

// NOLINTEND
