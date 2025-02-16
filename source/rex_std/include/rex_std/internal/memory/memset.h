// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: memset.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/memory/byte.h"

namespace rsl
{
  inline namespace v1
  {

    constexpr void* memset(void* dest, char val, card64 len)
    {
      rsl::byte* dest_b = static_cast<byte*>(dest);
      while (len-- > 0)
      {
        *dest_b++ = static_cast<byte>(val);
      }
      return dest;
    }

  } // namespace v1
} // namespace rsl
