// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: min.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

// based on https://en.cppreference.com/w/cpp/algorithm/min

#include "rex_std/internal/algorithm/min_element.h"
#include "rex_std/initializer_list.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    constexpr const T&(min)(const T& lhs, const T& rhs)
    {
      return lhs < rhs ? lhs : rhs;
    }
    template <typename T, typename Compare>
    constexpr const T&(min)(const T& lhs, const T& rhs, Compare comp)
    {
      return comp(lhs, rhs) ? lhs : rhs;
    }
    template <typename T>
    T(min)(rsl::initializer_list<T> ilist)
    {
      return *rsl::min_element(ilist.begin(), ilist.end());
    }
    template <typename T, typename Compare>
    T(min)(rsl::initializer_list<T> ilist, Compare compare)
    {
      return *rsl::min_element(ilist.begin(), ilist.end());
    }

  } // namespace v1
} // namespace rsl
