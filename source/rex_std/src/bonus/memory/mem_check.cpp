// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mem_check.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/memory/mem_check.h"
#include "rex_std/array.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    const void* memcheck(const void* p, uint8 value, count_t byteCount)
    {
      for(const uint8* p8 = static_cast<const uint8*>(p); byteCount > 0; ++p8, --byteCount)
      {
        if(*p8 != value)
        {
          return p8;
        }
      }

      return nullptr;
    }
    const void* memcheck(const void* p, uint16 value, count_t byteCount)
    {
      union u16
      {
        explicit u16(uint16 val = 0)
        : c16(val)
        {}

        uint16 c16;
        rsl::array<uint8, 2> c8;
      };
      const u16 u(value);
      size_t i    = static_cast<size_t>(reinterpret_cast<uintptr>(p) % sizeof(uint16)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

      for(const uint8 *p8 = static_cast<const uint8*>(p), *p8_end = static_cast<const uint8*>(p) + byteCount; p8 != p8_end; ++p8, i ^= 1u)
      {
        if(*p8 != u.c8[static_cast<card32>(i)]) // NOLINT(cppcoreguidelines-pro-type-union-access)
        {
          return p8;
        }
      }

      return nullptr;
    }
    const void* memcheck(const void* p, uint32 value, count_t byteCount)
    {
      union u32
      {
        explicit u32(uint32 val = 0)
        : c32(val)
        {}

        uint32 c32;
        rsl::array<uint8, 4> c8;
      };
      const u32 u(value);
      size_t i    = static_cast<size_t>(reinterpret_cast<uintptr>(p) % sizeof(uint32)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

      for(const uint8 *p8 = static_cast<const uint8*>(p), *p8_end = static_cast<const uint8*>(p) + byteCount; p8 != p8_end; ++p8, i = (i + 1) % 4)
      {
        if(*p8 != u.c8[static_cast<card32>(i)]) // NOLINT(cppcoreguidelines-pro-type-union-access)
        {
          return p8;
        }
      }

      return nullptr;
    }
    const void* memcheck(const void* p, uint64 value, count_t byteCount)
    {
      union u64
      {
        explicit u64(uint64 val = 0)
        : c64(val)
        {}

        uint64 c64;
        rsl::array<uint8, 8> c8;
      };
      const u64 u(value);
      size_t i    = static_cast<size_t>(reinterpret_cast<uintptr>(p) % sizeof(uint64)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

      for(const uint8 *p8 = static_cast<const uint8*>(p), *p8_end = static_cast<const uint8*>(p) + byteCount; p8 != p8_end; ++p8, i = (i + 1) % 8)
      {
        if(*p8 != u.c8[static_cast<card32>(i)]) // NOLINT(cppcoreguidelines-pro-type-union-access)
        {
          return p8;
        }
      }

      return nullptr;
    }

    const void* memcheck(const void* p, int8 value, count_t byteCount)
    {
      return memcheck(p, static_cast<uint8>(value), byteCount);
    }
    const void* memcheck(const void* p, int16 value, count_t byteCount)
    {
      return memcheck(p, static_cast<uint16>(value), byteCount);
    }
    const void* memcheck(const void* p, int32 value, count_t byteCount)
    {
      return memcheck(p, static_cast<uint32>(value), byteCount);
    }
    const void* memcheck(const void* p, int64 value, count_t byteCount)
    {
      return memcheck(p, static_cast<uint64>(value), byteCount);
    }
  } // namespace v1
} // namespace rsl