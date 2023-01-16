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

#include "rex_std_extra/utilities/wrapped_index.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::WrappedIndex::WrappedIndex(card32 min, card32 max)
    : m_value(0)
    , m_min(min)
    , m_max(max)
{
}

rsl::WrappedIndex::WrappedIndex(card32 value, card32 min, card32 max)
    : m_value(value)
    , m_min(min)
    , m_max(max)
{
}

rsl::WrappedIndex::operator rsl::card32() const
{
  return m_value;
}

void rsl::WrappedIndex::increment(card32 inc_size)
{
  m_value += inc_size;

  if(m_value >= m_max)
  {
    m_value = m_min;
  }
}
void rsl::WrappedIndex::decrement(card32 dec_size)
{
  m_value -= dec_size;

  if(m_value < m_min)
  {
    m_value = m_max - 1;
  }
}