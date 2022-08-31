// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_const.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct add_const
    {
        using type = const T;
    };

    template <typename T>
    using add_const_t = typename add_const<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using AddConstStruct = add_const<T>;
    
    template <typename T>
    using AddConst = typename AddConstStruct<T>::type;
#endif
}
