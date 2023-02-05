// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/limits.h"

namespace rsl
{
  inline namespace v1
  {

    constexpr card64 hash_combine(card64 seed, card64 hash)
    {
      hash += 0X9E3779B9 + (seed << 6) + (seed >> 2); // NOLINT(hicpp-signed-bitwise)
      return seed ^ hash;                             // NOLINT(hicpp-signed-bitwise)
    }

#pragma warning(push)
#pragma warning(disable : 4307)
    constexpr card32 hash(const char8* key)
    {
      const card32 p       = 31;
      const card32 m       = static_cast<card32>(1e9 + 9);
      long long hash_value = 0;
      long long p_pow      = 1;
      const char8* c       = key;
      while(*c != '\0')
      {
        hash_value = (hash_value + (*c - static_cast<card32>('a') + 1) * p_pow) % m;
        p_pow      = (p_pow * p) % m;
        c++;
      }

      return static_cast<card32>(hash_value);
    }
#pragma warning(pop)

    class hash_val
    {
    public:
      using type = card64;

      constexpr explicit hash_val(card64 hash)
          : m_value(hash)
      {
      }

      constexpr type value() const
      {
        return m_value;
      }
      constexpr bool operator==(hash_val rhs) const
      {
        return m_value == rhs.m_value;
      }
      constexpr bool operator!=(hash_val rhs) const
      {
        return m_value != rhs.m_value;
      }

      static constexpr hash_val invalid()
      {
        return hash_val(rsl::numeric_limits<card64>::max());
      }

      static hash_val new_hash();

    private:
      type m_value;
    };

  } // namespace v1
} // namespace rsl