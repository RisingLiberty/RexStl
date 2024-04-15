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

#include "rex_std/internal/ios/io_types.h"
#include "rex_std/internal/istream/basic_iostream.h"
#include "rex_std/internal/sstream/basic_stringbuf.h"
#include "rex_std/internal/type_traits/is_same.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits = char_traits<CharType>, typename Alloc = allocator>
    class basic_stringstream : public basic_iostream<CharType, Traits>
    {
    private:
      using base = basic_iostream<CharType, Traits>;

    public:
      using char_type      = CharType;
      using traits_type    = Traits;
      using int_type       = typename Traits::int_type;
      using pos_type       = typename Traits::pos_type;
      using off_type       = typename Traits::off_type;
      using allocator_type = Alloc;

      basic_stringstream()
          : base(&m_str_buff)
          , m_str_buff()
      {
      }
      explicit basic_stringstream(io::openmode mode)
          : base(&m_str_buff)
          , m_str_buff(mode)
      {
      }

      basic_stringstream(const basic_stringstream<CharType, Traits, Alloc>& str)
          : basic_stringstream(str.str(), io::openmode::in | io::openmode::out)
      {
      }
      explicit basic_stringstream(const basic_string<CharType, Traits, Alloc>& str, io::openmode mode = io::openmode::in | io::openmode::out)
          : base(&m_str_buff)
          , m_str_buff(str, mode)
      {
      }
      basic_stringstream(basic_stringstream&& other)
          : base(rsl::move(other))
          , m_str_buff(rsl::move(other.m_str_buff))
      {
      }
      basic_stringstream(io::openmode mode, const Alloc& alloc)
          : base(&m_str_buff)
          , m_str_buff(mode, alloc)
      {
      }

      ~basic_stringstream() override = default;

      basic_stringstream& operator=(const basic_stringstream& other) = delete;

      basic_stringstream& operator=(basic_stringstream&& other)
      {
        base::operator=(rsl::move(other));
        m_str_buff = rsl::move(other.m_str_buff);
      }

      void swap(basic_stringstream& other)
      {
        base::swap(other);
        rsl::swap(m_str_buff, other.m_str_buff);
      }
      basic_stringbuf<CharType, Traits, Alloc>* rdbuf()
      {
        return &m_str_buff;
      }

      basic_string<CharType, Traits, Alloc> str() const
      {
        return m_str_buff.str();
      }
      void str(const basic_string<CharType, Traits, Alloc>& str)
      {
        m_str_buff.str(str);
      }
      basic_string_view<CharType, Traits> view() const
      {
        return m_str_buff.view();
      }

    private:
      basic_stringbuf<CharType, Traits, Alloc> m_str_buff;
    };

    template <typename CharType, typename Traits, typename Alloc>
    void swap(basic_stringstream<CharType, Traits, Alloc>& lhs, basic_stringstream<CharType, Traits, Alloc>& rhs)
    {
      lhs.swap(rhs);
    }

    using stringstream  = basic_stringstream<rsl::char8>;
    using wstringstream = basic_stringstream<rsl::char16>;
  } // namespace v1
} // namespace rsl