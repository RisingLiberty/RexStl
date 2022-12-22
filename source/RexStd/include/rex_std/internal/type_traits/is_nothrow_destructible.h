// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_nothrow_destructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_destructible.h"
#include "rex_std/internal/type_traits/is_reference.h"
#include "rex_std/internal/type_traits/is_scalar.h"
#include "rex_std/internal/type_traits/remove_all_extents.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <bool, typename Tp>
      struct is_nothrow_destructible;

      template <typename Tp>
      struct is_nothrow_destructible<false, Tp> : public false_type
      {
      };

      template <typename Tp>
      struct is_nothrow_destructible<true, Tp> : public bool_constant<noexcept(rsl::declval<Tp>().~Tp())>
      {
      };
    } // namespace internal

    template <typename Tp>
    struct is_nothrow_destructible : public internal::is_nothrow_destructible<is_destructible_v<Tp>, Tp>
    {
    };

    template <typename Tp, size_t Ns>
    struct is_nothrow_destructible<Tp[Ns]> : public is_nothrow_destructible<Tp> // NOLINT(modernize-avoid-c-arrays)
    {
    };

    template <typename Tp>
    struct is_nothrow_destructible<Tp&> : public true_type
    {
    };

    template <typename Tp>
    struct is_nothrow_destructible<Tp&&> : public true_type
    {
    };

    template <typename T>
    inline constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;
  } // namespace v1
} // namespace rsl
