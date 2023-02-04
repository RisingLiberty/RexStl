// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: remove_copy_if.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <class InputIterator, class OutputIterator, class Predicate>
    OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator dstFirst, Predicate p)
    {
      for(; first != last; ++first)
      {
        if(!p(*first))
        {
          *dstFirst++ = *first;
        }
      }
      return dstFirst;
    }

  } // namespace v1
} // namespace rsl
