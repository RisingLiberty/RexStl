// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: date.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/time/date.h"

#include "rex_std/format.h"
#include "rex_std_extra/time/time_digits.h"

rsl::date::date()
    : m_week_day(0)
    , m_month_day(1)
    , m_month(1)
    , m_year(1970)
{
}
rsl::date::date(card32 weekDay, card32 monthDay, card32 month, card32 year)
    : m_week_day(weekDay)
    , m_month_day(monthDay)
    , m_month(month)
    , m_year(year)
{
}

rsl::tiny_stack_string rsl::date::week_day() const
{
  switch(m_week_day)
  {
    case 0: return "Sunday"_tiny;
    case 1: return "Monday"_tiny;
    case 2: return "Tuesday"_tiny;
    case 3: return "Wednesday"_tiny;
    case 4: return "Thursday"_tiny;
    case 5: return "Friday"_tiny;
    case 6: return "Saturday"_tiny;
  }

  RSL_ASSERT("Invalid day");
  return ""_tiny;
}

card32 rsl::date::month_day() const
{
  return m_month_day;
}
card32 rsl::date::month() const
{
  return m_month;
}

rsl::tiny_stack_string rsl::date::month_name() const
{
  switch(m_month)
  {
    case 1: return "January"_tiny;
    case 2: return "February"_tiny;
    case 3: return "March"_tiny;
    case 4: return "April"_tiny;
    case 5: return "May"_tiny;
    case 6: return "June"_tiny;
    case 7: return "July"_tiny;
    case 8: return "August"_tiny;
    case 9: return "September"_tiny;
    case 10: return "October"_tiny;
    case 11: return "November"_tiny;
    case 12: return "December"_tiny;
  }

  RSL_ASSERT("Invalid month");
  return ""_tiny;
}
card32 rsl::date::year() const
{
  return m_year;
}

rsl::small_stack_string rsl::date::to_string() const
{
  return rsl::small_stack_string(rsl::format("{} {}", week_day(), to_string_without_weekday()));
}
rsl::small_stack_string rsl::date::to_string_without_weekday() const
{
  return rsl::small_stack_string(rsl::format("{}/{}/{}", time_digits(month_day()), time_digits(month()), year()));
}

bool rsl::date::operator>(const date& date) const
{
  if(m_year > date.year())
    return true;

  if(m_month > date.month())
    return true;

  if(m_month_day > date.month_day())
    return true;

  return false;
}
bool rsl::date::operator>=(const date& date) const
{
  if(operator>(date))
    return true;

  return *this == date;
}
bool rsl::date::operator<(const date& date) const
{
  if(m_year < date.year())
    return true;

  if(m_month < date.month())
    return true;

  if(m_month_day < date.month_day())
    return true;

  return false;
}
bool rsl::date::operator<=(const date& date) const
{
  if(operator<(date))
    return true;

  return *this == date;
}

bool rsl::date::operator==(const rsl::date& date) const
{
  return m_month_day == date.month_day() && m_month == date.month() && m_year == date.year();
}
bool rsl::date::operator!=(const rsl::date& date) const
{
  return !(*this == date);
}

rsl::ostream& rsl::operator<<(ostream& os, const date& date)
{
  os << date.to_string();
  return os;
}