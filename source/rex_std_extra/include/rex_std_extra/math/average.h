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

REX_RSL_BEGIN_NAMESPACE

template <typename Iterator>
REX_NO_DISCARD constexpr typename Iterator::value_type average(const Iterator first, const Iterator last)
{
  using underlying_type = typename Iterator::value_type;

  underlying_type value = rsl::accumulate(first, last, underlying_type());
  auto diff             = rsl::distance(first, last);
  return value /= clamp_min(diff, 1);
}

REX_RSL_END_NAMESPACE