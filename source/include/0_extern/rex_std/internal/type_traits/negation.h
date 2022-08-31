// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: negation.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct negation : bool_constant<!bool(T::value)>
    {};

    template <typename T>
    constexpr bool negation_v = negation<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using NegationStruct = negation<T>;

    template <typename T>
    constexpr bool Negation = negation<T>::value;
#endif
}