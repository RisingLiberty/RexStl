// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: assert.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std_extra/fmt/fmt_format.h"

#ifdef REX_ENABLE_ASSERTS
  #undef REX_ENABLE_ASSERTS
#endif

#ifdef REX_ENABLE_ASSERTS

REX_RSL_BEGIN_NAMESPACE

template <typename CharType>
class BasicStringView;
using StringView = BasicStringView<char8>;

class Allocator;

template <typename CharType, typename Alloc>
class BasicString;
using String = BasicString<char8, Allocator>;

REX_RSL_END_NAMESPACE

REX_RSL_BEGIN_NAMESPACE::internal
{
  void internal_assert(const char8* file, const char8* function, card32 line_nr, rsl::StringView message);
  void internal_assert(rsl::StringView condition_str, const char8* file, const char8* function, card32 line_nr, rsl::StringView message);
}

  #define REX_ASSERT_X(condition, ...)                                                                                                                                                                                                                   \
    if(!(condition))                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
  rsl::internal::internal_assert(#condition, __FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__);                                                                                                                                                 \
    }

  #define REX_ASSERT(...) rsl::internal::internal_assert(__FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__));

#else

  #define REX_ASSERT_X(condition, ...)                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_ASSERT(...)                                                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                    \
    }

#endif