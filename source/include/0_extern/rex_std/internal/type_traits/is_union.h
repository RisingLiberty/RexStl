// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_union.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct is_union : public bool_constant<__is_union(T)> {};

    template <typename T>
    constexpr bool is_union_v = is_union<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsUnionStruct = is_union<T>;

    template <typename T>
    constexpr bool IsUnion = is_union<T>::value;
#endif
}