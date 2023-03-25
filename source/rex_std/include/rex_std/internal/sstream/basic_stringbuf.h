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
#include "rex_std/internal/string/basic_string.h"
#include "rex_std/internal/string_view/basic_string_view.h"

#include "rex_std/string.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits = char_traits<CharType>, typename Allocator = allocator>
    class basic_stringbuf : public basic_streambuf<CharType, Traits>
    {
    public:
      using char_type = CharType;
      using traits_type = Traits;
      using int_type = typename Traits::int_type;
      using pos_type = typename Traits::pos_type;
      using off_type = typename Traits::off_type;

      basic_stringbuf();
      explicit basic_stringbuf(io::openmode which);
      explicit basic_stringbuf(const basic_string<CharType, Traits, Allocator>& s, io::openmode which = io::openmode::in | io::openmode::out);
      basic_stringbuf(const basic_string<CharType, Traits, Allocator>& rhs) = delete;
      basic_stringbuf(basic_stringbuf&& rhs);
      explicit basic_stringbuf(const Allocator& alloc);
      explicit basic_stringbuf(io::openmode which, const Allocator& alloc);
      explicit basic_stringbuf(basic_string<CharType, Traits, Allocator>&& s, io::openmode which = io::openmode::in | io::openmode::out);

      basic_stringbuf& operator=(const basic_stringbuf&) = delete;
      basic_stringbuf& operator=(basic_stringbuf&&);

      void swap(basic_stringbuf& other);

      basic_string<CharType, Traits, Allocator> str() const;

      /// RSL Comment: Different from ISO C++ Standard at time of writing (25/Mar/2023)
      // Returns the allocator associated with the container
      const allocator_type& get_allocator() const;

      rsl::basic_string_view<CharType, Traits> view() const;

    protected:
      int_type underflow() override;
      int_type pbackfail(int_type c) override;
      int_type overflow(int_type c);
      basic_streambuf<CharType, Traits>* setbuf(char_type* s, streamsize n);
      pos_type seekoff(off_type off, io::seekdir dir, io::openmode which = io::openmode::in | io::openmode::out);
      pos_type seekpos(pos_type sp, io::openmode which = io::openmode::in | io::openmode::out);

    private:
      Allocator m_allocator;
    };

    template <typename CharType, typename Traits, typename Allocator>
    void swap(basic_stringbuf<CharType, Traits, Allocator>& lhs, basic_stringbuf<CharType, Traits, Allocator>& rhs)
    {
      lhs.swap(rhs);
    }
  }
}