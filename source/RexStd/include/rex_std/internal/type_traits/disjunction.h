// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: disjunction.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <bool FirstValue, typename First, typename... Rest>
      struct disjunction
      {
        using type = First;
      };

      template <typename False, typename Next, typename... Rest>
      struct disjunction<false, False, Next, Rest...>
      {
        using type = typename disjunction<Next::value, Next, Rest...>::type;
      };
    } // namespace internal

    template <typename... Traits>
    struct disjunction : false_type
    {
    };

    template <typename First, typename... Rest>
    struct disjunction<First, Rest...> : internal::disjunction<First::value, First, Rest...>::type
    {
    };

    template <typename... Traits>
    using disjunction_t = typename disjunction<Traits...>::type;

  } // namespace v1
} // namespace rsl
