// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_bounded_array.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_bounded_array : public false_type
    {};

    template <typename T, size_t N>
    struct is_bounded_array<T[N]> : public true_type
    {};

    template <typename T>
    constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsBoundedArrayStruct = is_bounded_array<T>;

    template <typename T>
    constexpr bool IsBoundedArray = IsBoundedArrayStruct<T>::value;
#endif
}