// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: range.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/initializer_list.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct range
    {
      using value_type = const T;

      const T* first;
      const T* last;

      template <typename InputIt>
      range(InputIt firstIt, InputIt lastIt)
      {
        first = firstIt;
        last = lastIt;
      }

      bool empty() const
      {
        return first == last;
      }

      card32 size() const
      {
        return static_cast<card32>(last - first);
      }

      const value_type& front() const
      {
        return *first;
      }
      value_type& back() const
      {
        return *(last - 1);
      }

      value_type& operator[](card32 idx) const
      {
        return first[idx];
      }
    };

    template <typename T>
    range(T...)->range<T>;

  } // namespace v1
} // namespace rsl
