// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: wrapped_index.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/utility/wrapped_index.h"

rsl::wrapped_index::wrapped_index(card32 min, card32 max)
    : m_value(0)
    , m_max(max)
    , m_min(min)
{
}

rsl::wrapped_index::wrapped_index(card32 value, card32 min, card32 max)
    : m_value(value)
    , m_max(max)
    , m_min(min)
{
}

rsl::wrapped_index::operator rsl::card32() const
{
  return m_value;
}

void rsl::wrapped_index::increment(card32 incSize)
{
  m_value += incSize;

  if(m_value >= m_max)
  {
    m_value = m_min;
  }
}
void rsl::wrapped_index::decrement(card32 decSize)
{
  m_value -= decSize;

  if(m_value < m_min)
  {
    m_value = m_max - 1;
  }
}