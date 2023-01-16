// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_trivially_destructible.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct is_trivially_destructible : bool_constant<__is_trivially_destructible(T)>
    {
    };

    template <typename T>
    inline constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;

  } // namespace v1
} // namespace rsl
