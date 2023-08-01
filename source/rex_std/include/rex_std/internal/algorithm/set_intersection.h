// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: set_intersection.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/assert.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
    OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
    {
      while((first1 != last1) && (first2 != last2))
      {
        if(*first1 < *first2)
          ++first1;
        else if(*first2 < *first1)
          ++first2;
        else
        {
          *result = *first1;
          ++first1;
          ++first2;
          ++result;
        }
      }

      return result;
    }

    template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
    OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare)
    {
      while((first1 != last1) && (first2 != last2))
      {
        if(compare(*first1, *first2))
        {
          RSL_ASSERT_X(!compare(*first2, *first1), "invalid comparison function");
          ++first1;
        }
        else if(compare(*first2, *first1))
        {
          RSL_ASSERT_X(!compare(*first1, *first2), "invalid comparison function");
          ++first2;
        }
        else
        {
          *result = *first1;
          ++first1;
          ++first2;
          ++result;
        }
      }

      return result;
    }
  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"