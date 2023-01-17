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

#include "rex_std_extra/diagnostics/log_message.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::Date::Date()
    : m_week_day(0)
    , m_month_day(1)
    , m_month(1)
    , m_year(1970)
{
}
rsl::Date::Date(card32 week_day, card32 month_day, card32 month, card32 year)
    : m_week_day(week_day)
    , m_month_day(month_day)
    , m_month(month)
    , m_year(year)
{
}

rsl::TinyStackString rsl::Date::week_day() const
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

  REX_ASSERT("Invalid day");
  return ""_tiny;
}

card32 rsl::Date::month_day() const
{
  return m_month_day;
}
card32 rsl::Date::month() const
{
  return m_month;
}

rsl::TinyStackString rsl::Date::month_name() const
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

  REX_ASSERT("Invalid month");
  return ""_tiny;
}
card32 rsl::Date::year() const
{
  return m_year;
}

rsl::SmallStackString rsl::Date::to_string() const
{
  return stack_string_from_message<SmallStackString>(week_day(), ' ', to_string_without_weekday());
}
rsl::SmallStackString rsl::Date::to_string_without_weekday() const
{
  return stack_string_from_message<SmallStackString>(TimeDigits(month_day()), '/', TimeDigits(month()), '/', year());
}

bool rsl::Date::operator>(const Date& date) const
{
  if(m_year > date.year())
    return true;

  if(m_month > date.month())
    return true;

  if(m_month_day > date.month_day())
    return true;

  return false;
}
bool rsl::Date::operator>=(const Date& date) const
{
  if(operator>(date))
    return true;

  return *this == date;
}
bool rsl::Date::operator<(const Date& date) const
{
  if(m_year < date.year())
    return true;

  if(m_month < date.month())
    return true;

  if(m_month_day < date.month_day())
    return true;

  return false;
}
bool rsl::Date::operator<=(const Date& date) const
{
  if(operator<(date))
    return true;

  return *this == date;
}

bool rsl::Date::operator==(const rsl::Date& date) const
{
  return m_month_day == date.month_day() && m_month == date.month() && m_year == date.year();
}
bool rsl::Date::operator!=(const rsl::Date& date) const
{
  return !(*this == date);
}

rsl::OStream& rsl::operator<<(OStream& os, const Date& date)
{
  os << date.to_string();
  return os;
}