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

REX_RSL_BEGIN_NAMESPACE

    template <typename Callable, typename ... Args>
    struct is_nothrow_invocable : internal::SelectInvokeTraits<Callable, Args...>::is_nothrow_invocable_v
    {};

    template <typename Callable, typename ... Args>
    constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<Callable, Args...>::value;

REX_RSL_END_NAMESPACE
