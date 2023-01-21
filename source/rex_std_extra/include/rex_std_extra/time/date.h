// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: date.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/types.h"
#include "rex_std/iostream.h"

namespace rsl { inline namespace v1 {

class Date
{
public:
  Date();
  Date(card32 week_day, card32 month_data, card32 month, card32 year);

  tiny_stack_string week_day() const;
  card32 month_day() const;
  card32 month() const;
  tiny_stack_string month_name() const;
  card32 year() const;

  small_stack_string to_string() const;
  small_stack_string to_string_without_weekday() const;

  bool operator>(const Date& date) const;
  bool operator>=(const Date& date) const;
  bool operator<(const Date& date) const;
  bool operator<=(const Date& date) const;

  bool operator==(const Date& date) const;
  bool operator!=(const Date& date) const;

private:
  card32 m_week_day;
  card32 m_month_day;
  card32 m_month;
  card32 m_year;
};

ostream& operator<<(ostream& os, const Date& date);

}}

#ifdef REX_PLATFORM_WINDOWS
  #include "rex_std_extra/time/win/win_date.h"
#endif