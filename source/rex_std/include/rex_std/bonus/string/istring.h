// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash_result.h
// Copyright (c) Nick De Breuck 2025
//
// ============================================

#pragma once

#include "rex_std/bonus/string/char_traits_case_insensitive.h"
#include "rex_std/internal/string/basic_string.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename Allocator = rsl::allocator>
    using istring = basic_string<char8, ichar_traits<char8>, Allocator>;
    template <typename Allocator = rsl::allocator>
    using iwstring = basic_string<char8, ichar_traits<char8>, Allocator>;

    template <typename CharType, typename Alloc>
    struct hash<basic_string<CharType, ichar_traits<CharType>, Alloc>>
    {
      constexpr hash_result operator()(const basic_string<CharType, ichar_traits<CharType>, Alloc>& str) const
      {
        return rsl::internal::hash_as_lower(str.data(), str.length());
      }
    };
  } // namespace v1
} // namespace rsl
