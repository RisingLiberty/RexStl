// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: negate.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T = void>
    struct negate
    {
        constexpr T operator()(const T& arg) const
        {
            return -arg;
        }
    };

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T = void>
    using Negate = negate<T>;
#endif
}