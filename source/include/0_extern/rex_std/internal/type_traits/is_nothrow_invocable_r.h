// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_nothrow_invocable_r.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_invocable_utils.h"

namespace rsl
{
    template <typename Rx, typename Callable, typename ... Args>
    struct is_nothrow_invocable_r : internal::SelectInvokeTraits<Callable, Args...>::template is_nothrow_invocable_r_v<Rx>
    {};

    template <typename Rx, typename Callable, typename ... Args>
    constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<Rx, Callable, Args...>;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsNothrowInvocableRStruct = is_nothrow_invocable_r<T>;

    template <typename T>
    constexpr bool IsNothrowInvocableR = IsNothrowInvocableRStruct<T>::value;
#endif
}