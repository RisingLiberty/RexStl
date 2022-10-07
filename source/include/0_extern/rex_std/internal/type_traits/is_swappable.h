// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_swappable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_swappable_utils.h"
#include "rex_std/bonus/type_traits/unused.h"
#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct is_swappable : public bool_constant<!is_same_v<decltype(swap(declval<T&>(), declval<T&>())), Unused>>
    {
    };

    template <typename T>
    inline constexpr bool is_swappable_v = is_swappable<T>::value;

  } // namespace v1
} // namespace rsl
