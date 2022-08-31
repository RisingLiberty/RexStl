// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: conditional.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <bool Test, typename T1, typename T2>
    struct conditional
    {
        using type = T1;
    };

    template <typename T1, typename T2>
    struct conditional<false, T1, T2>
    {
        using type = T2;
    };

    template <bool Test, typename T1, typename T2>
    using conditional_t = typename conditional<Test, T1, T2>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <bool Test, typename T1, typename T2>
    using ConditionalStruct = conditional<Test, T1, T2>;

    template <bool Test, typename T1, typename T2>
    using Conditional = typename ConditionalStruct<Test, T1, T2>::type;
#endif
}
