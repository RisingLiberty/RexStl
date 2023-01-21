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

rsl::HighWaterMark::HighWaterMark(card32 init_value)
    : m_value(init_value)
    , m_high_water_mark(init_value)
{
}

rsl::HighWaterMark& rsl::HighWaterMark::operator++()
{
  ++m_value;
  m_high_water_mark = rsl::max(m_high_water_mark, m_value);
  return *this;
}
rsl::HighWaterMark rsl::HighWaterMark::operator++(int)
{
  card32 tmp = m_value;
  ++m_value;
  m_high_water_mark = rsl::max(m_high_water_mark, m_value);
  return tmp;
}

rsl::HighWaterMark& rsl::HighWaterMark::operator--()
{
  --m_value;
  return *this;
}
rsl::HighWaterMark rsl::HighWaterMark::operator--(int)
{
  card32 tmp = m_value;
  --m_value;
  return tmp;
}

rsl::HighWaterMark rsl::HighWaterMark::operator+(int32 val) const
{
  return HighWaterMark(m_value + val);
}
rsl::HighWaterMark& rsl::HighWaterMark::operator+=(int32 val)
{
  m_value += val;
  m_high_water_mark = max(m_high_water_mark, m_value);
  return *this;
}

rsl::HighWaterMark rsl::HighWaterMark::operator-(int32 val) const
{
  return HighWaterMark(m_value - val);
}
rsl::HighWaterMark& rsl::HighWaterMark::operator-=(int32 val)
{
  // there's no guarantee that val is positive
  // so the subtraction could actually INCREASE the value
  // which is wh we have to use max here
  m_value -= val;
  m_high_water_mark = max(m_high_water_mark, m_value);
  return *this;
}

rsl::HighWaterMark rsl::HighWaterMark::operator*(int32 val) const
{
  return HighWaterMark(m_value * val);
}
rsl::HighWaterMark& rsl::HighWaterMark::operator*=(int32 val)
{
  m_value *= val;
  m_high_water_mark = max(m_high_water_mark, m_value);
  return *this;
}

rsl::HighWaterMark rsl::HighWaterMark::operator/(int32 val) const
{
  return HighWaterMark(m_value / val);
}
rsl::HighWaterMark& rsl::HighWaterMark::operator/=(int32 val)
{
  m_value /= val;
  return *this;
}

rsl::HighWaterMark rsl::HighWaterMark::operator%(int32 val) const
{
  return HighWaterMark(m_value % val);
}
rsl::HighWaterMark& rsl::HighWaterMark::operator%=(int32 val)
{
  m_value %= val;
  return *this;
}

rsl::HighWaterMark::operator card32() const
{
  return value();
}
card32 rsl::HighWaterMark::value() const
{
  return m_value;
}
card32 rsl::HighWaterMark::high_water_mark() const
{
  return m_high_water_mark;
}
