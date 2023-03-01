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