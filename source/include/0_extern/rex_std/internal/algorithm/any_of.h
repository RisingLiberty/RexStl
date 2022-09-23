// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: any_of.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename InputIterator, typename Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate p)
{
  for(; first != last; ++first)
  {
    if(p(*first))
      return true;
  }
  return false;
}

REX_RSL_END_NAMESPACE
