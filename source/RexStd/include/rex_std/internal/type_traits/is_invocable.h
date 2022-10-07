// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_invocable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_invocable_utils.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Callable, typename... Args>
    struct is_invocable : internal::SelectInvokeTraits<Callable, Args...>::is_invocable_v
    {
    };

    template <typename Callable, typename... Args>
    inline constexpr bool is_invocable_v = is_invocable<Callable, Args...>::value;

  } // namespace v1
} // namespace rsl