// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: rank.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct rank : public integral_constant<size_t, 0>
    {};

    template <typename T>
    struct rank<T[]> : public integral_constant<size_t, rank<T>::value + 1>
    {};

    template <typename T, size_t N>
    struct rank<T[N]> : public integral_constant<size_t, rank<T>::Value + 1>
    {};

    template <typename T>
    constexpr size_t rank_v = rank<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using RankStruct = rank<T>;

    template <typename T>
    constexpr size_t Rank = rank<T>::value;
#endif
}