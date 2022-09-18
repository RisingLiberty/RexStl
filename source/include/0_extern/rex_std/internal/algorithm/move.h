// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: move.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/utility/move.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename OutputIterator>
    OutputIterator move(InputIterator first, InputIterator last, OutputIterator dst_first)
    {
        auto src = first;
        auto dst = dst_first;
        while (first != last)
        {
            *dst = rsl::move(*src);
            ++src;
            ++dst;
        }
    }

REX_RSL_END_NAMESPACE
