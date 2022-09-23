// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: call_traits.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_arithmetic.h"
#include "rex_std/internal/type_traits/is_pointer.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T, bool IsSmall>
  struct call_traitsImpl2
  {
    using param_type = const T&;
  };

  template <typename T>
  struct call_traitsImpl2<T, true>
  {
    using param_type = T;
  };

  template <typename T, bool is_pointer_v, bool B1>
  struct call_traitsImpl
  {
    using param_type = const T&;
  };

  template <typename T, bool is_pointer_v>
  struct call_traitsImpl<T, is_pointer_v, true>
  {
    using param_type = typename call_traitsImpl2<T, sizeof(T) <= sizeof(void*)>::param_type;
  };

  template <typename T, bool B1>
  struct call_traitsImpl<T, true, B1>
  {
    using param_type = const T;
  };
} // namespace internal

template <typename T>
struct call_traits
{
public:
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;
  using param_type      = typename internal::call_traitsImpl<T, is_pointer_v<T>, is_arithmetic_v<T>>::param_type;
};

template <typename T>
struct call_traits<T&>
{
public:
  using value_type      = T&;
  using reference       = T&;
  using const_reference = const T&;
  using param_type      = T&;
};

template <typename T, card32 N>
struct call_traits<T[N]>
{
private:
  using array_type = T[N];

public:
  using value_type      = const T*;
  using reference       = array_type&;
  using const_reference = const array_type&;
  using param_type      = const T* const;
};

template <typename T, card32 N>
struct call_traits<const T[N]>
{
private:
  using array_type = const T[N];

public:
  using value_type      = const T*;
  using reference       = array_type&;
  using const_reference = const array_type&;
  using param_type      = const T* const;
};

REX_RSL_END_NAMESPACE
