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

    template <typename T>
    class high_water_mark
    {
    public:
      explicit high_water_mark(T initValue)
        : m_value(initValue)
        , m_max_value(initValue)
      {
      }
      high_water_mark(T initValue, T maxValue)
        : m_value(initValue)
        , m_max_value(maxValue)
      {
      }

      high_water_mark& operator++()
      {
        ++m_value;
        m_max_value = rsl::max(m_max_value, m_value);
        return *this;
      }
      high_water_mark operator++(int)
      {
        const card32 tmp = m_value;
        ++m_value;
        m_max_value = rsl::max(m_max_value, m_value);
        return rsl::high_water_mark(tmp, m_max_value);
      }

      high_water_mark& operator--()
      {
        --m_value;
        return *this;
      }
      high_water_mark operator--(int)
      {
        const card32 tmp = m_value;
        --m_value;
        return rsl::high_water_mark(tmp, m_max_value);
      }

      template <typename U>
      high_water_mark operator+(U val) const
      {
        return high_water_mark(m_value + val);
      }
      template <typename U>
      high_water_mark& operator+=(U val)
      {
        m_value += val;
        m_max_value = max(m_max_value, m_value);
        return *this;
      }

      template <typename U>
      high_water_mark operator-(U val) const
      {
        return high_water_mark(m_value - val);
      }
      template <typename U>
      high_water_mark& operator-=(U val)
      {
        // there's no guarantee that val is positive
        // so the subtraction could actually INCREASE the value
        // which is wh we have to use max here
        m_value -= val;
        m_max_value = max(m_max_value, m_value);
        return *this;
      }

      template <typename U>
      high_water_mark operator*(U val) const
      {
        return high_water_mark(m_value * val);
      }
      template <typename U>
      high_water_mark& operator*=(U val)
      {
        m_value *= val;
        m_max_value = max(m_max_value, m_value);
        return *this;
      }


      template <typename U>
      high_water_mark operator/(U val) const
      {
        return high_water_mark(m_value / val);
      }
      template <typename U>
      high_water_mark& operator/=(U val)
      {
        m_value /= val;
        return *this;
      }

      template <typename U>
      high_water_mark operator%(U val) const
      {
        return high_water_mark(m_value % val);
      }
      template <typename U>
      high_water_mark& operator%=(U val)
      {
        m_value %= val;
        return *this;
      }

      operator T() const // NOLINT(google-explicit-constructor
      {
        return value();
      }
      T value() const
      {
        return m_value;
      }
      T max_value() const
      {
        return m_max_value;
      }

    private:
      T m_value;
      T m_max_value;
    };

  } // namespace v1
} // namespace rsl