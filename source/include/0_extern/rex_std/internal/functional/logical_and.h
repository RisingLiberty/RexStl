// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: logical_and.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T = void>
    struct logical_and
    {
        /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Aug/2022)
        // the standard doesn't template the second argument.
        // we do so we can, for example, compare a string with a const char*
        // without the second getting promoted to a string
        template <typename U = T>
        constexpr T operator()(const T& lhs, const U& rhs) const
        {
            return lhs && rhs;
        }
    };

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T = void>
    using LogicalAnd = logical_and<T>;
#endif
}