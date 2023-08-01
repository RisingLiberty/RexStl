// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: equal_range.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    template <typename InputIterator1, typename InputIterator2>
    bool equal_range(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
      while((first1 != last1) && (first2 != last2) && (*first1 == *first2))
      {
        ++first1;
        ++first2;
      }
      return (first1 == last1) && (first2 == last2);
    }

    template <typename InputIterator1, typename InputIterator2, typename Predicate>
    bool equal_range(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Predicate predicate)
    {
      while((first1 != last1) && (first2 != last2) && predicate(*first1, *first2))
      {
        ++first1;
        ++first2;
      }
      return (first1 == last1) && (first2 == last2);
    }

  } // namespace v1
} // namespace rsl
