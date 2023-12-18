// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_timepoint.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================
#pragma once

#include "rex_std_extra/time/timepoint.h"

struct _SYSTEMTIME;

namespace rsl
{
  inline namespace v1
  {
    class time_point; // IWYU pragma: keep

    time_point current_timepoint();
    time_point timepoint_from_systime(const _SYSTEMTIME& sysTime);

  } // namespace v1
} // namespace rsl