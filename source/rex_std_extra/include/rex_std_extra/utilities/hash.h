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
      hash += 0X9E3779B9 + (seed << 6) + (seed >> 2);
      return seed ^ hash;
    }

#pragma warning(push)
#pragma warning(disable : 4307)
    constexpr card32 hash(const char8* key)
    {
      const card32 p       = 31;
      const card32 m       = (card32)1e9 + 9;
      long long hash_value = 0;
      long long p_pow      = 1;
      const char8* c       = key;
      while(*c)
      {
        hash_value = (hash_value + (*c - (card32)'a' + 1) * p_pow) % m;
        p_pow      = (p_pow * p) % m;
        c++;
      }

      return (card32)hash_value;
    }
#pragma warning(pop)

    class Hash
    {
    public:
      using type = card64;

      constexpr Hash(card64 hash)
          : m_value(hash)
      {
      }

      constexpr type value() const
      {
        return m_value;
      }
      constexpr bool operator==(Hash rhs) const
      {
        return m_value == rhs.m_value;
      }
      constexpr bool operator!=(Hash rhs) const
      {
        return m_value != rhs.m_value;
      }

      static constexpr Hash invalid()
      {
        return Hash(rsl::numeric_limits<card64>::max());
      }

      static Hash new_hash();

    private:
      type m_value;
    };

  } // namespace v1
} // namespace rsl