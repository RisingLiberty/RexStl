// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: move_backward.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/utility/move.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename InputIterator, typename OutputIterator>
    OutputIterator move_backward(InputIterator first, InputIterator last, OutputIterator dstLast)
    {
      while(first != last)
      {
        *--dstLast = rsl::move(*--last);
      }

      // dstLast now points to the beginning of the destination sequence instead of the end.
      return dstLast;
    }

  } // namespace v1
} // namespace rsl
