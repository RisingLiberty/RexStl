// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_copy_if.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template<class InputIterator, class OutputIterator, class Predicate>
    OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator d_first, Predicate p)
    {
        for (; first != last; ++first) 
        {
            if (!p(*first)) 
            {
                *d_first++ = *first;
            }
        }
        return d_first;
    }
}
