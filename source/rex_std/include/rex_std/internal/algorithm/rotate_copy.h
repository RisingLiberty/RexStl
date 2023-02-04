// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: rotate_copy.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/copy.h"

namespace rsl
{
  inline namespace v1
  {

    template <class InputIterator, class OuputIterator>
    constexpr OuputIterator rotate_copy(InputIterator first, InputIterator firstN, InputIterator last, OuputIterator dstFirst)
    {
      dstFirst = rsl::copy(firstN, last, dstFirst);
      return rsl::copy(first, firstN, dstFirst);
    }

  } // namespace v1
} // namespace rsl
