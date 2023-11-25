// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: median.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/functional/less.h"
#include "rex_std/internal/utility/forward.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    inline T&& median_impl(T&& a, T&& b, T&& c)
    {
      if(rsl::less<T>()(a, b))
      {
        if(rsl::less<T>()(b, c))
          return rsl::forward<T>(b);
        else if(rsl::less<T>()(a, c))
          return rsl::forward<T>(c);
        else
          return rsl::forward<T>(a);
      }
      else if(rsl::less<T>()(a, c))
        return rsl::forward<T>(a);
      else if(rsl::less<T>()(b, c))
        return rsl::forward<T>(c);
      return rsl::forward<T>(b);
    }

    template <typename T>
    inline const T& median(const T& a, const T& b, const T& c)
    {
      return median_impl(a, b, c);
    }

    template <typename T>
    inline T&& median(T&& a, T&& b, T&& c)
    {
      return rsl::forward<T>(median_impl(rsl::forward<T>(a), rsl::forward<T>(b), rsl::forward<T>(c)));
    }

    template <typename T, typename Compare>
    inline T&& median_impl(T&& a, T&& b, T&& c, Compare compare)
    {
      if(compare(a, b))
      {
        if(compare(b, c))
          return rsl::forward<T>(b);
        else if(compare(a, c))
          return rsl::forward<T>(c);
        else
          return rsl::forward<T>(a);
      }
      else if(compare(a, c))
        return rsl::forward<T>(a);
      else if(compare(b, c))
        return rsl::forward<T>(c);
      return rsl::forward<T>(b);
    }

    template <typename T, typename Compare>
    inline const T& median(const T& a, const T& b, const T& c, Compare compare)
    {
      return median_impl<const T&, Compare>(a, b, c, compare);
    }

    template <typename T, typename Compare>
    inline T&& median(T&& a, T&& b, T&& c, Compare compare)
    {
      return rsl::forward<T>(median_impl<T&&, Compare>(rsl::forward<T>(a), rsl::forward<T>(b), rsl::forward<T>(c), compare));
    }
  } // namespace v1
} // namespace rsl
