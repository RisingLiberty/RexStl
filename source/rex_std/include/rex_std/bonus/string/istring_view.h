// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_string_view.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/char_traits_case_insensitive.h"
#include "rex_std/internal/string_view/basic_string_view.h"

namespace rsl
{
	inline namespace v1
	{
		using istring_view = basic_string_view<char8, ichar_traits<char8>>;
		using iwstring_view = basic_string_view<tchar, ichar_traits<char8>>;

    template <typename CharType>
    struct hash<basic_string_view<CharType, ichar_traits<CharType>>>
    {
      constexpr hash_result operator()(const basic_string_view<CharType, ichar_traits<CharType>>& str) const
      {
        return rsl::internal::hash_as_lower(str.data(), str.length());
      }
    };

    namespace crc32
    {
      constexpr uint32 compute(rsl::istring_view view, uint32 crc = 0)
      {
        return crc32::compute_as_lower(view.data(), view.length(), crc);
      }
    }
	}
}