// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/c_string.h"
#include "rex_std/bonus/string/character_lookup.h"
#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/string/string_fwd.h"
#include "rex_std/bonus/string/string_utils.h"
#include "rex_std/bonus/string/string_utils_impl.h"
#include "rex_std/internal/algorithm/count.h"
#include "rex_std/string.h"
#include "rex_std/string_view.h"
#include "rex_std/vector.h"

namespace rsl
{
	inline namespace v1
	{
		namespace internal
		{
			// Splits the string input into different parts using the deliminators
			template <typename AllocatorType, typename CharType, typename Traits>
			rsl::vector<rsl::basic_string_view<CharType, Traits>, AllocatorType> split(rsl::basic_string_view<CharType, Traits> str, rsl::basic_string_view<CharType, Traits> deliminators)
			{
				using string_view_type = rsl::basic_string_view<CharType, Traits>;

				rsl::vector<string_view_type, AllocatorType> result;

				// Quick memory optimization to avoid reallocation later on
				// Always starts with 1 as in worst case we need to copy the entire string
				card32 delim_in_str = 1;
				for (CharType c : deliminators)
				{
					delim_in_str += rsl::count(str.cbegin(), str.end(), c);
				}
				result.reserve(delim_in_str);

				card32 start = 0;
				for (card32 i = 0; i < str.size(); ++i)
				{
					const CharType c = str[i];
					for (const CharType d : deliminators)
					{
						if (c == d)
						{
							const string_view_type sub_str = str.substr(start, i - start);
							if (!sub_str.empty())
							{
								result.push_back(str.substr(start, i - start));
							}
							start = i + 1;
						}
					}
				}

				if (start != str.size())
				{
					result.push_back(str.substr(start));
				}

				return result;
			}
		}

		// Splits the string input into different parts using the deliminators
		template <typename AllocatorType = rsl::allocator>
		rsl::vector<rsl::string_view, AllocatorType> split(rsl::string_view str, rsl::string_view deliminators)
		{
			return internal::split<AllocatorType>(str, deliminators);
		}
		// Splits the string input into different parts using the deliminators
		template <typename AllocatorType = rsl::allocator>
		rsl::vector<rsl::wstring_view, AllocatorType> split(rsl::wstring_view str, rsl::wstring_view deliminators)
		{
			return internal::split<AllocatorType>(str, deliminators);
		}
	} // namespace v1
} // namespace rsl