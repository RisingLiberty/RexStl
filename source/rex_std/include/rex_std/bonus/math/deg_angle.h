// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: deg_angle.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/numbers.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {

    class deg_angle
    {
    public:
      constexpr deg_angle()
        : deg_angle(0)
      {}
      constexpr explicit deg_angle(float32 angle)
          : m_angle(angle)
      {
      }

      constexpr deg_angle operator+(const deg_angle angle) const
      {
        return deg_angle(m_angle + angle.m_angle);
      }
      constexpr deg_angle& operator+=(const deg_angle angle)
      {
        m_angle += angle.m_angle;
        return *this;
      }

      constexpr deg_angle operator-(const deg_angle angle) const
      {
        return deg_angle(m_angle - angle.m_angle);
      }
      constexpr deg_angle& operator-=(const deg_angle angle)
      {
        m_angle -= angle.m_angle;
        return *this;
      }

      constexpr deg_angle operator*(const deg_angle angle) const
      {
        return deg_angle(m_angle * angle.m_angle);
      }
      constexpr deg_angle& operator*=(const deg_angle angle)
      {
        m_angle *= angle.m_angle;
        return *this;
      }

      constexpr deg_angle operator/(const deg_angle angle) const
      {
        return deg_angle(m_angle / angle.m_angle);
      }
      constexpr deg_angle& operator/=(const deg_angle angle)
      {
        m_angle /= angle.m_angle;
        return *this;
      }

      constexpr float32 get() const
      {
        return m_angle;
      }
      constexpr void set(float32 angle)
      {
        m_angle = angle;
      }
      constexpr float32 to_rad() const
      {
        return m_angle * (pi / 180.0f);
      }

      constexpr bool operator<(const deg_angle angle) const
      {
        return m_angle < angle.m_angle;
      }
      constexpr bool operator<=(const deg_angle angle) const
      {
        return m_angle <= angle.m_angle;
      }
      constexpr bool operator>(const deg_angle angle) const
      {
        return m_angle > angle.m_angle;
      }
      constexpr bool operator>=(const deg_angle angle) const
      {
        return m_angle >= angle.m_angle;
      }

      constexpr bool operator==(const deg_angle angle) const
      {
        return m_angle == angle.m_angle;
      }
      constexpr bool operator!=(const deg_angle angle) const
      {
        return m_angle != angle.m_angle;
      }

    private:
      float32 m_angle;
    };

  } // namespace v1
} // namespace rsl

constexpr rsl::deg_angle operator""_deg(unsigned long long value)
{
  return rsl::deg_angle(static_cast<float32>(value));
}