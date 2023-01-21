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

#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/time.h"

namespace rsl { inline namespace v1 {

class Date;
class time;

class TimePoint
{
public:
  TimePoint();
  TimePoint(const Date& date, const rsl::time& time);

  const Date& date() const;
  const rsl::time& time() const;

  bool operator>(const TimePoint& timepoint) const;
  bool operator>=(const TimePoint& timepoint) const;
  bool operator<(const TimePoint& timepoint) const;
  bool operator<=(const TimePoint& timepoint) const;

  bool operator==(const TimePoint& timepoint) const;
  bool operator!=(const TimePoint& timepoint) const;

  float32 operator-(const TimePoint& other) const;

private:
  rsl::time m_time;
  rsl::Date m_date;
};

ostream& operator<<(ostream& os, const TimePoint& timepoint);

}}

#ifdef REX_PLATFORM_WINDOWS
  #include "rex_std_extra/time/win/win_timepoint.h"
#endif