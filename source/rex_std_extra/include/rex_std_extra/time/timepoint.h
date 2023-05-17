// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timepoint.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/ostream.h"
#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/time.h"

namespace rsl
{
  inline namespace v1
  {
    class time_point
    {
    public:
      time_point();
      time_point(const rsl::date& date, const rsl::time& time);

      const rsl::date& date() const;
      const rsl::time& time() const;

      bool operator>(const time_point& timepoint) const;
      bool operator>=(const time_point& timepoint) const;
      bool operator<(const time_point& timepoint) const;
      bool operator<=(const time_point& timepoint) const;

      bool operator==(const time_point& timepoint) const;
      bool operator!=(const time_point& timepoint) const;

      float32 operator-(const time_point& other) const;

    private:
      rsl::time m_time;
      rsl::date m_date;
    };

    ostream& operator<<(ostream& os, const time_point& timepoint);

  } // namespace v1
} // namespace rsl
