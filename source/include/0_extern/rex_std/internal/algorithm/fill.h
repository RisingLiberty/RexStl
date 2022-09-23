// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: fill.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_scalar.h"

REX_RSL_BEGIN_NAMESPACE

template <typename InputIterator, typename T>
void fill(InputIterator first, InputIterator end, const T& value)
{
  for(auto dst = first; dst != end; ++dst)
  {
    *dst = value;
  }
}

REX_RSL_END_NAMESPACE
