// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: transform.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename InputIterator, typename OutputIterator, typename Func>
    void transform(InputIterator first, InputIterator last, OutputIterator dstFirst, Func func)
    {
      auto it = first;
      while(it != last)
      {
        *dstFirst = func(*it);
        ++it;
        ++dstFirst;
      }
    }

    template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Func>
    OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, Func func)
    {
      for(; first1 != last1; ++first1, ++first2, ++result)
      {
        *result = func(*first1, *first2);
      }

      return result;
    }

  } // namespace v1
} // namespace rsl
