// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: prev.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/advance.h"
#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename InputIterator>
    InputIterator next(InputIterator it, typename rsl::iterator_traits<InputIterator>::difference_type n = 1)
    {
      rsl::advance(it, n);
      return it;
    }
  } // namespace v1
} // namespace rsl
