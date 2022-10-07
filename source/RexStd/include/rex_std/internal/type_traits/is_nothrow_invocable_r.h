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
  inline namespace v1
  {

    template <typename Rx, typename Callable, typename... Args>
    struct is_nothrow_invocable_r : internal::SelectInvokeTraits<Callable, Args...>::template is_nothrow_invocable_r_v<Rx>
    {
    };

    template <typename Rx, typename Callable, typename... Args>
    inline constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<Rx, Callable, Args...>;

  } // namespace v1
} // namespace rsl