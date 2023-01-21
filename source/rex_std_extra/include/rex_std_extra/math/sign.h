// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: sigb.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl { inline namespace v1 {

template <typename T>
constexpr T sign(T num)
{
  return num > 0 ? T(+1) : num < 0 ? T(-1) : T();
}

template <typename T>
constexpr bool is_negative(T val)
{
  static_assert(rsl::is_signed_v<T>, "T must be signed");
  return val < 0;
}
template <typename T>
constexpr bool is_positive(T val)
{
  static_assert(rsl::is_signed_v<T>, "T must be signed");
  return val > 0;
}

}}