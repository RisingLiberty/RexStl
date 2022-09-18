// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: transform.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename OutputIterator, typename Func>
    void transform(InputIterator first, InputIterator last, OutputIterator dst_first, Func func)
    {
        auto it = first;
        while (it != last)
        {
            *dst_first = func(*it);
            ++it;
            ++dst_first;
        }
    }

REX_RSL_END_NAMESPACE
