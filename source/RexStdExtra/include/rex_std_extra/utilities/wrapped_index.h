// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: wrapped_index.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

class WrappedIndex
{
public:
  WrappedIndex(card32 min, card32 max);
  WrappedIndex(card32 value, card32 min, card32 max);

  operator card32() const;

  void increment(card32 inc_size = 1);
  void decrement(card32 dec_size = 1);

private:
  card32 m_value;
  card32 m_max;
  card32 m_min;
};

REX_RSL_END_NAMESPACE