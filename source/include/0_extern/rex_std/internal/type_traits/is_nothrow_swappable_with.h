// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_nothrow_swappable_with.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_swappable_utils.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_void.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T, typename U, bool OneTypeIsVoid = (is_void_v<T> || is_void_v<U>)>
  struct IsNoThrowSwappableWithHelper
  {
    static const bool value = noexcept(swap(declval<T>(), declval<U>()))&& noexcept(swap(declval<U>(), declval<T>()));
  };

  template <typename T, typename U>
  struct IsNoThrowSwappableWithHelper<T, U, true>
  {
    static const bool value = false;
  };
} // namespace internal

template <typename T, typename U>
struct is_nothrow_swappable_with : public bool_constant<internal::IsNoThrowSwappableWithHelper<T, U>::value>
{
};

template <typename T, typename U>
inline constexpr bool is_nothrow_swappable_with = is_nothrow_swappable_with<T>::value;

REX_RSL_END_NAMESPACE
