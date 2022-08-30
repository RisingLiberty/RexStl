// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: chrono.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/compare.h"

#include "rex_std/internal/chrono/calendar.h"
#include "rex_std/internal/chrono/clock.h"
#include "rex_std/internal/chrono/duration.h"
#include "rex_std/internal/chrono/duration_values.h"
#include "rex_std/internal/chrono/leap_second.h"
#include "rex_std/internal/chrono/time_of_day.h"
#include "rex_std/internal/chrono/time_point.h"
#include "rex_std/internal/chrono/time_zone.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <chrono>

namespace rsl::chrono
{
    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(common_type, T);

#ifdef REX_ENABLE_WITH_CPP20
    template <typename T>
    using formatter = std::formatter<T>;
#endif

    REX_STD_FUNC_ALIAS(operator<<);
#ifdef REX_ENABLE_WITH_CPP23
    REX_STD_FUNC_ALIAS(from_stream);
    REX_STD_FUNC_ALIAS(parse);
#endif // REX_ENABLE_WITH_CPP23

}

namespace rsl::chrono_literals
{
    using namespace std::chrono_literals;
}

#include "rex_std/enable_std_checking.h"
