// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_timepoint.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/time/win/win_timepoint.h"

#include "rex_std/bonus/time/timepoint.h"
#include "rex_std/bonus/time/win/win_date.h"
#include "rex_std/bonus/time/win/win_time.h"

#include <Windows.h>

rsl::time_point rsl::current_timepoint()
{
  return rsl::time_point(current_date(), current_time());
}

rsl::time_point rsl::timepoint_from_systime(const _SYSTEMTIME& sysTime)
{
  rsl::time time = rsl::time(sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
  rsl::date date = rsl::date(sysTime.wDayOfWeek, sysTime.wDay, sysTime.wMonth, sysTime.wYear);

  return rsl::time_point(date, time);
}