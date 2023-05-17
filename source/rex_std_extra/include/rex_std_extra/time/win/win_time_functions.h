// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_time_functions.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/time.h"
#include "rex_std_extra/time/timepoint.h"

#define NOMINMAX
#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {

    namespace win
    {
      using FileHandle = void*;

      FILETIME system_time();
      FILETIME to_local_time(const FILETIME& time);
      SYSTEMTIME to_local_sys_time(const FILETIME& time);
      SYSTEMTIME local_time();
      card64 to_integer(const FILETIME& time);

      rsl::date date(const SYSTEMTIME& date);
      rsl::time time(const SYSTEMTIME& time);
      rsl::time_point timepoint(const SYSTEMTIME& time);
    } // namespace win

  } // namespace v1
} // namespace rsl