// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: in_range.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/algorithm/in_range.h"
#include "rex_std/limits.h"

REX_RSL_BEGIN_NAMESPACE

    template<typename R, typename T >
    constexpr bool in_range(T t)
    {
        return rsl::in_range(t, rsl::numeric_limits<R>::min(), rsl::numeric_limits<R>::max());
    }

REX_RSL_END_NAMESPACE
