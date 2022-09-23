// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_nothrow_swappable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_swappable_utils.h"
#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T>
  struct IsNoThrowSwappableHelperNoExceptWrapper
  {
    const static bool value = noexcept(swap(declval<T&>(), declval<T&>()));
  };

  template <typename T, bool>
  struct IsNoThrowSwappableHelper : public bool_constant<IsNoThrowSwappableHelperNoExceptWrapper<T>::value>
  {
  };

  template <typename T>
  struct IsNoThrowSwappableHelper<T, false> : public false_type
  {
  };
} // namespace internal

template <typename T>
struct is_nothrow_swappable : internal::IsNoThrowSwappableHelper<T, is_swappable_v<T>>
{
};

template <typename T>
constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;

REX_RSL_END_NAMESPACE
