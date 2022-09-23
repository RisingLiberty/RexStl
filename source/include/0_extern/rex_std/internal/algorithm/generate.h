// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: generate.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename InputIterator, typename Generator>
void generate(InputIterator first, InputIterator last, Generator g)
{
  auto it = first;
  while(it != last)
  {
    *it = g();
    ++it;
  }
}

REX_RSL_END_NAMESPACE
