// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: lower_bound.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename T>
    InputIterator lower_bound(InputIterator first, InputIterator last, const T& value)
    {
        auto it = first;
        while (it != last)
        {
            if (!(*it < value))
            {
                return it;
            }
            ++it;
        }

        return it;
    }

    template <typename InputIterator, typename T, typename Compare>
    InputIterator lower_bound(InputIterator first, InputIterator last, const T& value, Compare comp)
    {
        auto it = first;
        while (it != last)
        {
            if (comp(*it, value) == false)
            {
                return it;
            }
            ++it;
        }

        return it;
    }

REX_RSL_END_NAMESPACE
