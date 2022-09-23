// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: for_each.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename InputIterator, typename Func>
void for_each(InputIterator first, InputIterator last, Func func)
{
  auto it = first;
  while(it != last)
  {
    func(*it);
    ++it;
  }
}

REX_RSL_END_NAMESPACE
