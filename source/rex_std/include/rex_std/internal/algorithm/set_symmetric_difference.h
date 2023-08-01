// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: set_symmetric_difference.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/array.h"
#include "rex_std/internal/algorithm/copy.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
    OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
    {
      while((first1 != last1) && (first2 != last2))
      {
        if(*first1 < *first2)
        {
          *result = *first1;
          ++first1;
          ++result;
        }
        else if(*first2 < *first1)
        {
          *result = *first2;
          ++first2;
          ++result;
        }
        else
        {
          ++first1;
          ++first2;
        }
      }

      return rsl::copy(first2, last2, rsl::copy(first1, last1, result));
    }

    template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
    OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare)
    {
      while((first1 != last1) && (first2 != last2))
      {
        if(compare(*first1, *first2))
        {
          RSL_ASSERT_X(!compare(*first2, *first1), "invalid comparison function");
          *result = *first1;
          ++first1;
          ++result;
        }
        else if(compare(*first2, *first1))
        {
          RSL_ASSERT_X(!compare(*first1, *first2), "invalid comparison function");
          *result = *first2;
          ++first2;
          ++result;
        }
        else
        {
          ++first1;
          ++first2;
        }
      }

      return rsl::copy(first2, last2, rsl::copy(first1, last1, result));
    }

  } // namespace v1
} // namespace rsl
