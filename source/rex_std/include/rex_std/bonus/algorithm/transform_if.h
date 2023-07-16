// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: transform_if.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    template <typename InputIterator, typename OutputIterator, typename Func, typename BinaryPredicate>
    OutputIterator transform_if(InputIterator first, InputIterator last, OutputIterator dstFirst, Func func, BinaryPredicate pred)
    {
      auto it = first;
      while(it != last)
      {
        if(*it && pred(*it))
        {
          *dstFirst = func(*it);
          ++dstFirst;
        }
        ++it;
      }

      return dstFirst;
    }

    template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Func, typename BinaryPredicate>
    OutputIterator transform_if(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, Func func, BinaryPredicate pred)
    {
      for (; first1 != last1; ++first1, ++first2, ++result)
      {
        if (pred(*first1, *first2))
        {
          *result = func(*first1, *first2);
        }
      }

      return result;
    }

  } // namespace v1
} // namespace rsl
