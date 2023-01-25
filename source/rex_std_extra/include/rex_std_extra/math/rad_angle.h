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

    class RadAngle
    {
    public:
      constexpr explicit RadAngle(float32 angle)
          : m_angle(angle)
      {
      }

      constexpr RadAngle operator+(const RadAngle angle) const
      {
        return RadAngle(m_angle + angle.m_angle);
      }
      constexpr RadAngle& operator+=(const RadAngle angle)
      {
        m_angle += angle.m_angle;
        return *this;
      }

      constexpr RadAngle operator-(const RadAngle angle) const
      {
        return RadAngle(m_angle - angle.m_angle);
      }
      constexpr RadAngle& operator-=(const RadAngle angle)
      {
        m_angle -= angle.m_angle;
        return *this;
      }

      constexpr RadAngle operator*(const RadAngle angle) const
      {
        return RadAngle(m_angle * angle.m_angle);
      }
      constexpr RadAngle& operator*=(const RadAngle angle)
      {
        m_angle *= angle.m_angle;
        return *this;
      }

      constexpr RadAngle operator/(const RadAngle angle) const
      {
        return RadAngle(m_angle / angle.m_angle);
      }
      constexpr RadAngle& operator/=(const RadAngle angle)
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
        return m_angle * (180 / Pi);
      }

      constexpr bool operator<(const RadAngle angle) const
      {
        return m_angle < angle.m_angle;
      }
      constexpr bool operator<=(const RadAngle angle) const
      {
        return m_angle <= angle.m_angle;
      }
      constexpr bool operator>(const RadAngle angle) const
      {
        return m_angle > angle.m_angle;
      }
      constexpr bool operator>=(const RadAngle angle) const
      {
        return m_angle >= angle.m_angle;
      }

      constexpr bool operator==(const RadAngle angle) const
      {
        return m_angle == angle.m_angle;
      }
      constexpr bool operator!=(const RadAngle angle) const
      {
        return m_angle != angle.m_angle;
      }

    private:
      float32 m_angle;
    };

  } // namespace v1
} // namespace rsl