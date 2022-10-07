// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_time_functions.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/time/win/win_time_functions.h"

#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/time.h"
#include "rex_std_extra/time/timepoint.h"

FILETIME rsl::win::system_time()
{
  FILETIME file_time;
  GetSystemTimePreciseAsFileTime(&file_time);
  return file_time;
}
FILETIME rsl::win::to_local_time(const FILETIME& time)
{
  FILETIME local_file_time;
  FileTimeToLocalFileTime(&time, &local_file_time);
  return local_file_time;
}
SYSTEMTIME rsl::win::to_local_sys_time(const FILETIME& time)
{
  FILETIME local_file_time = to_local_time(time);
  SYSTEMTIME sys_time;
  FileTimeToSystemTime(&local_file_time, &sys_time);

  return sys_time;
}

SYSTEMTIME rsl::win::local_time()
{
  FILETIME file_time       = system_time();
  FILETIME local_file_time = to_local_time(file_time);
  SYSTEMTIME sys_time;
  FileTimeToSystemTime(&local_file_time, &sys_time);

  return sys_time;
}

card64 rsl::win::to_integer(const FILETIME& time)
{
  ULARGE_INTEGER value;

  value.LowPart  = time.dwLowDateTime;
  value.HighPart = time.dwHighDateTime;

  return value.QuadPart;
}

rsl::Date rsl::win::date(const SYSTEMTIME& date)
{
  return Date(date.wDayOfWeek, date.wDay, date.wMonth, date.wYear);
}
rsl::Time rsl::win::time(const SYSTEMTIME& time)
{
  return Time(time.wHour, time.wMinute, time.wSecond);
}
rsl::TimePoint rsl::win::timepoint(const SYSTEMTIME& timepoint)
{
  return TimePoint(date(timepoint), time(timepoint));
}