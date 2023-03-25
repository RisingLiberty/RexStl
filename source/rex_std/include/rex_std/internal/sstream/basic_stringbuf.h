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
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/string.h"
#include "rex_std/limits.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits = char_traits<CharType>, typename Allocator = allocator>
    class basic_stringbuf : public basic_streambuf<CharType, Traits>
    {
    private:
      using base = basic_streambuf<CharType, Traits>;

    public:
      using char_type = CharType;
      using traits_type = Traits;
      using int_type = typename Traits::int_type;
      using pos_type = typename Traits::pos_type;
      using off_type = typename Traits::off_type;

      basic_stringbuf()
        : base()
      {}
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
      int_type overflow(int_type c)
      {
        if (traits_type::eq_int_type(traits_type::eof(), c))
        {
          return traits_type::not_eof(c);
        }

        // we can add to our internal buffer
        if (base::pptr() && base::pptr() < base::eptr())
        {

        }

        const auto old_size = base::epptr() - base::pbase();
        const auto new_size = old_size;
        if (old_size < (rsl::numeric_limits<int32>::max)() / 2)
        {
          new_size = old_size * 2;
        }
        else if (old_size < (rsl::numeric_limits<int32>::max)())
        {
          new_size = (rsl::numeric_limits<int32>::max)();
        }
        else
        {
          return traits_type::eof();
        }

        const auto old_read_size = base::gptr() - base::eback();
        const auto new_buffer = m_allocate.allocate(new_size);
        traits_type::copy(new_buffer, base::epbase(), old_size);

        m_allocator.deallocate(m_buffer, old_size);
        m_buffer = new_buffer;

        m_current_write = m_buffer + old_size;
        m_current_read = m_buffer + old_read_size;
        m_buffer_end = new_buffer + new_size;

        base::setg(&m_buffer, &m_current_read, &m_buffer_end);
        base::setp(&m_buffer, &m_current_write, &m_buffer_end);
      }
      basic_streambuf<CharType, Traits>* setbuf(char_type* s, streamsize n);
      pos_type seekoff(off_type off, io::seekdir dir, io::openmode which = io::openmode::in | io::openmode::out);
      pos_type seekpos(pos_type sp, io::openmode which = io::openmode::in | io::openmode::out);

    private:
      Allocator m_allocator;
      CharType* m_buffer;
      CharType* m_buffer_end;
      CharType* m_current_read;
      CharType* m_current_write;
    };

    template <typename CharType, typename Traits, typename Allocator>
    void swap(basic_stringbuf<CharType, Traits, Allocator>& lhs, basic_stringbuf<CharType, Traits, Allocator>& rhs)
    {
      lhs.swap(rhs);
    }
  }
}