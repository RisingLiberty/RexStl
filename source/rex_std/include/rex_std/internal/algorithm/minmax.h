// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: minmax.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/initializer_list.h"
#include "rex_std/internal/algorithm/minmax_element.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct min_max_result
    {
      const T& min; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
      const T& max; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    };

    template <typename T>
    min_max_result<T> minmax(const T& lhs, const T& rhs)
    {
      return lhs < rhs ? min_max_result<T> {lhs, rhs} : min_max_result<T> {rhs, lhs};
    }
    template <typename T, typename Compare>
    min_max_result<T> minmax(const T& lhs, const T& rhs, Compare compare)
    {
      return compare(lhs, rhs) ? min_max_result<T> {lhs, rhs} : min_max_result<T> {rhs, lhs};
    }

    template <typename T>
    min_max_result<T> minmax(rsl::initializer_list<T> ilist)
    {
      min_max_element_result<const T*> res = rsl::minmax_element(ilist.begin(), ilist.end());
      return min_max_result<T> {*res.min, *res.max};
    }
    template <typename T, typename Compare>
    min_max_result<T> minmax(rsl::initializer_list<T> ilist, Compare compare)
    {
      min_max_element_result<const T*> res = rsl::minmax_element(ilist.begin(), ilist.end(), compare);
      return min_max_result<T> {*res.min, *res.max};
    }

  } // namespace v1
} // namespace rsl
