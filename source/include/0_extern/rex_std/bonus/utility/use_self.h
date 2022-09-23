// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: use_self.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct use_self
{
  using result_type = T;

  const T& operator()(const T& x) const
  {
    return x;
  }
};

REX_RSL_END_NAMESPACE