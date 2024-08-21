// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: partition.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/find_if_not.h"
#include "rex_std/internal/algorithm/iter_swap.h"
#include "rex_std/internal/iterator/next.h"

namespace rsl
{
	inline namespace v1
	{

    template<class ForwardIt, class UnaryPredicate>
    ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
    {
      first = rsl::find_if_not(first, last, p);
      if (first == last)
      {
        return first;
      }

      for (ForwardIt i = rsl::next(first); i != last; ++i) 
      {
        if (p(*i)) 
        {
          rsl::iter_swap(i, first);
          ++first;
        }
      }
      
      return first;
    }
	} // namespace v1
} // namespace rsl
