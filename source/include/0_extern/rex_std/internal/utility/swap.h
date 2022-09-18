// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: swap.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/utility/move.h"
#include "rex_std/internal/algorithm/swap_ranges.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    constexpr void swap(T& lhs, T& rhs)
    {
        T tmp = rsl::move(lhs);
        lhs = rsl::move(rhs);
        rhs = rsl::move(tmp);
    }

    template <typename T, size_t N>
    constexpr void swap(T (&a)[N], T (&b)[N])
    {
        swap_ranges(a, a + N, b);
    }

REX_RSL_END_NAMESPACE
