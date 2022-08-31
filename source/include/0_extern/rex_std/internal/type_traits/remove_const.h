// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_const.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct remove_const
    {
        using type = T;
    };

    template <typename T>
    struct remove_const<const T>
    {
        using type = T;
    };

    template <typename T>
    using remove_const_t = typename remove_const<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using RemoveConstStruct = remove_const<T>;

    template <typename T>
    using RemoveConst = typename remove_const<T>::type;
#endif
}
