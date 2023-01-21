// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: point.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/math/point.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::point::point()
    : x(0)
    , y(0)
{
}
rsl::point::point(int16 _x, int16 _y)
    : x(_x)
    , y(_y)
{
}

rsl::point rsl::point::operator+(const point& rhs) const
{
  return {x + rhs.x, y + rhs.y};
}
rsl::point rsl::point::operator-(const point& rhs) const
{
  return {x - rhs.x, y - rhs.y};
}
rsl::point rsl::point::operator*(const point& rhs) const
{
  return {x * rhs.x, y * rhs.y};
}
rsl::point rsl::point::operator/(const point& rhs) const
{
  return {x / rhs.x, y / rhs.y};
}

rsl::point& rsl::point::operator+=(const point& rhs)
{
  x += rhs.x;
  y += rhs.y;
  return *this;
}
rsl::point& rsl::point::operator-=(const point& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}
rsl::point& rsl::point::operator*=(const point& rhs)
{
  x *= rhs.x;
  y *= rhs.y;
  return *this;
}
rsl::point& rsl::point::operator/=(const point& rhs)
{
  x /= rhs.x;
  y /= rhs.y;
  return *this;
}

rsl::point rsl::point::operator+(const int16 rhs) const
{
  return {x + rhs, y + rhs};
}

rsl::point rsl::point::operator-(const int16 rhs) const
{
  return {x - rhs, y - rhs};
}

rsl::point rsl::point::operator*(const int16 rhs) const
{
  return {x * rhs, y * rhs};
}

rsl::point rsl::point::operator/(const int16 rhs) const
{
  return {x / rhs, y / rhs};
}

rsl::point& rsl::point::operator+=(const int16 rhs)
{
  x += rhs;
  y += rhs;
  return *this;
}
rsl::point& rsl::point::operator-=(const int16 rhs)
{
  x -= rhs;
  y -= rhs;
  return *this;
}
rsl::point& rsl::point::operator*=(const int16 rhs)
{
  x *= rhs;
  y *= rhs;
  return *this;
}
rsl::point& rsl::point::operator/=(const int16 rhs)
{
  x /= rhs;
  y /= rhs;
  return *this;
}

bool rsl::point::operator==(const point& point) const
{
  return x == point.x && y == point.y;
}
bool rsl::point::operator!=(const point& point) const
{
  return !(*this == point);
}

rsl::point rsl::point::operator-() const
{
  return {-x, -y};
}

rsl::ostream& rsl::operator<<(ostream& os, const point& point)
{
  return os << "(x: " << point.x << ", y: " << point.y << ")";
}
