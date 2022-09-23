// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_forward_declare.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

REX_RSL_BEGIN_NAMESPACE

template <typename CharType>
class char_traits;

template <typename CharType, typename Traits>
class basic_string_view;

using string_view = basic_string_view<char8, char_traits<char8>>;

class allocator;
template <typename CharType, typename Traits, typename Allocator>
class basic_string;

using string = basic_string<char8, char_traits<char8>, allocator>;

REX_RSL_END_NAMESPACE
