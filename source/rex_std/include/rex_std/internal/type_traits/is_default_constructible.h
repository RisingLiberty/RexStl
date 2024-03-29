// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_default_constructible.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_constructible.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct is_default_constructible : bool_constant<__is_constructible(T)>
    {
    };

    template <typename T>
    inline constexpr bool is_default_constructible_v = is_default_constructible<T>::value;

  } // namespace v1
} // namespace rsl
