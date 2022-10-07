// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: common_type.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/decay.h"
#include "rex_std/internal/type_traits/void.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename... T>
    struct common_type;

    template <typename... T>
    using common_type_t = typename common_type<T...>::type;

    template <>
    struct common_type<>
    {
    };

    template <typename T1>
    struct common_type<T1> : common_type_t<T1, T1>
    {
    };

    namespace internal
    {
      template <typename T1, typename T2, typename Decayed1 = decay_t<T1>, typename Decayed2 = decay_t<T2>>
      struct common_type2 : common_type<Decayed1, Decayed2>
      {
      };

      template <typename T1, typename T2, typename = void>
      struct decayed_cond_oper
      {
      };

      template <typename T1, typename T2>
      struct common_type2<T1, T2, T1, T2> : decayed_cond_oper<T1, T2>
      {
      };

      template <typename VoidT, typename T1, typename T2, typename... Rest>
      struct common_type3
      {
      };

      template <typename T1, typename T2, typename... Rest>
      struct common_type3<void_t<common_type_t<T1, T2>>, T1, T2, Rest...> : common_type<common_type_t<T1, T2>, Rest...>
      {
      };
    } // namespace internal

    template <typename T1, typename T2, typename... Rest>
    struct common_type<T1, T2, Rest...> : internal::common_type3<void, T1, T2, Rest...>
    {
    };

  } // namespace v1
} // namespace rsl