// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: memory_size.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {

    constexpr card64 KiloByteMultiple = 1000;
    constexpr card64 MegaByteMultiple = KiloByteMultiple * 1000;
    constexpr card64 GigaByteMultiple = MegaByteMultiple * 1000;

    constexpr card64 KibiByteMultiple = 1024;
    constexpr card64 MibiByteMultiple = KibiByteMultiple * 1024;
    constexpr card64 GibiByteMultiple = MibiByteMultiple * 1024;

    class memory_size
    {
    public:
      constexpr memory_size()
        : m_size_in_bytes(0)
      {
      }
      constexpr explicit memory_size(card64 sizeInBytes)
        : m_size_in_bytes(sizeInBytes)
      {}

      constexpr operator card64() const
      {
        return size_in_bytes();
      }
      constexpr card64 size_in_bytes() const
      {
        return m_size_in_bytes;
      }

      constexpr memory_size operator+(card64 bytes) const
      {
        card64 res = m_size_in_bytes + bytes;
        return memory_size(res);
      }
      constexpr memory_size& operator+=(card64 bytes)
      {
        m_size_in_bytes += bytes;
        return *this;
      }

      constexpr memory_size operator-(card64 bytes) const
      {
        card64 res = m_size_in_bytes - bytes;
        return memory_size(res);
      }
      constexpr memory_size operator-=(card64 bytes)
      {
        m_size_in_bytes -= bytes;
        return *this;
      }

      constexpr card64 size_in_kb() const
      {
        return size_in_bytes() / KiloByteMultiple;
      }
      constexpr card64 size_in_mb() const
      {
        return size_in_bytes() / MegaByteMultiple;
      }
      constexpr card64 size_in_gb() const
      {
        return size_in_bytes() / GigaByteMultiple;
      }
      constexpr card64 size_in_kib() const
      {
        return size_in_bytes() / KibiByteMultiple;
      }
      constexpr card64 size_in_mib() const
      {
        return size_in_bytes() / MibiByteMultiple;
      }
      constexpr card64 size_in_gib() const
      {
        return size_in_bytes() / GibiByteMultiple;
      }

      static constexpr memory_size from_bytes(card64 bytes)
      {
        return memory_size(bytes);
      }
      static constexpr memory_size from_kb(card64 kb)
      {
        card64 size = static_cast<card64>(kb * rsl::KiloByteMultiple);
        return memory_size(size);
      }
      static constexpr memory_size from_mb(card64 mb)
      {
        card64 size = static_cast<card64>(mb * rsl::MegaByteMultiple);
        return memory_size(size);
      }
      static constexpr memory_size from_gb(card64 gb)
      {
        card64 size = static_cast<card64>(gb * rsl::GigaByteMultiple);
        return memory_size(size);
      }

      static constexpr memory_size from_kib(card64 kib)
      {
        card64 size = static_cast<card64>(kib * rsl::KibiByteMultiple);
        return memory_size(size);
      }
      static constexpr memory_size from_mib(card64 mib)
      {
        card64 size = static_cast<card64>(mib * rsl::MibiByteMultiple);
        return memory_size(size);
      }
      static constexpr memory_size from_gib(card64 gib)
      {
        card64 size = static_cast<card64>(gib * rsl::GibiByteMultiple);
        return memory_size(size);
      }

    private:
      card64 m_size_in_bytes;
    };

  } // namespace v1
} // namespace rsl

constexpr rsl::memory_size operator"" _bytes(unsigned long long bytes)
{
  return rsl::memory_size::from_bytes(bytes);
}
constexpr rsl::memory_size operator"" _kb(unsigned long long bytes)
{
  return rsl::memory_size::from_kb(bytes);
}
constexpr rsl::memory_size operator"" _mb(unsigned long long bytes)
{
  return rsl::memory_size::from_mb(bytes);
}
constexpr rsl::memory_size operator"" _gb(unsigned long long bytes)
{
  return rsl::memory_size::from_gb(bytes);
}

constexpr rsl::memory_size operator"" _kib(unsigned long long bytes)
{
  return rsl::memory_size::from_kib(bytes);
}
constexpr rsl::memory_size operator"" _mib(unsigned long long bytes)
{
  return rsl::memory_size::from_mib(bytes);
}
constexpr rsl::memory_size operator"" _gib(unsigned long long bytes)
{
  return rsl::memory_size::from_gib(bytes);
}