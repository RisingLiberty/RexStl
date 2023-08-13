// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: reverse_search.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/functional/equal_to.h"
#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  inline namespace v1
  {
    template <class BiDirectionalIterator1, class BiDirectionalIterator2, class Predicate>
    constexpr BiDirectionalIterator1 reverse_search(BiDirectionalIterator1 first, BiDirectionalIterator1 last, BiDirectionalIterator2 firstToFind, BiDirectionalIterator2 lastToFind, Predicate p)
    {
      if(first == last || firstToFind == lastToFind)
      {
        return first;
      }

      // search from the back for first character matching the last character in the range to look for
      // from then on, continue search to see if an exact match is found
      BiDirectionalIterator1 it         = last - 1;
      BiDirectionalIterator2 to_find_it = lastToFind - 1;
      while(it != first - 1)
      {
        auto start         = it;
        auto to_find_start = to_find_it;
        while(p(*start, *to_find_start) && it != first - 1 && to_find_start != firstToFind - 1)
        {
          if(to_find_start == firstToFind)
          {
            return start;
          }

          --start;
          --to_find_start;
        }

        --it;
      }

      return last;
    }

    template <class BiDirectionalIterator1, class BiDirectionalIterator2>
    constexpr BiDirectionalIterator1 reverse_search(BiDirectionalIterator1 first, BiDirectionalIterator1 last, BiDirectionalIterator2 firstToFind, BiDirectionalIterator2 lastToFind)
    {
      return reverse_search(first, last, firstToFind, lastToFind, rsl::equal_to<typename rsl::iterator_traits<BiDirectionalIterator1>::value_type>());
    }
  } // namespace v1
} // namespace rsl
