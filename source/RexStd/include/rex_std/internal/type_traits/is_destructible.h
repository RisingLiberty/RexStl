// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_destructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_function.h"
#include "rex_std/internal/type_traits/remove_all_extents.h"
#include "rex_std/internal/utility/declval.h"

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    struct is_destructible : bool_constant<__is_destructible(T)>
    {
    };

    template <typename T>
    inline constexpr bool is_destructible_v = is_destructible<T>::value;
#else
    namespace internal
    {
      template <typename>
      struct is_destructible_apply
      {
        using type = int;
      };

      struct two
      {
        char lx[2]; // NOLINT(modernize-avoid-c-arrays)
      };

      template <typename T>
      struct is_destructor_wellformed
      {
        template <typename Tp1>
        static char test(typename is_destructible_apply<decltype(rsl ::declval<Tp1&>().~Tp1())>::type);

        template <typename Tp1>
        static two test(...);

        static constexpr bool value = sizeof(test<T>(12)) == sizeof(char);
      };

      template <typename T, bool>
      struct destructible_imp;

      template <typename T>
      struct destructible_imp<T, false> : public rsl::bool_constant<is_destructor_wellformed<typename rsl::remove_all_extents<T>::type>::value>
      {
      };

      template <typename T>
      struct destructible_imp<T, true> : public rsl::true_type
      {
      };

      template <typename T, bool>
      struct destructible_false;

      template <typename T>
      struct destructible_false<T, false> : public destructible_imp<T, rsl::is_reference<T>::value>
      {
      };

      template <typename T>
      struct destructible_false<T, true> : public rsl::false_type
      {
      };
    } // namespace internal

    template <typename T>
    struct is_destructible : public internal::destructible_false<T, rsl::is_function<T>::value>
    {
    };

    template <typename T>
    struct is_destructible<T[]> : public rsl::false_type // NOLINT(modernize-avoid-c-arrays)
    {
    };

    template <>
    struct is_destructible<void> : public rsl::false_type
    {
    };

    template <typename T>
    inline constexpr bool is_destructible_v = is_destructible<T>::value;
#endif

  } // namespace v1
} // namespace rsl
