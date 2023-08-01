// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: find_first_of.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    template <typename ForwardIt1, typename ForwardIt2>
    ForwardIt1 find_first_of(ForwardIt1 first1, ForwardIt2 last1, ForwardIt2 first2, ForwardIt2 last2)
    {
      for(; first1 != last1; ++first1)
      {
        for(ForwardIt2 i = first2; i != last2; ++i)
        {
          if(*first1 == *i)
          {
            return first1;
          }
        }
      }

      return last1;
    }

    template <typename ForwardIt1, typename ForwardIt2, typename Predicate>
    ForwardIt1 find_first_of(ForwardIt1 first1, ForwardIt2 last1, ForwardIt2 first2, ForwardIt2 last2, Predicate pred)
    {
      for(; first1 != last1; ++first1)
      {
        for(ForwardIt2 i = first2; i != last2; ++i)
        {
          if(pred(*first1, *i))
          {
            return first1;
          }
        }
      }

      return last1;
    }

  } // namespace v1
} // namespace rsl
