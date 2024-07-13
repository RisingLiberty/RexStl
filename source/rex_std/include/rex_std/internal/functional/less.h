// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: less.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T = void>
    struct less
    {
      using is_transparent = rsl::true_type;

      // Perform the less operator on the type
      // This function is provided to avoid compiler errors where the below 2 functions
      // turn out to be ambiguous if T == U
      constexpr bool operator()(const T& lhs, const T& rhs) const
      {
        return lhs < rhs;
      }

      /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Aug/2022)
      // the standard doesn't template the second argument.
      // we do so we can, for example, compare a string with a const char*
      // without the second getting promoted to a string
      template <typename U = T>
      constexpr bool operator()(const T& lhs, const U& rhs) const
      {
        return lhs < rhs;
      }

      /// RSL Comment: Different from ISO C++ Standard at time of writing (06/Jul/2024)
      // the standard doesn't template the second argument.
      // we do so we can, for example, compare a string with a const char*
      // without the second getting promoted to a string
      template <typename U = T>
      constexpr bool operator()(const U& lhs, const T& rhs) const
      {
        return lhs < rhs;
      }
    };

  } // namespace v1
} // namespace rsl
