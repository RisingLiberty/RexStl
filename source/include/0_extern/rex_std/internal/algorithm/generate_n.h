// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: generate_n.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename Size, typename Generator>
    void generate_n(InputIterator first, InputIterator last, Size n, Generator g)
    {
        auto it = first;
        for (Size i = 0; i < n; ++i, ++it)
        {
            *it = g();
        }
    }

REX_RSL_END_NAMESPACE
