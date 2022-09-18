// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_invocable_r.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_invocable_utils.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        template <typename Rx, typename Callable, typename ... Args>
        using IsInvocableRHelper = typename internal::SelectInvokeTraits<Callable, Args...>::template IsInvocableRHelper<Rx>;

        template <typename Rx, typename Callable, typename ... Args>
        struct IsInvocableRHelper : IsInvocableRHelper<Rx, Callable, Args...>
        {};
    }
    
    template <typename Rx, typename Callable, typename ... Args>
    struct is_invocable_r : internal::IsInvocableRHelper<Rx, Callable, Args>
    {};

    template <typename Rx, typename Callable, typename ... Args>
    constexpr bool is_invocable_r_v = is_convertible<Rx, Callable, Args...>;

REX_RSL_END_NAMESPACE
