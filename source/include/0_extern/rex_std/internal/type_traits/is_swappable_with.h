// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_swappable_with.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_swappable_utils.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_same.h"
#include "rex_std/internal/type_traits/is_void.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T, typename U, bool OneTypeIsvoid = (is_void_v<T> || is_void_v<U>)>
  struct IsSwappableWithHelper
  {
    static const bool value = !is_same_v<decltype(swap(declval<T>(), declval<U>())), Unused>::value && !is_same_v<decltype(swap(declval<U>(), declval<T>())), Unused>::value;
  };

  template <typename T, typename U>
  struct IsSwappableWithHelper<T, U, true>
  {
    static const bool value = false;
  };
} // namespace internal

template <typename T, typename U>
    struct is_swappable_with : public bool_constant < internal::IsSwappableWithHelper<T, U>::value
{
};

template <typename T, typename U>
constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;

REX_RSL_END_NAMESPACE
