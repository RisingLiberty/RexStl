// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: locale.h
// Copyright (c) Nick De Breuck 2023
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

    RSL_CLASS_ALIAS(locale);

    class allocator;

    // Deprecated in C++17
    // template <typename Codecvt, typename Elem = tchar, typename Wide_alloc = allocator, typename Byte_alloc = allocator>
    // RSL_TEMPLATED_CLASS_ALIAS(wstring_convert, Codecvt, Elem, Wide_alloc, Byte_alloc);

    template <typename T>
    class char_traits;

    // Deprecated in C++17
    // template <typename Codecvt, typename Elem = tchar, typename Tr = char_traits<tchar>>
    // RSL_TEMPLATED_CLASS_ALIAS(wbuffer_convert, Codecvt, Elem, Tr);

    RSL_CLASS_ALIAS(ctype_base);
    RSL_CLASS_ALIAS(codecvt_base);
    RSL_CLASS_ALIAS(messages_base);
    RSL_CLASS_ALIAS(time_base);
    RSL_CLASS_ALIAS(money_base);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, ctype, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename InternT, typename ExternT, typename StateT>, codecvt, InternT, ExternT, StateT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, collate, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, messages, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>, time_get, CharT, InputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>, time_put, CharT, OutputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>, num_get, CharT, InputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>, num_put, CharT, OutputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, numpunct, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>, money_get, CharT, InputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>, money_put, CharT, OutputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, bool International = false>, moneypunct, CharT, International);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, ctype_byname, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename InternT, typename ExternT, typename State>, codecvt_byname, InternT, ExternT, State);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, messages_byname, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, collate_byname, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename InputIt = istreambuf_iterator<CharT>>, time_get_byname, CharT, InputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename OutputIt = ostreambuf_iterator<CharT>>, time_put_byname, CharT, OutputIt);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, numpunct_byname, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, bool International = false>, moneypunct_byname, CharT, International);

    RSL_FUNC_ALIAS(use_facet);
    RSL_FUNC_ALIAS(has_facet);

    RSL_FUNC_ALIAS(isspace);
    RSL_FUNC_ALIAS(isblank);
    RSL_FUNC_ALIAS(iscntrl);
    RSL_FUNC_ALIAS(isupper);
    RSL_FUNC_ALIAS(islower);
    RSL_FUNC_ALIAS(isalpha);
    RSL_FUNC_ALIAS(isdigit);
    RSL_FUNC_ALIAS(ispunct);
    RSL_FUNC_ALIAS(isxdigit);
    RSL_FUNC_ALIAS(isalnum);
    RSL_FUNC_ALIAS(isprint);
    RSL_FUNC_ALIAS(isgraph);

    RSL_FUNC_ALIAS(toupper);
    RSL_FUNC_ALIAS(tolower);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
