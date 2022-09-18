// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: rotate.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/iter_swap.h"

REX_RSL_BEGIN_NAMESPACE

    template<class InputIterator>
    constexpr InputIterator rotate(InputIterator first, InputIterator n_first, InputIterator last)
    {
        if (first == n_first) 
            return last;
        if (n_first == last) 
            return first;

        InputIterator read = n_first;
        InputIterator write = first;
        InputIterator next_read = first; // read position for when "read" hits "last"

        while (read != last) 
        {
            if (write == next_read) 
                next_read = read; // track where "first" went

            iter_swap(write++, read++);
        }

        // rotate the remaining sequence into place
        (rotate)(write, next_read, last);
        return write;
    }

REX_RSL_END_NAMESPACE
