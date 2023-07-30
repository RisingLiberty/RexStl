// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: find_first_not_of.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/find.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename ForwardIt1, typename ForwardIt2>
    constexpr ForwardIt1 find_first_not_of(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
    {
      for (; first1 != last1; ++first1)
      {
        auto it = rsl::find(first2, last2, *first1);

        if (it == last2)
        {
          return first1;
        }
      }

      return last1;
    }

    template <typename ForwardIt1, typename ForwardIt2, typename Predicate>
    constexpr ForwardIt1 find_first_not_of(ForwardIt1 first1, ForwardIt2 last1, ForwardIt2 first2, ForwardIt2 last2, Predicate pred)
    {
      using value_type = rsl::iterator_traits<ForwardIt1>::value_type;

      for (; first1 != last1; ++first1)
      {
        auto it = rsl::find_if(first2, last2, [&](const value_type& val) { return pred(*first1, val); });

        if (it == last2)
        {
          return first1;
        }
      }

      return last1;
    }
  }
}
