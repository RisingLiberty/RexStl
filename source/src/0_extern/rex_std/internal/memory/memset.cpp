// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: memset.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/memory/memset.h"
#include "rex_std/internal/memory/byte.h"

REX_RSL_BEGIN_NAMESPACE

    void* memset(void* dest, char val, count_t len)
    {
      rsl::byte* dest_b = static_cast<byte*>(dest);
      while (len-- > 0)
      {
        *dest_b++ = static_cast<byte>(val);
      }
      return dest;
    }

REX_RSL_END_NAMESPACE