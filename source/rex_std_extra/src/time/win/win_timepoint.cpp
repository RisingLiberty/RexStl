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

#include "rex_std_extra/time/win/win_timepoint.h"

#include "rex_std_extra/time/timepoint.h"
#include "rex_std_extra/time/win/win_date.h"
#include "rex_std_extra/time/win/win_time.h"

rsl::TimePoint rsl::current_timepoint()
{
  return rsl::TimePoint(current_date(), current_time());
}