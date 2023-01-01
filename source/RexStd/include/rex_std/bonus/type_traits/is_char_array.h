// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_char_array.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_character.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/remove_const.h"
#include "rex_std/internal/type_traits/remove_extent.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    inline constexpr bool is_char_array_v = rsl::is_character_v<rsl::remove_const_t<rsl::remove_extent_t<T>>> && rsl::is_array_v<T>;

    template <typename T>
    struct is_char_array : rsl::bool_constant<is_char_array_v<T>>
    {
    };
  } // namespace v1
} // namespace rsl
