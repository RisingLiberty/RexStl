// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: point.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/ostream.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    struct point
    {
    public:
      constexpr point()
        : x(T())
        , y(T())
      {}
      constexpr point(T x, T y)
        : x(x)
        , y(y)
      {}

      constexpr point operator+(const point& rhs) const
      {
        return rsl::point<T>(x + rhs.x, y + rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }
      constexpr point operator-(const point& rhs) const
      {
        return rsl::point<T>(x - rhs.x, y - rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }
      constexpr point operator*(const point& rhs) const
      {
        return rsl::point<T>(x * rhs.x, y * rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }
      constexpr point operator/(const point& rhs) const
      {
        return rsl::point<T>(x / rhs.x, y / rhs.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }

      constexpr point& operator+=(const point& rhs)
      {
        x += rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y += rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }
      constexpr point& operator-=(const point& rhs)
      {
        x -= rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y -= rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }
      constexpr point& operator*=(const point& rhs)
      {
        x *= rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y *= rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }
      constexpr point& operator/=(const point& rhs)
      {
        x /= rhs.x; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y /= rhs.y; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }

      constexpr point operator+(int16 rhs) const
      {
        return rsl::point<T>(x + rhs, y + rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }
      constexpr point operator-(int16 rhs) const
      {
        return rsl::point<T>(x - rhs, y - rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }
      constexpr point operator*(int16 rhs) const
      {
        return rsl::point<T>(x * rhs, y * rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }
      constexpr point operator/(int16 rhs) const
      {
        return rsl::point<T>(x / rhs, y / rhs); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }

      constexpr point& operator+=(int16 rhs)
      {
        x += rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y += rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }
      constexpr point& operator-=(int16 rhs)
      {
        x -= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y -= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }
      constexpr point& operator*=(int16 rhs)
      {
        x *= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y *= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }
      constexpr point& operator/=(int16 rhs)
      {
        x /= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        y /= rhs; // NOLINT(cppcoreguidelines-narrowing-conversions)
        return *this;
      }

      constexpr bool operator==(const point& point) const
      {
        return x == point.x && y == point.y;
      }
      constexpr bool operator!=(const point& point) const
      {
        return !(*this == point);
      }

      constexpr point operator-() const
      {
        return rsl::point(-x, -y); // NOLINT(cppcoreguidelines-narrowing-conversions)
      }

    public:
      T x;
      T y;
    };

    template <typename T>
    ostream& operator<<(ostream& os, const point<T>& point)
    {
      return os << "(x: " << point.x << ", y: " << point.y << ")";
    }

    using pointu8 = point<int8>;
    using pointu16 = point<int16>;
    using pointu32 = point<int32>;
    using pointu64 = point<int64>;

    using pointi8  = point<int8>;
    using pointi16 = point<int16>;
    using pointi32 = point<int32>;
    using pointi64 = point<int64>;

  } // namespace v1
} // namespace rsl