// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: character_lookup.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/array/array.h"
#include "rex_std/internal/iterator/random_access_iterator.h"
#include "rex_std/internal/iterator/reverse_iterator.h"
#include "rex_std/internal/type_traits/make_unsigned.h"
#include "rex_std/limits.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Traits>
    class character_lookup
    {
    public:
      using traits_type            = Traits;
      using value_type             = typename Traits::char_type;
      using pointer                = value_type*;
      using const_pointer          = const value_type*;
      using reference              = value_type&;
      using const_reference        = const value_type&;
      using const_iterator         = const_random_access_iterator<value_type>;
      using iterator               = const_iterator;
      using const_reverse_iterator = reverse_iterator<const_iterator>;
      using reverse_iteartor       = const_reverse_iterator;
      using size_type              = count_t;
      using difference_type        = int32;

      constexpr character_lookup(const_pointer str, size_type length)
          : m_table()
      {
        for(size_type i = 0; i < length; ++i)
        {
          auto c = traits_type::to_int_type(str[i]);
          m_table[c]         = true;
        }
      }

      bool exists(value_type c) const
      {
        auto idx = traits_type::to_int_type(c);
        return m_table[idx];
      }

    private:
      rsl::array<bool, (numeric_limits<rsl::make_unsigned_t<value_type>>::max)() + 1> m_table {}; // NOLINT
    };

  } // namespace v1
} // namespace rsl
