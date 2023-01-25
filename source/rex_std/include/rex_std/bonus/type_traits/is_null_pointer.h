// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_null_pointer.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_same.h"
#include "rex_std/internal/type_traits/remove_cv.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    inline constexpr bool is_null_pointer_v = is_same_v<remove_cv_t<T>, decltype(nullptr)>;

    template <typename T>
    struct is_null_pointer : bool_constant<is_null_pointer_v<T>>
    {
    };
  } // namespace v1
} // namespace rsl
