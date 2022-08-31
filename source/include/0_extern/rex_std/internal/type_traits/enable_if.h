// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: enable_if.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <bool Test, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T>
    {
        using type = T;
    };

    template <bool Test, typename T = void>
    using enable_if_t = typename enable_if<Test, T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <bool Test, typename T = void>
    using EnableIfStruct = enable_if<Test, T>;

    template <bool Test, typename T = void>
    using EnableIf = typename EnableIfStruct<Test>::type;
#endif
}
