// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: count.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    // C++ doesn't define a count with predicate, as it can effectively be synthesized via count_if
    // with an appropriate predicate. However, it's often simpler to just have count with a predicate.
    template <typename InputIterator, typename T, typename Predicate>
    typename InputIterator::difference_type count(InputIterator first, InputIterator last, const T& value, Predicate predicate)
    {
        typename InputIterator::difference_type result = 0;

        for (; first != last; ++first)
        {
            if (predicate(*first, value))
                ++result;
        }
        return result;
    }

REX_RSL_END_NAMESPACE
