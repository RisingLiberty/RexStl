// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_if.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/find_if.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename Predicate>
    InputIterator remove_if(InputIterator first, InputIterator last, Predicate predicate)
    {
        first = rsl::find_if(first, last, predicate);
        if (first != last)
        {
            for (InputIterator it = first; ++it != last; )
            {
                if (!predicate(*it))
                {
                    *first++ = rsl::move(*it);
                }
            }
        }
        return first;
    }

REX_RSL_END_NAMESPACE
