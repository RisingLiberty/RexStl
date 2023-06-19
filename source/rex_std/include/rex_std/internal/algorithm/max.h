// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: max.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

// based on https://en.cppreference.com/w/cpp/algorithm/max

#include "rex_std/internal/algorithm/max_element.h"
#include "rex_std/initializer_list.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    constexpr const T&(max)(const T& lhs, const T& rhs)
    {
      return lhs < rhs ? rhs : lhs;
    }
    template <typename T, typename Compare>
    constexpr const T&(max)(const T& lhs, const T& rhs, Compare comp)
    {
      return comp(lhs, rhs) ? rhs : lhs;
    }
    template <typename T>
    T (max)(rsl::initializer_list<T> ilist)
    {
      return *rsl::max_element(ilist.begin(), ilist.end());
    }
    template <typename T, typename Compare>
    T(max)(rsl::initializer_list<T> ilist, Compare compare)
    {
      return *rsl::max_element(ilist.begin(), ilist.end());
    }

  } // namespace v1
} // namespace rsl
