// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: reverse_copy.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_tags.h"
#include "rex_std/internal/type_traits/is_base_of.h"

namespace rsl
{
  inline namespace v1
  {

    template <class InputIterator, class OutputIterator>
    constexpr OutputIterator reverse_copy(InputIterator first, InputIterator last, OutputIterator dstFirst)
    {
      while(first != last)
      {
        *(dstFirst++) = *(--last);
      }

      return dstFirst;
    }

  } // namespace v1
} // namespace rsl
