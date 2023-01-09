// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: memcpy.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/memory/byte.h"

namespace rsl
{
  inline namespace v1
  {
    // TODO: are there more performant ways of copying bytes over that is defined behavior?
    // Maybe cast the memory to int32 or int64, so we can copy over more bytes in 1 go
    constexpr void* memcpy(void* dst, const void* src, count_t len)
    {
      const rsl::byte* src_byte = static_cast<const rsl::byte*>(src);
      rsl::byte* dst_byte       = static_cast<rsl::byte*>(dst);

      // Copy contents of src[] to dest[]
      for(count_t i = 0; i < len; ++i)
      {
        dst_byte[i] = src_byte[i];

        // using the following code instead of the above breaks clang when optimizations are enabled
        // as it can possibly skip a call to memcpy, resulting in bugs that are incredibly hard to track down

        //   *dst_byte = *src_byte;
        //   ++dst_byte;
        //   ++src_byte;
      }

      return dst;
    }
  } // namespace v1
} // namespace rsl
