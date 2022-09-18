// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: for_each_n.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename Size, typename Func>
    InputIterator for_each_n(InputIterator first, Size n, Func func)
    {
        auto it = first;
        for (Size i = 0; i < n; ++i, ++it)
        {
            func(*it);
        }
        return it;
    }

REX_RSL_END_NAMESPACE
