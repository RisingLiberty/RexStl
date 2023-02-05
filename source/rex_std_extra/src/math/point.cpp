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

rsl::point::point()
    : x(0)
    , y(0)
{
}
rsl::point::point(int16 x, int16 y)
    : x(x)
    , y(y)
{
}

rsl::point rsl::point::operator+(const point& rhs) const
{
  return rsl::point(x + rhs.x, y + rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
}
rsl::point rsl::point::operator-(const point& rhs) const
{
  return rsl::point(x - rhs.x, y - rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
}
rsl::point rsl::point::operator*(const point& rhs) const
{
  return rsl::point(x * rhs.x, y * rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
}
rsl::point rsl::point::operator/(const point& rhs) const
{
  return rsl::point(x / rhs.x, y / rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

rsl::point& rsl::point::operator+=(const point& rhs)
{
  x += rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y += rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
  return *this;
}
rsl::point& rsl::point::operator-=(const point& rhs)
{
  x -= rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y -= rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
  return *this;
}
rsl::point& rsl::point::operator*=(const point& rhs)
{
  x *= rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y *= rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
  return *this;
}
rsl::point& rsl::point::operator/=(const point& rhs)
{
  x /= rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y /= rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
  return *this;
}

rsl::point rsl::point::operator+(const int16 rhs) const
{
  return rsl::point(x + rhs, y + rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

rsl::point rsl::point::operator-(const int16 rhs) const
{
  return rsl::point(x - rhs, y - rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

rsl::point rsl::point::operator*(const int16 rhs) const
{
  return rsl::point(x * rhs, y * rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

rsl::point rsl::point::operator/(const int16 rhs) const
{
  return rsl::point(x / rhs, y / rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

rsl::point& rsl::point::operator+=(const int16 rhs)
{
  x += rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y += rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
  return *this;
}
rsl::point& rsl::point::operator-=(const int16 rhs)
{
  x -= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y -= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
  return *this;
}
rsl::point& rsl::point::operator*=(const int16 rhs)
{
  x *= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y *= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
  return *this;
}
rsl::point& rsl::point::operator/=(const int16 rhs)
{
  x /= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
  y /= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
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
  return rsl::point(-x, -y); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

rsl::ostream& rsl::operator<<(ostream& os, const point& point)
{
  return os << "(x: " << point.x << ", y: " << point.y << ")";
}
