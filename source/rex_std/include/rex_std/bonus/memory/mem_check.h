// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mem_check.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    constexpr const void* memcheck(const void* p, uint8 value, count_t byteCount)
    {
      for (const uint8* p8 = (const uint8*)p; byteCount > 0; ++p8, --byteCount)
      {
        if (*p8 != value)
        {
          return p8;
        }
      }

      return nullptr;
    }
    constexpr const void* memcheck(const void* p, uint8 value, count_t byteCount)
    {
      union U16
      {
        uint16 c16;
        uint8  c8[2];
      };
      const U16 u = { value };
      size_t    i = (size_t)((uintptr)p % sizeof(uint16));

      for (const uint8* p8 = (const uint8*)p, *p8End = (const uint8*)p + byteCount; p8 != p8End; ++p8, i ^= 1)
      {
        if (*p8 != u.c8[i])
        {
          return p8;
        }
      }

      return nullptr;

    }
    constexpr const void* memcheck(const void* p, uint8 value, count_t byteCount)
    {
      union U32 
      {
        uint32 c32;
        uint8  c8[4];
      };
      const U32 u = { value };
      size_t    i = (size_t)((uintptr)p % sizeof(uint32));

      for (const uint8* p8 = (const uint8*)p, *p8End = (const uint8*)p + byteCount; p8 != p8End; ++p8, i = (i + 1) % 4)
      {
        if (*p8 != u.c8[i])
        {
          return p8;
        }
      }

      return nullptr;
    }
    constexpr const void* memcheck(const void* p, uint8 value, count_t byteCount)
    {
      union U64 
      {
        uint64 c64;
        uint8  c8[8];
      };
      const U64 u = { value };
      size_t    i = (size_t)((uintptr)p % sizeof(uint64));

      for (const uint8* p8 = (const uint8*)p, *p8End = (const uint8*)p + byteCount; p8 != p8End; ++p8, i = (i + 1) % 8)
      {
        if (*p8 != u.c8[i])
        {
          return p8;
        }
      }

      return nullptr;

    }
  }
}