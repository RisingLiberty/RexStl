// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_time.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/time/win/win_time.h"

#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/time/time.h"
#include "rex_std_extra/time/win/win_time_functions.h"

rsl::Time rsl::current_time()
{
  SYSTEMTIME sys_time = win::local_time();
  return Time(sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
}