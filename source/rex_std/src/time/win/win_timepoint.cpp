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

namespace rsl
{
  inline namespace v1
  {
    time_point current_timepoint()
    {
      return time_point(current_date(), current_time());
    }

    time_point timepoint_from_systime(const _SYSTEMTIME& sysTime)
    {
      const rsl::time time = rsl::time(sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
      const rsl::date date = rsl::date(sysTime.wDayOfWeek, sysTime.wDay, sysTime.wMonth, sysTime.wYear);

      return rsl::time_point(date, time);

    }
  }
}