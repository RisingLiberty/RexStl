// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/iterator/bidirectional_iterator.h"
#include "rex_std/internal/iterator/forward_iterator.h"
#include "rex_std/internal/iterator/iterator_tags.h"
#include "rex_std/internal/iterator/random_access_iterator.h"
#include "rex_std/internal/iterator/reverse_iterator.h"

REX_RSL_BEGIN_NAMESPACE

/// RSL Comment: Not in ISO C++ Standard at time of writing (17/Aug/2022)
template <typename It>
constexpr auto iterator_to_pointer(It it)
{
  return &(*it);
}

/// RSL Comment: Not in ISO C++ Standard at time of writing (17/Aug/2022)
template <typename It>
constexpr const auto const_iterator_to_pointer(It it)
{
  return &(*it);
}

/// RSL Comment: Not in ISO C++ Standard at time of writing (17/Aug/2022)
template <typename reverse_iterator>
constexpr auto to_forward_iterator(reverse_iterator it)
{
  return (it + 1).base();
}

REX_RSL_END_NAMESPACE

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <iterator>

REX_RSL_BEGIN_NAMESPACE
// No C++20 symbols added here

template <typename Container>
REX_STD_TEMPLATED_CLASS_ALIAS(back_insert_iterator, Container);

template <typename Container>
REX_STD_TEMPLATED_CLASS_ALIAS(front_insert_iterator, Container);

template <typename Container>
REX_STD_TEMPLATED_CLASS_ALIAS(insert_iterator, Container);

template <typename CharT>
class char_traits;

template <typename T, typename CharT = char8, typename Traits = rsl::char_traits<CharT>, typename Distance = ptrdiff>
REX_STD_TEMPLATED_CLASS_ALIAS(istream_iterator, T, CharT, Traits, Distance);

template <typename T, typename CharT = char8, typename Traits = rsl::char_traits<CharT>>
REX_STD_TEMPLATED_CLASS_ALIAS(ostream_iterator, T, CharT, Traits);

template <typename CharT, typename Traits = char_traits<CharT>>
REX_STD_TEMPLATED_CLASS_ALIAS(ostreambuf_iterator, CharT, Traits);

REX_STD_FUNC_ALIAS(front_inserter);
REX_STD_FUNC_ALIAS(back_inserter);
REX_STD_FUNC_ALIAS(inserter);

REX_STD_FUNC_ALIAS(operator==);
REX_STD_FUNC_ALIAS(operator!=);
REX_STD_FUNC_ALIAS(operator<);
REX_STD_FUNC_ALIAS(operator<=);
REX_STD_FUNC_ALIAS(operator>);
REX_STD_FUNC_ALIAS(operator>=);
REX_STD_FUNC_ALIAS(operator+);
REX_STD_FUNC_ALIAS(operator-);

REX_STD_FUNC_ALIAS(advance);
REX_STD_FUNC_ALIAS(distance);
REX_STD_FUNC_ALIAS(next);
REX_STD_FUNC_ALIAS(prev);
REX_STD_FUNC_ALIAS(begin);
REX_STD_FUNC_ALIAS(cbegin);
REX_STD_FUNC_ALIAS(end);
REX_STD_FUNC_ALIAS(cend);
REX_STD_FUNC_ALIAS(rbegin);
REX_STD_FUNC_ALIAS(crbegin);
REX_STD_FUNC_ALIAS(rend);
REX_STD_FUNC_ALIAS(crend);
REX_STD_FUNC_ALIAS(size);
REX_STD_FUNC_ALIAS(ssize);
REX_STD_FUNC_ALIAS(data);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"