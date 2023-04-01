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

#include "rex_std/bonus/utility/has_flag.h"
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/internal/ios/ios_base.h"
#include "rex_std/internal/memory/allocator.h"
#include "rex_std/internal/streambuf/basic_streambuf.h"
#include "rex_std/internal/string/basic_string.h"
#include "rex_std/internal/string/char_traits.h"
#include "rex_std/internal/string_view/basic_string_view.h"
#include "rex_std/limits.h"
#include "rex_std/string.h"

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
      using char_type      = CharType;
      using traits_type    = Traits;
      using int_type       = typename Traits::int_type;
      using pos_type       = typename Traits::pos_type;
      using off_type       = typename Traits::off_type;
      using allocator_type = Allocator;

      basic_stringbuf()
          : base()
          , m_buffer(nullptr)
          , m_buffer_end(nullptr)
          , m_current_read(nullptr)
          , m_current_write(nullptr)
          , m_openmode(io::openmode::in | io::openmode::out)
          , m_allocator()
      {
      }
      explicit basic_stringbuf(io::openmode which)
          : base()
          , m_buffer(nullptr)
          , m_buffer_end(nullptr)
          , m_current_read(nullptr)
          , m_current_write(nullptr)
          , m_openmode(which)
          , m_allocator()
      {
      }
      explicit basic_stringbuf(const basic_string<CharType, Traits, Allocator>& s, io::openmode which = io::openmode::in | io::openmode::out)
          : base()
          , m_buffer(nullptr)
          , m_buffer_end(nullptr)
          , m_current_read(nullptr)
          , m_current_write(nullptr)
          , m_openmode(which)
          , m_allocator(s.get_allocator())
      {
        str(s);
      }
      explicit basic_stringbuf(const Allocator& alloc)
          : base()
          , m_buffer(nullptr)
          , m_buffer_end(nullptr)
          , m_current_read(nullptr)
          , m_current_write(nullptr)
          , m_openmode(io::openmode::in | io::openmode::out)
          , m_allocator(alloc)
      {
      }
      explicit basic_stringbuf(io::openmode which, const Allocator& alloc)
          : base()
          , m_buffer(nullptr)
          , m_buffer_end(nullptr)
          , m_current_read(nullptr)
          , m_current_write(nullptr)
          , m_openmode(which)
          , m_allocator(alloc)
      {
      }
      basic_stringbuf(const basic_stringbuf<CharType, Traits, Allocator>& rhs) = delete;
      basic_stringbuf(basic_stringbuf&& rhs)
          : base(rsl::move(rhs))
          , m_buffer(rhs.m_buffer)
          , m_buffer_end(rhs.m_buffer_end)
          , m_current_read(rhs.m_current_read)
          , m_current_write(rhs.m_current_write)
          , m_openmode(rhs.m_openmode)
          , m_allocator(rhs.m_allocator)
      {
        rhs.m_buffer        = nullptr;
        rhs.m_buffer_end    = nullptr;
        rhs.m_current_read  = nullptr;
        rhs.m_current_write = nullptr;
      }

      basic_stringbuf& operator=(const basic_stringbuf&) = delete;
      basic_stringbuf& operator=(basic_stringbuf&&);

      void swap(basic_stringbuf& other)
      {
        rsl::swap(m_buffer, other.m_buffer);
        rsl::swap(m_buffer_end, other.m_buffer_end);
        rsl::swap(m_current_read, other.m_current_read);
        rsl::swap(m_current_write, other.m_current_write);
        rsl::swap(m_openmode, other.m_openmode);
        rsl::swap(m_allocator, other.m_allocator);
      }

      basic_string<CharType, Traits, Allocator> str() const
      {
        if(rsl::has_flag(m_openmode, io::openmode::out))
        {
          return rsl::basic_string<CharType, Traits, Allocator>(m_buffer, m_current_write);
        }
        else if(rsl::has_flag(m_openmode, io::openmode::in))
        {
          return rsl::basic_string<CharType, Traits, Allocator>(m_buffer, m_current_read);
        }
        else
        {
          return basic_string<CharType, Traits, Allocator> {};
        }
      }
      void str(const basic_string<CharType, Traits, Allocator>& str)
      {
        const auto buffer_size = m_buffer_end - m_buffer;
        if(str.size() > buffer_size)
        {
          m_allocator.deallocate(m_buffer, buffer_size);
          m_buffer = static_cast<char_type*>(m_allocator.allocate(str.size() + 1));
          m_buffer_end = m_buffer + str.size();
        }

        traits_type::copy(m_buffer, str.data(), str.size() + 1);

        m_current_read  = m_buffer;
        m_current_write = m_buffer;
      }

      /// RSL Comment: Different from ISO C++ Standard at time of writing (25/Mar/2023)
      // Returns the allocator associated with the container
      const allocator_type& get_allocator() const
      {
        return m_allocator;
      }

      rsl::basic_string_view<CharType, Traits> view() const
      {
        return rsl::basic_string_view<CharType, Traits>(m_buffer, m_buffer_end);
      }

    protected:
      int_type underflow() override
      {
        const auto gptr = base::gptr();

        if(!gptr)
        {
          return traits_type::eof();
        }

        if(gptr < base::egptr())
        {
          return traits_type::to_int_type(*gptr);
        }

        return traits_type::eof();
      }
      int_type pbackfail(int_type c) override
      {
        const auto gptr = base::gptr();

        // no current read pointer or it's aready at the beginning
        if(!gptr || gptr == base::eback())
        {
          return traits_type::eof();
        }

        base::gbump(-1);
        if(!traits_type::eq_int_type(traits_type::eof(), c))
        {
          *base::gptr() = traits_type::to_char_type(c);
        }

        return traits_type::not_eof(c);
      }
      int_type overflow(int_type c) override
      {
        char_type ch = traits_type::to_char_type(c);
        if(overflown(&ch, 1) == -1)
        {
          return traits_type::not_eof(c);
        }
        return c;
      }
      int_type overflown(const char_type* s, streamsize count) override
      {
        const auto old_size = base::epptr() - base::pbase();
        auto new_size       = old_size;
        if(old_size == 0)
        {
          new_size = count;
        }
        else if(old_size < (rsl::numeric_limits<int32>::max)() / 2)
        {
          new_size = (old_size * 2) + count;
        }
        else if(old_size < (rsl::numeric_limits<int32>::max)())
        {
          new_size = (rsl::numeric_limits<int32>::max)();
        }
        else
        {
          return traits_type::eof();
        }

        const auto old_read_size = base::gptr() - base::eback();
        const auto new_buffer    = static_cast<CharType*>(m_allocator.allocate(new_size));

        traits_type::copy(new_buffer, base::eback(), static_cast<count_t>(old_size));
        traits_type::copy(new_buffer + old_size, s, count);

        m_allocator.deallocate(m_buffer, old_size);
        m_buffer = new_buffer;

        m_current_write = m_buffer + old_size + count;
        m_current_read  = m_buffer + old_read_size;
        m_buffer_end    = new_buffer + new_size;

        base::setg(&m_buffer, &m_current_read, &m_buffer_end);
        base::setp(&m_buffer, &m_current_write, &m_buffer_end);

        return count;
      }

      pos_type seekoff(off_type off, io::seekdir dir, io::openmode which = io::openmode::in | io::openmode::out) override
      {
        const pos_type buffer_length = static_cast<off_type>(m_buffer_end - m_buffer);
        const pos_type read_off      = static_cast<off_type>(m_current_read - m_buffer);
        const pos_type write_off     = static_cast<off_type>(m_current_write - m_buffer);

        switch(dir)
        {
          case rsl::v1::io::seekdir::beg:
          {
            if(rsl::has_flag(which, io::openmode::in))
            {
              m_current_read = m_buffer;
            }
            if(rsl::has_flag(which, io::openmode::out))
            {
              m_current_write = m_buffer;
            }
            return pos_type(0);
          }
          case rsl::v1::io::seekdir::end:
          {
            if(rsl::has_flag(which, io::openmode::in))
            {
              m_current_read = m_buffer_end;
            }
            if(rsl::has_flag(which, io::openmode::out))
            {
              m_current_write = m_buffer_end;
            }
            return static_cast<pos_type>(buffer_length);
          }
          case rsl::v1::io::seekdir::cur:
          {
            if(read_off + off < 0 || read_off + off > (buffer_length))
            {
              return static_cast<pos_type>(static_cast<off_type>(-1));
            }
            if(write_off + off < 0 || write_off + off > (buffer_length))
            {
              return static_cast<pos_type>(static_cast<off_type>(-1));
            }
            if(rsl::has_flag(which, io::openmode::in))
            {
              m_current_read = m_current_read + off;
            }
            if(rsl::has_flag(which, io::openmode::out))
            {
              m_current_write = m_current_write + off;
            }
            return static_cast<pos_type>(read_off);
          }
        }

        return pos_type(-1);
      }
      pos_type seekpos(pos_type sp, io::openmode which = io::openmode::in | io::openmode::out) override
      {
        const auto buffer_length = m_buffer_end - m_buffer;
        if(sp < 0 || sp > buffer_length)
        {
          return off_type(-1);
        }

        if(rsl::has_flag(which, io::openmode::in))
        {
          m_current_read = m_buffer + sp;
        }
        if(rsl::has_flag(which, io::openmode::out))
        {
          m_current_write = m_buffer + sp;
        }

        return sp;
      }

    private:
      CharType* m_buffer;
      CharType* m_buffer_end;
      CharType* m_current_read;
      CharType* m_current_write;
      io::openmode m_openmode;
      Allocator m_allocator;
    };

    template <typename CharType, typename Traits, typename Allocator>
    void swap(basic_stringbuf<CharType, Traits, Allocator>& lhs, basic_stringbuf<CharType, Traits, Allocator>& rhs)
    {
      lhs.swap(rhs);
    }
  } // namespace v1
} // namespace rsl