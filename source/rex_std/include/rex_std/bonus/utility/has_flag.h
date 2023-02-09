// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: has_flag.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/is_enum.h"
#include "rex_std/internal/type_traits/is_integral.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T, rsl::enable_if_t<rsl::is_enum_v<T>, bool> = true>
    constexpr bool has_flag(T val, T flag)
    {
      return (val & flag) == flag;
    }

    template <typename T, typename U, rsl::enable_if_t<rsl::is_integral_v<T>, bool> = true>
    constexpr bool has_flag(T val, U flag)
    {
      U u_val = static_cast<T>(val);
      return (u_val & flag) == flag;
    }
  } // namespace v1
} // namespace rsl
