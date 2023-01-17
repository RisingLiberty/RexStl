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

#include "rex_std_extra/time/timepoint.h"

#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/time.h"

rsl::TimePoint::TimePoint() = default;
rsl::TimePoint::TimePoint(const Date& date, const Time& time)
    : m_date(date)
    , m_time(time)
{
}

const rsl::Date& rsl::TimePoint::date() const
{
  return m_date;
}
const rsl::Time& rsl::TimePoint::time() const
{
  return m_time;
}

bool rsl::TimePoint::operator>(const TimePoint& timepoint) const
{
  return m_date > timepoint.date() && m_time > timepoint.time();
}
bool rsl::TimePoint::operator>=(const TimePoint& timepoint) const
{
  return m_date >= timepoint.date() && m_time >= timepoint.time();
}
bool rsl::TimePoint::operator<(const TimePoint& timepoint) const
{
  return m_date < timepoint.date() && m_time < timepoint.time();
}
bool rsl::TimePoint::operator<=(const TimePoint& timepoint) const
{
  return m_date <= timepoint.date() && m_time <= timepoint.time();
}

bool rsl::TimePoint::operator==(const TimePoint& timepoint) const
{
  return m_date == timepoint.date() && m_time == timepoint.time();
}
bool rsl::TimePoint::operator!=(const TimePoint& timepoint) const
{
  return !(*this == timepoint);
}

float32 rsl::TimePoint::operator-(const TimePoint& /*other*/) const
{
  return 0.0f;
}

rsl::OStream& rsl::operator<<(OStream& os, const TimePoint& timepoint)
{
  os << timepoint.date() << ' ' << timepoint.time();
  return os;
}
