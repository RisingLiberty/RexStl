// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: yes_no.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/utilities/yes_no.h"

rsl::yes_no::yes_no(eyes_no value)
    : m_value(value)
{
}

rsl::yes_no::operator bool() const
{
  return m_value == eyes_no::yes;
}