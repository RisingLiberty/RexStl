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
    template <typename T, typename U>
    constexpr bool has_flag(T val, U flag)
    {
      static_assert(rsl::is_integral_v<T> || rsl::is_enum_v<T>, "T must be of integral or enum type");
      static_assert(rsl::is_integral_v<U> || rsl::is_enum_v<U>, "U must be of integral or enum type");

      uint64 val_int = static_cast<uint64>(val);
      uint64 flag_int = static_cast<uint64>(flag);

      return (val_int & flag_int) == flag_int;
    }
  } // namespace v1
} // namespace rsl
