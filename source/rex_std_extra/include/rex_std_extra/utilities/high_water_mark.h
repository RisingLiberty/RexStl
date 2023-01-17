// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: high_water_mark.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

class HighWaterMark
{
public:
  HighWaterMark(card32 init_value = 0);

  HighWaterMark& operator++();
  HighWaterMark operator++(int);

  HighWaterMark& operator--();
  HighWaterMark operator--(int);

  HighWaterMark operator+(int32 val) const;
  HighWaterMark& operator+=(int32 val);

  HighWaterMark operator-(int32 val) const;
  HighWaterMark& operator-=(int32 val);

  HighWaterMark operator*(int32 val) const;
  HighWaterMark& operator*=(int32 val);

  HighWaterMark operator/(int32 val) const;
  HighWaterMark& operator/=(int32 val);

  HighWaterMark operator%(int32 val) const;
  HighWaterMark& operator%=(int32 val);

  operator card32() const;
  card32 value() const;
  card32 high_water_mark() const;

private:
  card32 m_value;
  card32 m_high_water_mark;
};

REX_RSL_END_NAMESPACE