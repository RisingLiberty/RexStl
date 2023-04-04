// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_isstream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/ios/io_types.h"
#include "rex_std/internal/istream/basic_istream.h"
#include "rex_std/internal/sstream/basic_stringbuf.h"
#include "rex_std/internal/type_traits/is_same.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits = char_traits<CharType>, typename Allocator = rsl::allocator>
    class basic_istringstream : public basic_istream<CharType, Traits>
    {
    private:
      using base = basic_istream<CharType, Traits>;

    public:
      using char_type      = CharType;
      using traits_type    = Traits;
      using int_type       = typename Traits::int_type;
      using pos_type       = typename Traits::pos_type;
      using off_type       = typename Traits::off_type;
      using allocator_type = Allocator;

      basic_istringstream()
          : base(&m_str_buff)
          , m_str_buff()
      {
      }
      explicit basic_istringstream(io::openmode mode)
          : base(&m_str_buff)
          , m_str_buff(mode)
      {
      }

      explicit basic_istringstream(const basic_string<CharType, Traits, Allocator>& str, io::openmode mode = io::openmode::in | io::openmode::out)
          : base(&m_str_buff)
          , m_str_buff(str, mode)
      {
      }
      basic_istringstream(basic_istringstream&& other)
          : base(rsl::move(other))
          , m_str_buff(rsl::move(other.m_str_buff))
      {
      }
      basic_istringstream(io::openmode mode, const Allocator& alloc)
          : base(&m_str_buff)
          , m_str_buff(mode, alloc)
      {
      }

      basic_istringstream& operator=(basic_istringstream&& other)
      {
        base::operator=(rsl::move(other));
        m_str_buff = rsl::move(other.m_str_buff);
      }

      void swap(basic_istringstream& other)
      {
        base::swap(other);
        rsl::swap(m_str_buff, other.m_str_buff);
      }
      basic_stringbuf<CharType, Traits, Allocator>* rdbuf()
      {
        return &m_str_buff;
      }

      basic_string<CharType, Traits, Allocator> str() const
      {
        return m_str_buff.str();
      }
      void str(const basic_string<CharType, Traits, Allocator>& str)
      {
        m_str_buff.str(str);
      }
      basic_string_view<CharType, Traits> view() const
      {
        return m_str_buff.view();
      }

    private:
      basic_stringbuf<CharType, Traits, Allocator> m_str_buff;
    };

    template <typename CharType, typename Traits>
    void swap(basic_istringstream<CharType, Traits>& lhs, basic_istringstream<CharType, Traits>& rhs)
    {
      basic_istringstream<CharType, Traits> tmp = rsl::move(lhs);
      lhs                                       = rsl::move(rhs);
      rhs                                       = rsl::move(tmp);
    }

    using istringstream  = basic_istringstream<rsl::char8>;
    using wistringstream = basic_istringstream<rsl::char16>;
  } // namespace v1
} // namespace rsl
