// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_nothrow_swappable_with.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_void.h"
#include "rex_std/bonus/type_traits/is_swappable_utils.h"

namespace rsl
{
    namespace internal
    {
        template <typename T, typename U, bool OneTypeIsVoid = (is_void_v<T> || is_void_v<U>)>
        struct IsNoThrowSwappableWithHelper
        {
            static const bool value = noexcept(swap(declval<T>(), declval<U>())) && 
                                      noexcept(swap(declval<U>(), declval<T>()));
        };

        template <typename T, typename U>
        struct IsNoThrowSwappableWithHelper<T, U, true> 
        {
            static const bool value = false;
        };
    }

    template <typename T, typename U>
    struct is_nothrow_swappable_with : public bool_constant<internal::IsNoThrowSwappableWithHelper<T, U>::value>
    {};

    template <typename T, typename U>
    constexpr bool is_nothrow_swappable_with = is_nothrow_swappable_with<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T, typename U>
    using IsNothrowSwappableWithStruct = is_nothrow_swappable_with<T, U>;

    template <typename T, typename U>
    constexpr bool IsNothrowSwappableWith = IsNothrowSwappableWith<T, U>::value;
#endif
}