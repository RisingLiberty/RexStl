// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_unbounded_array.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct IsUnboundedArrayStruct : public false_type
    {};

    template <typename T>
    struct IsUnboundedArrayStruct<T[]> : public true_type
    {};

    template <typename T>
    constexpr bool IsUnboundedArray = IsUnboundedArrayStruct<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using is_unbounded_array = IsUnboundedArray<T>;

    template <typename T>
    constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;
#endif
}