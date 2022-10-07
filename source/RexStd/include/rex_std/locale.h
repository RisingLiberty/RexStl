// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: locale.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/iterator.h"
#include "rex_std/std_alias_defines.h"

#include <locale>

namespace rsl
{
  inline namespace v1
  {

    REX_STD_CLASS_ALIAS(locale);

    class allocator;

    // Deprecated in C++17
    // template <typename Codecvt, typename Elem = tchar, typename Wide_alloc = allocator, typename Byte_alloc = allocator>
    // REX_STD_TEMPLATED_CLASS_ALIAS(wstring_convert, Codecvt, Elem, Wide_alloc, Byte_alloc);

    template <typename T>
    class char_traits;

    // Deprecated in C++17
    // template <typename Codecvt, typename Elem = tchar, typename Tr = char_traits<tchar>>
    // REX_STD_TEMPLATED_CLASS_ALIAS(wbuffer_convert, Codecvt, Elem, Tr);

    REX_STD_CLASS_ALIAS(ctype_base);
    REX_STD_CLASS_ALIAS(codecvt_base);
    REX_STD_CLASS_ALIAS(messages_base);
    REX_STD_CLASS_ALIAS(time_base);
    REX_STD_CLASS_ALIAS(money_base);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(ctype, CharT);

    template <typename InternT, typename ExternT, typename StateT>
    REX_STD_TEMPLATED_CLASS_ALIAS(codecvt, InternT, ExternT, StateT);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(collate, CharT);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(messages, CharT);

    template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(time_get, CharT, InputIt);

    template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(time_put, CharT, OutputIt);

    template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(num_get, CharT, InputIt);

    template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(num_put, CharT, OutputIt);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(numpunct, CharT);

    template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(money_get, CharT, InputIt);

    template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(money_put, CharT, OutputIt);

    template <typename CharT, bool International = false>
    REX_STD_TEMPLATED_CLASS_ALIAS(moneypunct, CharT, International);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(ctype_byname, CharT);

    template <typename InternT, typename ExternT, typename State>
    REX_STD_TEMPLATED_CLASS_ALIAS(codecvt_byname, InternT, ExternT, State);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(messages_byname, CharT);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(collate_byname, CharT);

    template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(time_get_byname, CharT, InputIt);

    template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(time_put_byname, CharT, OutputIt);

    template <typename CharT>
    REX_STD_TEMPLATED_CLASS_ALIAS(numpunct_byname, CharT);

    template <typename CharT, bool International = false>
    REX_STD_TEMPLATED_CLASS_ALIAS(moneypunct_byname, CharT, International);

    REX_STD_FUNC_ALIAS(use_facet);
    REX_STD_FUNC_ALIAS(has_facet);

    REX_STD_FUNC_ALIAS(isspace);
    REX_STD_FUNC_ALIAS(isblank);
    REX_STD_FUNC_ALIAS(iscntrl);
    REX_STD_FUNC_ALIAS(isupper);
    REX_STD_FUNC_ALIAS(islower);
    REX_STD_FUNC_ALIAS(isalpha);
    REX_STD_FUNC_ALIAS(isdigit);
    REX_STD_FUNC_ALIAS(ispunct);
    REX_STD_FUNC_ALIAS(isxdigit);
    REX_STD_FUNC_ALIAS(isalnum);
    REX_STD_FUNC_ALIAS(isprint);
    REX_STD_FUNC_ALIAS(isgraph);

    REX_STD_FUNC_ALIAS(toupper);
    REX_STD_FUNC_ALIAS(tolower);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
