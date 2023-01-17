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

#define NOMINMAX
#include <Windows.h>

REX_RSL_BEGIN_NAMESPACE

class Date;
class Time;
class TimePoint;

namespace win
{
  using FileHandle = void*;

  FILETIME system_time();
  FILETIME to_local_time(const FILETIME& time);
  SYSTEMTIME to_local_sys_time(const FILETIME& time);
  SYSTEMTIME local_time();
  card64 to_integer(const FILETIME& time);

  Date date(const SYSTEMTIME& date);
  Time time(const SYSTEMTIME& time);
  TimePoint timepoint(const SYSTEMTIME& time);
} // namespace win

REX_RSL_END_NAMESPACE