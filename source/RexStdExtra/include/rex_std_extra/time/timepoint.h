// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timepoint.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/time.h"

REX_RSL_BEGIN_NAMESPACE

class Date;
class Time;

class TimePoint
{
public:
  TimePoint();
  TimePoint(const Date& date, const Time& time);

  const Date& date() const;
  const Time& time() const;

  bool operator>(const TimePoint& timepoint) const;
  bool operator>=(const TimePoint& timepoint) const;
  bool operator<(const TimePoint& timepoint) const;
  bool operator<=(const TimePoint& timepoint) const;

  bool operator==(const TimePoint& timepoint) const;
  bool operator!=(const TimePoint& timepoint) const;

  float32 operator-(const TimePoint& other) const;

private:
  Time m_time;
  Date m_date;
};

class OStream;
OStream& operator<<(OStream& os, const TimePoint& timepoint);

REX_RSL_END_NAMESPACE

#ifdef REX_PLATFORM_WINDOWS
  #include "rex_std_extra/time/win/win_timepoint.h"
#endif