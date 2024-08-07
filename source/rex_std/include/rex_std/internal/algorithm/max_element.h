// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: max_element.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename InputIterator>
    InputIterator max_element(InputIterator first, InputIterator last)
    {
      auto largest = first++;
      auto it = first;
      while (it != last)
      {
        if (*largest < *it)
        {
          largest = it;
        }
        ++it;
      }

      return largest;
    }

    template <typename InputIterator, typename Compare>
    InputIterator max_element(InputIterator first, InputIterator last, Compare comp)
    {
      auto largest = first++;
      auto it = first;
      while (it != last)
      {
        // the comparison should return true if lhs is less than rhs
        if (comp(*largest, *it))
        {
          largest = it;
        }
        ++it;
      }

      return largest;
    }

  } // namespace v1
} // namespace rsl
