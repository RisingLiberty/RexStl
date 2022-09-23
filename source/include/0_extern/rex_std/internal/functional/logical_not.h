// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: logical_not.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T = void>
struct logical_not
{
  /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Aug/2022)
  // the standard doesn't template the second argument.
  // we do so we can, for example, compare a string with a const char*
  // without the second getting promoted to a string
  constexpr T operator()(const T& arg) const
  {
    return !arg;
  }
};

REX_RSL_END_NAMESPACE
