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

#include "rex_std/ostream.h"

namespace rsl
{
  inline namespace v1
  {

    struct point
    {
    public:
      point();
      point(int16 x, int16 y);

      point operator+(const point& rhs) const;
      point operator-(const point& rhs) const;
      point operator*(const point& rhs) const;
      point operator/(const point& rhs) const;

      point& operator+=(const point& rhs);
      point& operator-=(const point& rhs);
      point& operator*=(const point& rhs);
      point& operator/=(const point& rhs);

      point operator+(int16 rhs) const;
      point operator-(int16 rhs) const;
      point operator*(int16 rhs) const;
      point operator/(int16 rhs) const;

      point& operator+=(int16 rhs);
      point& operator-=(int16 rhs);
      point& operator*=(int16 rhs);
      point& operator/=(int16 rhs);

      bool operator==(const point& point) const;
      bool operator!=(const point& point) const;

      point operator-() const;

    public:
      int16 x;
      int16 y;
    };

    ostream& operator<<(ostream& os, const point& point);

  } // namespace v1
} // namespace rsl