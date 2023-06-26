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
    template <typename InputIterator, typename OutputIterator, typename Func, typename Predicate>
    OutputIterator transform(InputIterator first, InputIterator last, OutputIterator dstFirst, Func func, Predicate predicate)
    {
      auto it = first;
      while(it != last)
      {
        if(*it)
        {
          *dstFirst = func(*it);
          ++dstFirst;
        }
        ++it;
      }

      return dstFirst;
    }

  } // namespace v1
} // namespace rsl
