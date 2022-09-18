// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: invoke_result.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_invocable_utils.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename Callable, typename ... Args>
    struct invoke_result : internal::SelectInvokeTraits<Callable, Args...>
    {};

    template <typename Callable, typename ... Args>
    using invoke_result_t = invoke_result<Callable, Args...>::type;

REX_RSL_END_NAMESPACE
