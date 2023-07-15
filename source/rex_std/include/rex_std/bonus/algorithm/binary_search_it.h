// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: binary_search_it.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/lower_bound.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename ForwardIterator, typename T>
    ForwardIterator binary_search_it(ForwardIterator first, ForwardIterator last, const T& value)
    {
      // To do: This can be made slightly faster by not using lower_bound.
      ForwardIterator i(rsl::lower_bound<ForwardIterator, T>(first, last, value));
      if ((i != last) && !(value < *i)) // Note that we always express value comparisons in terms of < or ==.
      {
        return i;
      }
      return last;
    }

    template <typename ForwardIterator, typename T, typename Compare>
    ForwardIterator binary_search_it(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
    {
      // To do: This can be made slightly faster by not using lower_bound.
      ForwardIterator i(rsl::lower_bound<ForwardIterator, T, Compare>(first, last, value, compare));
      if ((i != last) && !compare(value, *i))
      {
        return i;
      }
      return last;
    }
  }
}
