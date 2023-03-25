// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_stringbuf.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/string/char_traits.h"
#include "rex_std/internal/memory/allocator.h"
#include "rex_std/internal/ios/ios_base.h"
#include "rex_std/internal/streambuf/basic_streambuf.h"

#include "rex_std/string.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits = char_traits<CharType>, typename Allocator = allocator>
    class basic_stringbuf : public basic_streambuf<CharType, Traits>
    {
    public:
      basic_stringbuf();
      explicit basic_stringbuf(io::openmode which);
      explicit basic_stringbuf(const basic_string<CharType, Traits, Allocator>& s, io::openmode which = io::openmode::in | io::openmode::out);
      basic_stringbuf(const basic_string<CharType, Traits, Allocator>& rhs) = delete;
      basic_stringbuf(basic_stringbuf&& rhs);
      explicit basic_stringbuf(const Allocator& alloc);
      explicit basic_stringbuf(io::openmode which, const Allocator& alloc);
      explicit basic_stringbuf(basic_string<CharType, Traits, Allocator>&& s, io::openmode which = io::openmode::in | io::openmode::out);

    private:

    };
  }
}