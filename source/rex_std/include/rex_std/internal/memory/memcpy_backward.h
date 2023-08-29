// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: memcpy_backward.h
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

    constexpr void* memcpy_backward(void* dst, const void* src, card32 len)
    {
      byte* dst_byte       = static_cast<byte*>(dst);
      const byte* src_byte = static_cast<const byte*>(src);

      for(card32 i = len - 1; i >= 0; --i)
      {
        dst_byte[i] = src_byte[i];
      }
      return dst;
    }

  } // namespace v1
} // namespace rsl
