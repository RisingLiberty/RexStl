// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_time.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/time/win/win_time.h"

#include "rex_std/bonus/time/time.h"
#include "rex_std/bonus/time/win/win_time_functions.h"

#include <Windows.h>

rsl::time rsl::current_time()
{
  const SYSTEMTIME sys_time = win::local_time();
  return time(sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
}