// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_class.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct is_class : public bool_constant<__is_class(T)> {};

    template <typename T>
    constexpr bool is_class_v = is_class<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsClassStruct = is_class<T>;

    template <typename T>
    constexpr bool IsClass = IsClassStruct<T>::value;
#endif
}