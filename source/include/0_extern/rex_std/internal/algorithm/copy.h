// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: copy.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/types.h"

#include "rex_std/internal/iterator/iterator_tags.h"

#include "rex_std/internal/utility/move.h"

#include "rex_std/bonus/type_traits/is_move_iterator.h"
#include "rex_std/internal/type_traits/is_same.h"
#include "rex_std/internal/type_traits/is_trivially_copyable.h"
#include "rex_std/internal/type_traits/is_pointer.h"

#include "rex_std/internal/memory/memmove.h"

namespace rsl
{
	namespace internal
	{
		template <typename InputIteratorCategory, bool IsMove, bool CanMemMove>
		struct MoveAndCopyHelper
		{
			template <typename InputIterator, typename OutputIterator>
			static OutputIterator move_or_copy(InputIterator first, InputIterator last, OutputIterator dst_first)
			{
				for (; first != last; ++dst_first, ++first)
				{
					*dst_first = *first;
				}

				return dst_first;
			}
		};

		template <>
		struct MoveAndCopyHelper<rsl::random_access_iterator_tag, false, false>
		{
			template <typename InputIterator, typename OutputIterator>
			static OutputIterator move_or_copy(InputIterator first, InputIterator last, OutputIterator result)
			{
				using difference_type = InputIterator::difference_type;

				for (difference_type n = (last - first); n > 0; --n, ++first, ++result)
				{
					*result = *first;
				}

				return result;
			}
		};

		template <typename InputIteratorCategory>
		struct MoveAndCopyHelper<InputIteratorCategory, true, false>
		{
			template <typename InputIterator, typename OutputIterator>
			static OutputIterator move_or_copy(InputIterator first, InputIterator last, OutputIterator result)
			{
				for (; first != last; ++result, ++first)
				{
					*result = rsl::move(*first);
				}
				return result;
			}
		};

		template <>
		struct MoveAndCopyHelper<rsl::random_access_iterator_tag, true, false>
		{
			template <typename InputIterator, typename OutputIterator>
			static OutputIterator move_or_copy(InputIterator first, InputIterator last, OutputIterator result)
			{
				using difference_type = InputIterator::difference_type;

				for (difference_type n = (last - first); n > 0; --n, ++first, ++result)
				{
					*result = rsl::move(*first);
				}

				return result;
			}
		};

		template <bool IsMove>
		struct MoveAndCopyHelper<rsl::random_access_iterator_tag, IsMove, true>
		{
			template <typename T>
			static T* move_or_copy(const T* first, const T* last, T* result)
			{
				if (first == last)
					return result;

				// We could use memcpy here if there's no range overlap, but memcpy is rarely much faster than memmove.
				size_t len = (size_t)((uintptr)last - (uintptr)first);
				return static_cast<T*>(rsl::memmove(result, first, len) + (last - first));
			}
		};
	}

	template <typename InputIterator, typename OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dst_first)
	{
		using IIC = typename InputIterator::iterator_category;
		using OIC = typename OutputIterator::iterator_category;
        using value_type_input  = typename InputIterator::value_type;
		using value_type_output = typename OutputIterator::value_type;

		constexpr bool IsMove = rsl::is_move_iterator_v<InputIterator>;
		constexpr bool CanBeMemmoved = rsl::is_trivially_copyable_v<value_type_output>::value &&
			rsl::is_same_v<value_type_input, value_type_output> &&
			(rsl::is_pointer_v<InputIterator> || rsl::is_same_v<IIC, rsl::continuous_iterator_tag>) &&
			(rsl::is_pointer_v<OutputIterator> || rsl::is_same_v<OIC, rsl::continuous_iterator_tag>);

		internal::MoveAndCopyHelper<IIC, IsMove, CanBeMemmoved>::move_or_copy(first, last, dst_first);
	}
}
