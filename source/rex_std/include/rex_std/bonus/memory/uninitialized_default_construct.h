// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: uninitialized_default_construct.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/iterator.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    void uninitialized_default_construct(T* ptr)
    {
      new(ptr) T();
    }

    template <typename Iterator>
    void uninitialized_default_construct(Iterator* begin, Iterator* end)
    {
      value_type = iterator_traits<Iterator>::value_type;

      for (auto it = begin; it != end; ++it)
      {
        new (iterator_to_pointer(it)) value_type();
      }
    }

  } // namespace v1
} // namespace rsl
