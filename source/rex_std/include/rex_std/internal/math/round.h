// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: round.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/math/abs.h"
#include "rex_std/internal/math/signbit.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    constexpr T round(const T x)
    {
      return internal::abs(x) - 0.5f < static_cast<int32>(internal::abs(x)) ? signbit(x) * static_cast<T>(static_cast<int32>(internal::abs(x))) : static_cast<T>(static_cast<int32>(x) + signbit(x) * 1);
    }

  } // namespace v1
} // namespace rsl
