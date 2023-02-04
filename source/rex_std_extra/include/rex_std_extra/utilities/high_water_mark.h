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

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {

    class high_water_mark
    {
    public:
      explicit high_water_mark(card32 maxValue);
      high_water_mark(card32 initValue, card32 maxValue);

      high_water_mark& operator++();
      high_water_mark operator++(int);

      high_water_mark& operator--();
      high_water_mark operator--(int);

      high_water_mark operator+(int32 val) const;
      high_water_mark& operator+=(int32 val);

      high_water_mark operator-(int32 val) const;
      high_water_mark& operator-=(int32 val);

      high_water_mark operator*(int32 val) const;
      high_water_mark& operator*=(int32 val);

      high_water_mark operator/(int32 val) const;
      high_water_mark& operator/=(int32 val);

      high_water_mark operator%(int32 val) const;
      high_water_mark& operator%=(int32 val);

      operator card32() const; // NOLINT(google-explicit-constructor)
      card32 value() const;
      card32 max_value() const;

    private:
      card32 m_value;
      card32 m_max_value;
    };

  } // namespace v1
} // namespace rsl