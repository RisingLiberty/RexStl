// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: transform_if.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

template <typename InputIterator, typename OutputIterator, typename Func, typename Predicate>
void transform(InputIterator first, InputIterator last, OutputIterator dst_first, Func func, Predicate predicate)
{
    auto it = first;
    while (it != last)
    {
        if (*it)
        {
            *dst_first = func(*it);
            ++dst_first;
        }
        ++it;
    }
}