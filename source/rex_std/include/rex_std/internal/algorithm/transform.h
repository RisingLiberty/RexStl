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

  } // namespace v1
} // namespace rsl
