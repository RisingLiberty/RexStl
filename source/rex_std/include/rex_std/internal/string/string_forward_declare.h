// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_forward_declare.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

namespace rsl
{
  inline namespace v1
  {

    template <typename CharType>
    class char_traits;

    template <typename CharType, typename Traits>
    class basic_string_view;

    using string_view  = basic_string_view<char8, char_traits<char8>>;
    using wstring_view = basic_string_view<tchar, char_traits<tchar>>;

    class allocator;
    template <typename CharType, typename Traits, typename Alloc>
    class basic_string;

    using string = basic_string<char8, char_traits<char8>, allocator>;

  } // namespace v1
} // namespace rsl
