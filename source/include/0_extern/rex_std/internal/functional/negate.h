// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: negate.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T = void>
struct negate
{
  constexpr T operator()(const T& arg) const
  {
    return -arg;
  }
};

REX_RSL_END_NAMESPACE
