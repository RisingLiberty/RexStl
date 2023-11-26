// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: comb_sort.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/iter_swap.h"
#include "rex_std/internal/functional/less.h"
#include "rex_std/internal/iterator/advance.h"
#include "rex_std/internal/iterator/distance.h"
#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  inline namespace v1
  {
    // comb_sort
    //
    // This is an unstable sort.
    // Implements the CombSort algorithm; in particular, implements the CombSort11 variation
    // of the CombSort algorithm, based on the reference to '11' in the implementation.
    //
    // To consider: Use a comb sort table instead of the '((nSpace * 10) + 3) / 13' expression.
    //              Ideal tables can be found on the Internet by looking up "comb sort table".
    //
    template <typename ForwardIterator, typename StrictWeakOrdering>
    void comb_sort(ForwardIterator first, ForwardIterator last, StrictWeakOrdering compare)
    {
      typedef typename rsl::iterator_traits<ForwardIterator>::difference_type difference_type;

      ForwardIterator iCurrent, iNext;
      difference_type length = rsl::distance(first, last);
      difference_type nSpace = length;

      for(bool bSwapped = false; (nSpace > 1) || bSwapped;)
      {
        nSpace = ((nSpace * 10) + 3) / 13; // Integer division is less than ideal.

        if((nSpace == 9) || (nSpace == 10))
          nSpace = 11;

        iCurrent = iNext = first;
        rsl::advance(iNext, nSpace);

        for(bSwapped = false; iNext != last; iCurrent++, iNext++)
        {
          if(compare(*iNext, *iCurrent))
          {
            RSL_ASSERT_X(!compare(*iCurrent, *iNext), "invalid comparison function"); // Validate that the compare function is sane.
            rsl::iter_swap(iCurrent, iNext);
            bSwapped = true;
          }
        }
      }
    } // comb_sort

    template <typename ForwardIterator>
    inline void comb_sort(ForwardIterator first, ForwardIterator last)
    {
      typedef rsl::less<typename rsl::iterator_traits<ForwardIterator>::value_type> Less;

      rsl::comb_sort<ForwardIterator, Less>(first, last, Less());
    }
  } // namespace v1
} // namespace rsl
