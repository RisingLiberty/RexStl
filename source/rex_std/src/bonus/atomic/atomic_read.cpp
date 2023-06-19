// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_read.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/atomic//atomic_read.h"

#include <Windows.h> // IWYU pragma: keep

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      int16 atomic_read(int16* data)
      {
        return _InterlockedCompareExchange16(data, 0, 0);
      }
      int32 atomic_read(int32* data)
      {
        return _InterlockedCompareExchange(reinterpret_cast<volatile long*>(data), 0, 0); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }
      int64 atomic_read(int64* data)
      {
        return _InterlockedCompareExchange64(data, 0, 0);
      }
      uint16 atomic_read(uint16* data)
      {
        return static_cast<uint16>(atomic_read(reinterpret_cast<int16*>(data))); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }
      uint32 atomic_read(uint32* data)
      {
        return _InterlockedCompareExchange(data, 0, 0);
      }
      uint64 atomic_read(uint64* data)
      {
        return _InterlockedCompareExchange(reinterpret_cast<volatile uint64*>(data), 0, 0); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }
    } // namespace internal

    int8 atomic_read(int8& val)
    {
      int32 i32_val = val; // NOLINT(bugprone-signed-char-misuse)
      return static_cast<int8>(internal::atomic_read(&i32_val));
    }
    int16 atomic_read(int16& val)
    {
      return internal::atomic_read(&val);
    }
    int32 atomic_read(int32& val)
    {
      return internal::atomic_read(&val);
    }
    int64 atomic_read(int64& val)
    {
      return internal::atomic_read(&val);
    }

    uint8 atomic_read(uint8& val)
    {
      uint32 u32_val = val;
      return static_cast<uint8>(internal::atomic_read(&u32_val));
    }
    uint16 atomic_read(uint16& val)
    {
      return internal::atomic_read(&val);
    }
    uint32 atomic_read(uint32& val)
    {
      return internal::atomic_read(&val);
    }
    uint64 atomic_read(uint64& val)
    {
      return internal::atomic_read(&val);
    }
  } // namespace v1
} // namespace rsl