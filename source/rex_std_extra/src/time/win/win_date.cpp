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

#include "rex_std_extra/time/win/win_date.h"

#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/win/win_time_functions.h"

rsl::Date rsl::current_date()
{
  SYSTEMTIME sys_time = win::local_time();
  return rsl::Date(sys_time.wDayOfWeek, sys_time.wDay, sys_time.wMonth, sys_time.wYear);
}