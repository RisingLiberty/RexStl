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

#include "rex_std_extra/time/time_digits.h"

rsl::time::time()
    : m_hours(0)
    , m_minutes(0)
    , m_seconds(0)
{
}
rsl::time::time(card32 hours, card32 minutes, card32 seconds)
    : m_hours(hours)
    , m_minutes(minutes)
    , m_seconds(seconds)
{
}

card32 rsl::time::hours() const
{
  return m_hours;
}
card32 rsl::time::minutes() const
{
  return m_minutes;
}
card32 rsl::time::seconds() const
{
  return m_seconds;
}

bool rsl::time::operator>(const time& time) const
{
  if(m_hours > time.hours())
    return true;

  if(m_minutes > time.minutes())
    return true;

  if(m_seconds > time.seconds())
    return true;

  return false;
}
bool rsl::time::operator>=(const time& time) const
{
  if(operator>(time))
    return true;

  return *this == time;
}
bool rsl::time::operator<(const time& time) const
{
  if(m_hours < time.hours())
    return true;

  if(m_minutes < time.minutes())
    return true;

  if(m_seconds < time.seconds())
    return true;

  return false;
}
bool rsl::time::operator<=(const time& time) const
{
  if(operator<(time))
    return true;

  return *this == time;
}

bool rsl::time::operator==(const time& time) const
{
  return m_hours == time.hours() && m_minutes == time.minutes() && m_seconds == time.seconds();
}
bool rsl::time::operator!=(const time& time) const
{
  return !(*this == time);
}

rsl::ostream& rsl::operator<<(ostream& os, const time& time)
{
  os << rsl::time_digits(time.hours()) << ':' << rsl::time_digits(time.minutes()) << ':' << rsl::time_digits(time.seconds());
  return os;
}