// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: copy_n.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/copy.h"
#include "rex_std/internal/iterator/iterator_tags.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename InputIterator, typename Size, typename OutputIterator>
  OutputIterator copy_n_impl(InputIterator first, Size n, OutputIterator result, rsl::input_iterator_tag)
  {
    for(; n > 0; --n)
      *result++ = *first++;
    return result;
  }

  template <typename random_access_iterator, typename Size, typename OutputIterator>
  OutputIterator copy_n_impl(random_access_iterator first, Size n, OutputIterator result, rsl::random_access_iterator_tag)
  {
    return rsl::copy(first, first + n, result); // Take advantage of the optimizations present in the copy algorithm.
  }
} // namespace internal

template <typename InputIterator, typename Size, typename OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator dst_first)
{
  using IC = typename InputIterator::iterator_category;
  return internal::copy_n_impl(first, n, dst_first, IC());
}

REX_RSL_END_NAMESPACE
