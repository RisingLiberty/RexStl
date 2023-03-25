// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_sstream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/istream/basic_iostream.h"
#include "rex_std/internal/ios/io_types.h"

#include "rex_std/internal/type_traits/is_same.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits = char_traits<CharType>, typename Allocator = allocator>
    class basic_stringstream : public basic_iostream<CharType, Traits>
    {
    private:
      using base = basic_iostream<CharType, Traits>;

    public:
      using char_type = CharType;
      using traits_type = Traits;
      using int_type = typename Traits::int_type;
      using pos_type = typename Traits::pos_type;
      using off_type = typename Traits::off_type;
      using allocator_type = Allocator;

      basic_stringstream();
      explicit basic_stringstream(io::openmode mode);
      explicit basic_stringstream(const basic_string<CharType, Traits, Allocator>& str, io::openmode mode = io::openmode::in | io::openmode::out);
      basic_stringstream(basic_stringstream&& other);
      basic_stringstream(io::openmode mode, const Allocator& alloc);
      explicit basic_stringstream(basic_string<CharType, Traits, Allocator>&& str, io::openmode mode = io::openmode::in | io::openmode::out);

      basic_stringstream& operator=(basic_stringstream&& other);

      void swap(basic_stringstream& other);
      basic_stringbuf<CharType, Traits, Allocator>* rdbuf();

      basic_string<CharType, Traits, Allocator> str() const;
      basic_string_view<CharType, Traits> view() const;
    };

    template <typename CharType, typename Traits, typename Allocator>
    void swap(basic_stringstream<CharType, Traits, Allocator>& lhs, basic_stringstream<CharType, Traits, Allocator>& rhs)
    {
      lhs.swap(rhs);
    }
  }
}