// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: move.h
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
    OutputIterator move(InputIterator first, InputIterator last, OutputIterator dstFirst)
    {
      auto src = first;
      auto dst = dstFirst;
      while(src != last)
      {
        *dst = rsl::move(*src);
        ++src;
        ++dst;
      }

      return dst;
    }

  } // namespace v1
} // namespace rsl
