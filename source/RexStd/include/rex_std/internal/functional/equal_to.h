// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: equal_to
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename T = void>
    struct equal_to
    {
      /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Aug/2022)
      // the standard doesn't template the second argument.
      // we do so we can, for example, compare a string with a const char*
      // without the second getting promoted to a string
      template <typename U>
      constexpr bool operator()(const T& lhs, const U& rhs) const
      {
        return lhs == rhs;
      }
    };

  } // namespace v1
} // namespace rsl
