// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_date.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/time/win/win_date.h"

#include "rex_std/bonus/time/date.h"
#include "rex_std/bonus/time/win/win_time_functions.h"

#include <Windows.h>

rsl::date rsl::current_date()
{
  const SYSTEMTIME sys_time = win::local_time();
  return rsl::date(sys_time.wDayOfWeek, sys_time.wDay, sys_time.wMonth, sys_time.wYear);
}