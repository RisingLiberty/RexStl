// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_nothrow_invocable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_invocable_utils.h"

namespace rsl
{
    template <typename Callable, typename ... Args>
    struct is_nothrow_invocable : internal::SelectInvokeTraits<Callable, Args...>::is_nothrow_invocable_v
    {};

    template <typename Callable, typename ... Args>
    constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<Callable, Args...>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename Callable, typename ... Args>
    using IsNothrowInvocableStruct = is_nothrow_invocable<Callable, Args...>;

    template <typename Callable, typename ... Args>
    constexpr bool IsNothrowInvocable = IsNothrowInvocableStruct<Callable, Args...>::value;
#endif
}