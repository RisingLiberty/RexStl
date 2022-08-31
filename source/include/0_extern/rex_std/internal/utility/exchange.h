// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: exchange.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/utility/move.h"
#include "rex_std/internal/utility/forward.h"

namespace rsl
{
    template <typename T, typename Other = T>
    constexpr T exchange(T& val, Other&& new_val)
    {
        T old_val = rsl::move(val);
        val = rsl::forward<Other>(new_val);
        return old_val;
    }
}