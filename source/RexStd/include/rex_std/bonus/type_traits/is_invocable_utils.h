// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_invocable_utils.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/returns_exactly.h"
#include "rex_std/internal/type_traits/conjunction.h"
#include "rex_std/internal/type_traits/disjunction.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_nothrow_convertible.h"
#include "rex_std/internal/type_traits/is_void.h"
#include "rex_std/internal/utility/declval.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename VoidT, typename Callable>
      struct invoke_traits_zero
      {
        using is_invocable_v         = false_type;
        using is_nothrow_invocable_v = false_type;
        template <typename Rx>
        using is_invocable_r_v = false_type;
        template <typename Rx>
        using is_nothrow_invocable_r_v = false_type;
      };

      template <typename From, typename To, typename = void>
      struct invoke_convertible : public false_type
      {
      };

      template <typename From, typename To>
      struct invoke_convertible<From, To, void_t<decltype(implicitly_convert_to<To>(returns_exactly<From>()))>> : true_type
      {
      };

      template <typename From, typename To>
      struct invoke_nothrow_convertible : bool_constant<noexcept(implicitly_convert_to<To>(returns_exactly<From>()))>
      {
      };

      template <typename Result, bool NoThrow>
      struct invoke_traits_common
      {
        using type               = Result;
        using is_invocable_v     = true_type;
        using IsNothrowInvocable = bool_constant<NoThrow>;
        template <typename Rx>
        using is_invocable_r = bool_constant<disjunction_v<is_void<Rx>, invoke_convertible<type, Rx>>>;
        template <typename Rx>
        using is_nothrow_invocable_r_v = bool_constant<conjunction_v<IsNothrowInvocable, disjunction<is_void_v<Rx>, conjunction<invoke_convertible<type, Rx>, invoke_nothrow_convertible<type, Rx>>>>>;
      };

      template <typename Void, typename... Types>
      struct invoke_traits_non_zero
      {
        using is_invocable         = false_type;
        using is_nothrow_invocable = false_type;
        template <typename Rx>
        using is_invocable_r = false_type;
        template <typename Rx>
        using is_nothrow_invocable_r = false_type;
      };

      template <typename Callable>
      using DecltypeInvokeNonZero = decltype(declval<Callable>()());

      template <typename Callable>
      struct invoke_traits_non_zero<void_t<DecltypeInvokeNonZero<Callable>>, Callable> : invoke_traits_common<DecltypeInvokeNonZero<Callable>, noexcept(declval<Callable>()())>
      {
      };

      template <typename Callable, typename... Args>
      using SelectInvokeTraits = conditional_t<sizeof...(Args) == 0, invoke_traits_zero<void, Callable>, invoke_traits_non_zero<void, Callable, Args...>>;
    } // namespace internal

  } // namespace v1
} // namespace rsl
