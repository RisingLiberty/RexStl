// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: integer_sequence.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/type_traits/is_integral.h"

namespace rsl
{
  inline namespace v1
  {
    // sequence of integer parameters
    template <typename T, T... Vals>
    struct integer_sequence 
    {
      static_assert(is_integral_v<T>, "integer_sequence<T, I...> requires T to be an integral type.");

      using value_type = T;

      REX_NO_DISCARD static constexpr card32 size() noexcept 
      {
        return sizeof...(Vals);
      }
    };

    template <typename T, T Size>
    using make_integer_sequence = __make_integer_seq<integer_sequence, T, Size>;

    template <card32... Vals>
    using index_sequence = integer_sequence<card32, Vals...>;

    template <card32 Size>
    using make_index_sequence = make_integer_sequence<card32, Size>;

    template <typename... Types>
    using index_sequence_for = make_index_sequence<sizeof...(Types)>;

  } // namespace v1
} // namespace rsl
