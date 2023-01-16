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

REX_RSL_BEGIN_NAMESPACE

struct Point
{
public:
  Point();
  Point(int16 x, int16 y);

  Point operator+(const Point& rhs) const;
  Point operator-(const Point& rhs) const;
  Point operator*(const Point& rhs) const;
  Point operator/(const Point& rhs) const;

  Point& operator+=(const Point& rhs);
  Point& operator-=(const Point& rhs);
  Point& operator*=(const Point& rhs);
  Point& operator/=(const Point& rhs);

  Point operator+(const int16 rhs) const;
  Point operator-(const int16 rhs) const;
  Point operator*(const int16 rhs) const;
  Point operator/(const int16 rhs) const;

  Point& operator+=(const int16 rhs);
  Point& operator-=(const int16 rhs);
  Point& operator*=(const int16 rhs);
  Point& operator/=(const int16 rhs);

  bool operator==(const Point& point) const;
  bool operator!=(const Point& point) const;

  Point operator-() const;

public:
  int16 x;
  int16 y;
};

OStream& operator<<(OStream& os, const Point& point);

REX_RSL_END_NAMESPACE