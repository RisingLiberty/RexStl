// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: scopeguard.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/utilities/scopeguard.h"

rsl::scope_guard::scope_guard(rsl::function<void()> func)
    : m_function(func)
{
}

rsl::scope_guard::~scope_guard()
{
  if(!m_is_released)
  {
    m_function();
  }
}

void rsl::scope_guard::release()
{
  m_is_released = true;
}