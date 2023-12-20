// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: conditional_static_cast.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    // to avoid useless casts (see https://github.com/nlohmann/json/issues/2893#issuecomment-889152324)
    template <typename T, typename U, rsl::enable_if_t<!rsl::is_same<T, U>::value, int> = 0>
    constexpr T conditional_static_cast(U value)
    {
      return static_cast<T>(value);
    }

    template <typename T, typename U, rsl::enable_if_t<rsl::is_same<T, U>::value, int> = 0>
    constexpr T conditional_static_cast(U value)
    {
      return value;
    }
  } // namespace v1
} // namespace rsl