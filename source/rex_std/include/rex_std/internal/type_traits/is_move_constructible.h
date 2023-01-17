// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_move_constructible.h
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
    struct is_move_constructible : bool_constant<__is_constructible(T, T)>
    {
    };

    template <typename T>
    inline constexpr bool is_move_constructible_v = is_move_constructible<T>::value;

  } // namespace v1
} // namespace rsl
