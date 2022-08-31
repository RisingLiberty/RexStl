// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: alignment_of.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct alignment_of : integral_constant<size_t, alignof(T)>
    {};

    template <typename T>
    constexpr size_t alignment_of_v = alignof(T);

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using AlignmentOfStruct = alignment_of<T>;

    template <typename T>
    constexpr size_t AlignmentOf = AlignmentOfStruct<T>::value;
#endif
}