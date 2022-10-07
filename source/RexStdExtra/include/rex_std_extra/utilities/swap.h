// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: swap.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
constexpr void swap_adl(T& lhs, T& rhs)
{
  T tmp = std::move(lhs);
  lhs   = std::move(rhs);
  rhs   = std::move(tmp);
}

template <typename It>
constexpr void iter_swap(It& lhs, It& rhs)
{
  swap_adl(*lhs, *rhs);
}

REX_RSL_END_NAMESPACE