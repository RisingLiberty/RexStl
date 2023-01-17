// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: time.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/time/time.h"

#include "rex_std_extra/diagnostics/log_message.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::Time::Time()
    : m_hours(0)
    , m_minutes(0)
    , m_seconds(0)
{
}
rsl::Time::Time(card32 hours, card32 minutes, card32 seconds)
    : m_hours(hours)
    , m_minutes(minutes)
    , m_seconds(seconds)
{
}

card32 rsl::Time::hours() const
{
  return m_hours;
}
card32 rsl::Time::minutes() const
{
  return m_minutes;
}
card32 rsl::Time::seconds() const
{
  return m_seconds;
}

bool rsl::Time::operator>(const Time& time) const
{
  if(m_hours > time.hours())
    return true;

  if(m_minutes > time.minutes())
    return true;

  if(m_seconds > time.seconds())
    return true;

  return false;
}
bool rsl::Time::operator>=(const Time& time) const
{
  if(operator>(time))
    return true;

  return *this == time;
}
bool rsl::Time::operator<(const Time& time) const
{
  if(m_hours < time.hours())
    return true;

  if(m_minutes < time.minutes())
    return true;

  if(m_seconds < time.seconds())
    return true;

  return false;
}
bool rsl::Time::operator<=(const Time& time) const
{
  if(operator<(time))
    return true;

  return *this == time;
}

bool rsl::Time::operator==(const Time& time) const
{
  return m_hours == time.hours() && m_minutes == time.minutes() && m_seconds == time.seconds();
}
bool rsl::Time::operator!=(const Time& time) const
{
  return !(*this == time);
}

rsl::OStream& rsl::operator<<(OStream& os, const Time& time)
{
  os << TimeDigits(time.hours()) << ':' << TimeDigits(time.minutes()) << ':' << TimeDigits(time.seconds());
  return os;
}