// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: zero_memory.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/memory/zero_memory.h"

#include "rex_std/internal/memory/memset.h"

namespace rsl
{
  inline namespace v1
  {
    void zero_memory(void* dst, card64 size)
    {
      memset(dst, 0, size);
    }
  } // namespace v1
} // namespace rsl