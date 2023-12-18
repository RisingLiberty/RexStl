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
#include "rex_std/ostream.h"

namespace rsl
{
  inline namespace v1
  {

    class date
    {
    public:
      date();
      date(card32 weekDay, card32 monthDay, card32 month, card32 year);

      tiny_stack_string week_day() const;
      card32 month_day() const;
      card32 month() const;
      tiny_stack_string month_name() const;
      card32 year() const;

      small_stack_string to_string() const;
      small_stack_string to_string_without_weekday() const;

      bool operator>(const date& date) const;
      bool operator>=(const date& date) const;
      bool operator<(const date& date) const;
      bool operator<=(const date& date) const;

      bool operator==(const date& date) const;
      bool operator!=(const date& date) const;

    private:
      card32 m_week_day;
      card32 m_month_day;
      card32 m_month;
      card32 m_year;
    };

    ostream& operator<<(ostream& os, const date& date);

  } // namespace v1
} // namespace rsl
