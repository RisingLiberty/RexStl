// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: rad_angle.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/numbers.h"

namespace rsl
{
  inline namespace v1
  {

    class rad_angle
    {
    public:
      constexpr explicit rad_angle(float32 angle)
          : m_angle(angle)
      {
      }

      constexpr rad_angle operator+(const rad_angle angle) const
      {
        return rad_angle(m_angle + angle.m_angle);
      }
      constexpr rad_angle& operator+=(const rad_angle angle)
      {
        m_angle += angle.m_angle;
        return *this;
      }

      constexpr rad_angle operator-(const rad_angle angle) const
      {
        return rad_angle(m_angle - angle.m_angle);
      }
      constexpr rad_angle& operator-=(const rad_angle angle)
      {
        m_angle -= angle.m_angle;
        return *this;
      }

      constexpr rad_angle operator*(const rad_angle angle) const
      {
        return rad_angle(m_angle * angle.m_angle);
      }
      constexpr rad_angle& operator*=(const rad_angle angle)
      {
        m_angle *= angle.m_angle;
        return *this;
      }

      constexpr rad_angle operator/(const rad_angle angle) const
      {
        return rad_angle(m_angle / angle.m_angle);
      }
      constexpr rad_angle& operator/=(const rad_angle angle)
      {
        m_angle /= angle.m_angle;
        return *this;
      }

      constexpr float32 get() const
      {
        return m_angle;
      }
      constexpr float32 to_deg() const
      {
        return m_angle * (180 / pi);
      }

      constexpr bool operator<(const rad_angle angle) const
      {
        return m_angle < angle.m_angle;
      }
      constexpr bool operator<=(const rad_angle angle) const
      {
        return m_angle <= angle.m_angle;
      }
      constexpr bool operator>(const rad_angle angle) const
      {
        return m_angle > angle.m_angle;
      }
      constexpr bool operator>=(const rad_angle angle) const
      {
        return m_angle >= angle.m_angle;
      }

      constexpr bool operator==(const rad_angle angle) const
      {
        return m_angle == angle.m_angle;
      }
      constexpr bool operator!=(const rad_angle angle) const
      {
        return m_angle != angle.m_angle;
      }

    private:
      float32 m_angle;
    };

  } // namespace v1
} // namespace rsl