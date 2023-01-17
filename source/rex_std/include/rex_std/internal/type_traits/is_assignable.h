// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_assignable.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename To, typename From>
    struct is_assignable : bool_constant<__is_assignable(To, From)>
    {
    };

    template <typename To, typename From>
    inline constexpr bool is_assignable_v = is_assignable<To, From>::value;

  } // namespace v1
} // namespace rsl
