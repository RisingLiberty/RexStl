// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: calendar.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <chrono>

namespace rsl::chrono
{
    using last_spec = std::chrono::last_spec;
    using day = std::chrono::day;
    using month = std::chrono::month;
    using year = std::chrono::year;
    using weekday = std::chrono::weekday;
    using weekday_index = std::chrono::weekday_indexed;
    using weekday_last = std::chrono::weekday_last;
    using month_day = std::chrono::month_day;
    using month_day_last = std::chrono::month_day_last;
    using month_weekday = std::chrono::month_weekday;
    using month_weekday_last = std::chrono::month_weekday_last;
    using year_month = std::chrono::year_month;
    using year_month_day = std::chrono::year_month_day;
    using year_month_day_last = std::chrono::year_month_day_last;
    using year_month_weekday = std::chrono::year_month_weekday;
    using year_month_weekday_last = std::chrono::year_month_weekday_last;

    using std::chrono::operator==;
    using std::chrono::operator+;
    using std::chrono::operator-;
    using std::chrono::operator/;
}

#include "rex_std/enable_std_checking.h"