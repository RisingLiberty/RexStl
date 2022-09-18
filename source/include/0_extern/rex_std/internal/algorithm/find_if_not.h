// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: find_if_not.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename Predicate>
    InputIterator find_if_not(InputIterator first, InputIterator last, Predicate pred)
    {
        auto it = first;
        while (it != last)
        {
            if (pred(*it) == false)
            {
                return it;
            }
            ++it;
        }

        return it;
    }

REX_RSL_END_NAMESPACE
