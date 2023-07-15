// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: string_fwd.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    class allocator;

    template <typename CharT>
    class char_traits;

    template <typename CharType, typename Traits, typename Alloc>
    class basic_string;

    using string = basic_string<char8, char_traits<char8>, allocator>;
    using wstring = basic_string<tchar, char_traits<tchar>, allocator>;
    using u16string = basic_string<char16_t, char_traits<char16_t>, allocator>;
    using u32string = basic_string<char32_t, char_traits<char32_t>, allocator>;
  }
}
