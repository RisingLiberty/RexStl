// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: regex.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/memory/typed_allocator.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/std_alias_defines.h"

#include <regex>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT>, regex_traits, CharT);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename Traits = regex_traits<CharT>>, basic_regex, CharT, Traits);

    RSL_CLASS_ALIAS(regex);
    RSL_CLASS_ALIAS(wregex);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename BiDirIt>, sub_match, BiDirIt);

    RSL_CLASS_ALIAS(csub_match);
    RSL_CLASS_ALIAS(wcsub_match);
    RSL_CLASS_ALIAS(ssub_match);
    RSL_CLASS_ALIAS(wssub_match);

    class allocator;

    RSL_TEMPLATED_CLASS_ALIAS(template <typename BiDirIt, typename Alloc = typed_allocator<typename iterator_traits<BiDirIt>::value_type>>, match_results, BiDirIt, Alloc);

    RSL_CLASS_ALIAS(cmatch);
    RSL_CLASS_ALIAS(wcmatch);
    RSL_CLASS_ALIAS(smatch);
    RSL_CLASS_ALIAS(wsmatch);

    template <typename Iterator>
    struct iterator_traits;

    RSL_TEMPLATED_CLASS_ALIAS(template <typename BiDirIt, typename CharT, typename iterator_traits<BiDirIt>::value_type, typename Traits = regex_traits<CharT>>, regex_iterator, BiDirIt, CharT, Traits);

    RSL_CLASS_ALIAS(cregex_iterator);
    RSL_CLASS_ALIAS(wcregex_iterator);
    RSL_CLASS_ALIAS(sregex_iterator);
    RSL_CLASS_ALIAS(wsregex_iterator);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename BiDirIt, typename CharT = typename iterator_traits<BiDirIt>::value_type, typename Traits = regex_traits<CharT>>, regex_token_iterator, BiDirIt, CharT, Traits);

    RSL_CLASS_ALIAS(cregex_token_iterator);
    RSL_CLASS_ALIAS(wcregex_token_iterator);
    RSL_CLASS_ALIAS(sregex_token_iterator);
    RSL_CLASS_ALIAS(wsregex_token_iterator);

    RSL_CLASS_ALIAS(regex_error);

    namespace regex_constants
    {
      using namespace std::regex_constants;
    }

    RSL_FUNC_ALIAS(regex_match);
    RSL_FUNC_ALIAS(regex_search);
    RSL_FUNC_ALIAS(regex_replace);

    // RSL_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap

    RSL_FUNC_ALIAS(operator==);
    RSL_FUNC_ALIAS(operator!=);
    RSL_FUNC_ALIAS(operator<);
    RSL_FUNC_ALIAS(operator<=);
    RSL_FUNC_ALIAS(operator>);
    RSL_FUNC_ALIAS(operator>=);
    RSL_FUNC_ALIAS(operator<<);
    RSL_FUNC_ALIAS(begin);
    RSL_FUNC_ALIAS(cbegin);
    RSL_FUNC_ALIAS(cend);
    RSL_FUNC_ALIAS(rbegin);
    RSL_FUNC_ALIAS(crbegin);
    RSL_FUNC_ALIAS(rend);
    RSL_FUNC_ALIAS(crend);
    RSL_FUNC_ALIAS(size);
    RSL_FUNC_ALIAS(ssize);
    RSL_FUNC_ALIAS(empty);
    RSL_FUNC_ALIAS(data);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
