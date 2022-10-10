// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: move.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_const.h"
#include "rex_std/internal/type_traits/is_lvalue_reference.h"
#include "rex_std/internal/type_traits/is_move_assignable.h"
#include "rex_std/internal/type_traits/is_move_constructible.h"
#include "rex_std/internal/type_traits/remove_reference.h"

namespace rsl
{
  inline namespace v1
  {

    /// RSL Comment: Different from ISO C++ Standard at time of writing (04/Aug/2022)
    // rex will fail to compile if move is called with a const T.
    template <typename T>
    constexpr typename rsl::remove_reference_t<T>&& move(T&& x) noexcept
    {
      return static_cast<typename rsl::remove_reference_t<T>&&>(x);
    }
    template <typename T>
    constexpr const T& move(const T& x)
    {
      static_assert(is_move_constructible_v<T> || is_move_assignable_v<T>, "calling move with a const T that can be moved");
      return x;
    }
  } // namespace v1
} // namespace rsl
