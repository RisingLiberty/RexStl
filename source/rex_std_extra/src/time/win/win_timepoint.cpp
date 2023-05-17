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
#include "rex_std_extra/time/date.h"
#include "rex_std_extra/time/time.h"

rsl::time_point rsl::current_timepoint()
{
  return rsl::time_point(current_date(), current_time());
}