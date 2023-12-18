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

#include "rex_std/bonus/math/constants.h"

namespace rsl
{
  inline namespace v1
  {

    class DegAngle
    {
    public:
      constexpr explicit DegAngle(float32 angle)
          : m_angle(angle)
      {
      }

      constexpr DegAngle operator+(const DegAngle angle) const
      {
        return DegAngle(m_angle + angle.m_angle);
      }
      constexpr DegAngle& operator+=(const DegAngle angle)
      {
        m_angle += angle.m_angle;
        return *this;
      }

      constexpr DegAngle operator-(const DegAngle angle) const
      {
        return DegAngle(m_angle - angle.m_angle);
      }
      constexpr DegAngle& operator-=(const DegAngle angle)
      {
        m_angle -= angle.m_angle;
        return *this;
      }

      constexpr DegAngle operator*(const DegAngle angle) const
      {
        return DegAngle(m_angle * angle.m_angle);
      }
      constexpr DegAngle& operator*=(const DegAngle angle)
      {
        m_angle *= angle.m_angle;
        return *this;
      }

      constexpr DegAngle operator/(const DegAngle angle) const
      {
        return DegAngle(m_angle / angle.m_angle);
      }
      constexpr DegAngle& operator/=(const DegAngle angle)
      {
        m_angle /= angle.m_angle;
        return *this;
      }

      constexpr float32 get() const
      {
        return m_angle;
      }
      constexpr float32 to_rad() const
      {
        return m_angle * (Pi / 180.0f);
      }

      constexpr bool operator<(const DegAngle angle) const
      {
        return m_angle < angle.m_angle;
      }
      constexpr bool operator<=(const DegAngle angle) const
      {
        return m_angle <= angle.m_angle;
      }
      constexpr bool operator>(const DegAngle angle) const
      {
        return m_angle > angle.m_angle;
      }
      constexpr bool operator>=(const DegAngle angle) const
      {
        return m_angle >= angle.m_angle;
      }

      constexpr bool operator==(const DegAngle angle) const
      {
        return m_angle == angle.m_angle;
      }
      constexpr bool operator!=(const DegAngle angle) const
      {
        return m_angle != angle.m_angle;
      }

    private:
      float32 m_angle;
    };

  } // namespace v1
} // namespace rsl