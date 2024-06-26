// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: copy_backward.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/type_traits/is_move_iterator.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/iterator/iterator_tags.h"
#include "rex_std/internal/type_traits/is_pointer.h"
#include "rex_std/internal/type_traits/is_same.h"
#include "rex_std/internal/type_traits/is_trivially_copyable.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      // Implementation moving copying both trivial and non-trivial data via a lesser iterator than random-access.
      template <typename /*BidirectionalIterator1Category*/, bool /*isMove*/, bool /*canMemmove*/>
      struct move_and_copy_backward_helper
      {
        template <typename InputIterator, typename OutputIterator>
        static OutputIterator move_or_copy_backward(InputIterator first, InputIterator last, OutputIterator dstLast)
        {
          while(first != last)
            *--dstLast = *--last;
          return dstLast; // dstLast now points to the beginning of the destination sequence instead of the end.
        }
      };

      // Specialization for moving non-trivial data via a lesser iterator than random-access.
      template <typename BidirectionalIterator1Category>
      struct move_and_copy_backward_helper<BidirectionalIterator1Category, true, false>
      {
        template <typename InputIterator, typename OutputIterator>
        static OutputIterator move_or_copy_backward(InputIterator first, InputIterator last, OutputIterator dstLast)
        {
          while(first != last)
          {
            *--dstLast = rsl::move(*--last);
          }
          return dstLast; // dstLast now points to the beginning of the destination sequence instead of the end.
        }
      };

      // Specialization for moving non-trivial data via a random-access iterator. It's theoretically faster because the compiler can see the count when its a compile-time const.
      template <>
      struct move_and_copy_backward_helper<rsl::random_access_iterator_tag, true, false>
      {
        template <typename InputIterator, typename OutputIterator>
        static OutputIterator move_or_copy_backward(InputIterator first, InputIterator last, OutputIterator dstLast)
        {
          using difference_type = typename iterator_traits<InputIterator>::difference_type;

          for(difference_type n = (last - first); n > 0; --n)
            *--dstLast = rsl::move(*--last);
          return dstLast; // dstLast now points to the beginning of the destination sequence instead of the end.
        }
      };

      // Specialization for copying non-trivial data via a random-access iterator. It's theoretically faster because the compiler can see the count when its a compile-time const.
      // This specialization converts the random access InputIterator last-first to an integral type. There's simple way for us to take advantage of a random access output iterator,
      // as the range is specified by the input instead of the output, and distance(first, last) for a non-random-access iterator is potentially slow.
      template <>
      struct move_and_copy_backward_helper<rsl::random_access_iterator_tag, false, false>
      {
        template <typename InputIterator, typename OutputIterator>
        static OutputIterator move_or_copy_backward(InputIterator first, InputIterator last, OutputIterator dstLast)
        {
          using difference_type = typename iterator_traits<InputIterator>::difference_type;

          for(difference_type n = (last - first); n > 0; --n)
            *--dstLast = *--last;
          return dstLast; // dstLast now points to the beginning of the destination sequence instead of the end.
        }
      };

      // Specialization for when we can use memmove/memcpy. See the notes above for what conditions allow this.
      template <bool IsMove>
      struct move_and_copy_backward_helper<rsl::random_access_iterator_tag, IsMove, true>
      {
        template <typename T>
        static T* move_or_copy_backward(const T* first, const T* last, T* dstLast)
        {
          size_t len = (size_t)((uintptr)last - (uintptr)first);
          return static_cast<T*>(memmove(dstLast - (last - first), first, len));
          // We could use memcpy here if there's no range overlap, but memcpy is rarely much faster than memmove.
        }
      };
    } // namespace internal

    template <typename InputIterator, typename OutputIterator>
    OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator dstFirst)
    {
      using IIC               = typename iterator_traits<InputIterator>::iterator_category;
      using OIC               = typename iterator_traits<OutputIterator>::iterator_category;
      using value_type_input  = typename iterator_traits<InputIterator>::value_type;
      using value_type_output = typename iterator_traits<OutputIterator>::value_type;

      RSL_MAYBE_UNUSED static constexpr bool IsMove        = rsl::is_move_iterator_v<InputIterator>;
      RSL_MAYBE_UNUSED static constexpr bool CanBeMemmoved = rsl::is_trivially_copyable_v<value_type_output> && rsl::is_same_v<value_type_input, value_type_output> &&
                                                        (rsl::is_pointer_v<InputIterator> || rsl::is_same_v<IIC, rsl::continuous_iterator_tag>)&&(rsl::is_pointer_v<OutputIterator> || rsl::is_same_v<OIC, rsl::continuous_iterator_tag>);

      return internal::move_and_copy_backward_helper<InputIterator, IsMove, CanBeMemmoved>::move_or_copy_backward(first, last, dstFirst);
    }

  } // namespace v1
} // namespace rsl
