// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_member_object_pointer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_function.h"
#include "rex_std/internal/type_traits/remove_cv.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename>
  struct is_member_object_pointer
  {
    static constexpr bool value = false;
  };

  template <typename T1, typename T2>
  struct is_member_object_pointer<T1 T2::*>
  {
    static constexpr bool value = !is_function_v<T1>;
    using class_type            = T2;
  };
} // namespace internal

template <typename _Ty>
inline constexpr bool is_member_object_pointer_v = internal::is_member_object_pointer<remove_cv_t<_Ty>>::value;

template <typename T>
struct is_member_object_pointer : bool_constant<is_member_function_pointer_v<T>>
{
};

REX_RSL_END_NAMESPACE
