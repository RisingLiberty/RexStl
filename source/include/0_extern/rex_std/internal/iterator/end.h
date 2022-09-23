// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: end.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

template <typename C>
auto end(C& c) -> decltype(c.end())
{
  return c.end();
}
template <typename C>
auto end(const C& c) -> decltype(c.end())
{
  return c.end();
}
template <typename T, card32 N>
T* end(T (&array)[N])
{
  return &array[N];
}
template <typename C>
auto cend(const C& c) -> decltype(c.cend())
{
  return c.cend();
}

REX_RSL_END_NAMESPACE
