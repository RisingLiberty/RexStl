// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: average.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include <numeric>

namespace rsl
{
  inline namespace v1
  {

    template <typename Iterator>
    REX_NO_DISCARD constexpr typename Iterator::value_type average(const Iterator first, const Iterator last)
    {
      using underlying_type = typename Iterator::value_type;

      underlying_type value = rsl::accumulate(first, last, underlying_type());
      auto diff             = rsl::distance(first, last);
      return value /= clamp_min(diff, 1);
    }

  } // namespace v1
} // namespace rsl