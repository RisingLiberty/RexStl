// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_floating_point.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/remove_cv.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T>
  struct IsFloatingPointHelper : public false_type
  {
  };

  template <>
  struct IsFloatingPointHelper<float32> : public true_type
  {
  };
  template <>
  struct IsFloatingPointHelper<float64> : public true_type
  {
  };

  // other types that aren't really used by rex engine, but we still need regardless
  template <>
  struct IsFloatingPointHelper<lfloat64> : public true_type
  {
  };
} // namespace internal

template <typename T>
struct is_floating_point : public internal::IsFloatingPointHelper<typename rsl::remove_cv_t<T>>
{
};

template <typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;

REX_RSL_END_NAMESPACE
