// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: high_water_mark.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/utilities/high_water_mark.h"

#include "rex_std/algorithm.h"

rsl::high_water_mark::high_water_mark(card32 maxValue)
    : m_value(0)
    , m_max_value(maxValue)
{
}

rsl::high_water_mark::high_water_mark(card32 initValue, card32 maxValue)
    : m_value(initValue)
    , m_max_value(maxValue)
{
}

rsl::high_water_mark& rsl::high_water_mark::operator++()
{
  ++m_value;
  m_max_value = rsl::max(m_max_value, m_value);
  return *this;
}
rsl::high_water_mark rsl::high_water_mark::operator++(int)
{
  const card32 tmp = m_value;
  ++m_value;
  m_max_value = rsl::max(m_max_value, m_value);
  return rsl::high_water_mark(tmp, m_max_value);
}

rsl::high_water_mark& rsl::high_water_mark::operator--()
{
  --m_value;
  return *this;
}
rsl::high_water_mark rsl::high_water_mark::operator--(int)
{
  const card32 tmp = m_value;
  --m_value;
  return rsl::high_water_mark(tmp, m_max_value);
}

rsl::high_water_mark rsl::high_water_mark::operator+(int32 val) const
{
  return high_water_mark(m_value + val);
}
rsl::high_water_mark& rsl::high_water_mark::operator+=(int32 val)
{
  m_value += val;
  m_max_value = max(m_max_value, m_value);
  return *this;
}

rsl::high_water_mark rsl::high_water_mark::operator-(int32 val) const
{
  return high_water_mark(m_value - val);
}
rsl::high_water_mark& rsl::high_water_mark::operator-=(int32 val)
{
  // there's no guarantee that val is positive
  // so the subtraction could actually INCREASE the value
  // which is wh we have to use max here
  m_value -= val;
  m_max_value = max(m_max_value, m_value);
  return *this;
}

rsl::high_water_mark rsl::high_water_mark::operator*(int32 val) const
{
  return high_water_mark(m_value * val);
}
rsl::high_water_mark& rsl::high_water_mark::operator*=(int32 val)
{
  m_value *= val;
  m_max_value = max(m_max_value, m_value);
  return *this;
}

rsl::high_water_mark rsl::high_water_mark::operator/(int32 val) const
{
  return high_water_mark(m_value / val);
}
rsl::high_water_mark& rsl::high_water_mark::operator/=(int32 val)
{
  m_value /= val;
  return *this;
}

rsl::high_water_mark rsl::high_water_mark::operator%(int32 val) const
{
  return high_water_mark(m_value % val);
}
rsl::high_water_mark& rsl::high_water_mark::operator%=(int32 val)
{
  m_value %= val;
  return *this;
}

rsl::high_water_mark::operator card32() const
{
  return value();
}
card32 rsl::high_water_mark::value() const
{
  return m_value;
}
card32 rsl::high_water_mark::max_value() const
{
  return m_max_value;
}
