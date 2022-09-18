// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_copy.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template<typename InputIterator, typename OutputIterator, typename T>
    OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator d_first, const T& value)
    {
        for (; first != last; ++first) 
        {
            if (!(*first == value)) 
            {
                *d_first++ = *first;
            }
        }
        return d_first;
    }

REX_RSL_END_NAMESPACE
