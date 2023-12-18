// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timepoint.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/time/timepoint.h"

#include "rex_std/bonus/time/date.h"
#include "rex_std/bonus/time/time.h"

rsl::time_point::time_point() = default;
rsl::time_point::time_point(const rsl::date& date, const rsl::time& time)
    : m_time(time)
    , m_date(date)
{
}

const rsl::date& rsl::time_point::date() const
{
  return m_date;
}
const rsl::time& rsl::time_point::time() const
{
  return m_time;
}

bool rsl::time_point::operator>(const time_point& timepoint) const
{
  return m_date > timepoint.date() && m_time > timepoint.time();
}
bool rsl::time_point::operator>=(const time_point& timepoint) const
{
  return m_date >= timepoint.date() && m_time >= timepoint.time();
}
bool rsl::time_point::operator<(const time_point& timepoint) const
{
  return m_date < timepoint.date() && m_time < timepoint.time();
}
bool rsl::time_point::operator<=(const time_point& timepoint) const
{
  return m_date <= timepoint.date() && m_time <= timepoint.time();
}

bool rsl::time_point::operator==(const time_point& timepoint) const
{
  return m_date == timepoint.date() && m_time == timepoint.time();
}
bool rsl::time_point::operator!=(const time_point& timepoint) const
{
  return !(*this == timepoint);
}

float32 rsl::time_point::operator-(const time_point& /*other*/) const
{
  return 0.0f;
}

rsl::ostream& rsl::operator<<(ostream& os, const time_point& timepoint)
{
  os << timepoint.date() << ' ' << timepoint.time();
  return os;
}
