#pragma once

// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_literal.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================


#include "rex_std/bonus/types.h"
#include "rex_std/bonus/type_traits/is_character.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename Char>
    class string_literal
    {
    public:
      static_assert(rsl::is_character_v<Char>, "Char must be a character type");

      template <count_t N>
      constexpr string_literal(const Char(&arr)[N])
        : m_data(arr)
        , m_length(N - 1)
      {}

      constexpr const Char* data() const
      {
        return m_data;
      }
      constexpr count_t size() const
      {
        return m_length;
      }
      constexpr count_t length() const
      {
        return m_length;
      }

    private:
      const Char* m_data;
      count_t m_length;
    };
  }
}