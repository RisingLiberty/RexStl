// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_filebuf.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/io/basic_filebuf
//
// a basic_streambuf that's associated with a character sequence
// of a file.
//-----------------------------------------------------------------------------

#pragma once

#include "rex_std/bonus/iostream/get_area.h"
#include "rex_std/bonus/platform/windows/handle.h"
#include "rex_std/internal/ios/ios_base.h"
#include "rex_std/internal/streambuf/basic_streambuf.h"
#include "rex_std/internal/string_view/basic_string_view.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      using handle = void*;

      class filebuf_impl
      {
      public:
        explicit filebuf_impl();
        filebuf_impl(const filebuf_impl&) = delete;
        filebuf_impl(filebuf_impl&& other);
        ~filebuf_impl();

        filebuf_impl& operator=(const filebuf_impl&) = delete;
        filebuf_impl& operator=(filebuf_impl&&);

        bool open(const char8* filename, io::openmode mode);
        bool open(rsl::string_view filename, io::openmode mode);
        // bool open(const rsl::filesystem::path& filename, io::openmode mode);
        // bool open(const rsl::filesystem::path::value_type* filename, io::openmode mode);

        bool close();

        streamsize xsgetn(char8* s, size_t elemSize, streamsize count);
        streamsize xsputn(const char8* s, size_t elemSize, streamsize count);

        template <typename CharT, typename Traits>
        typename Traits::int_type overflow(CharT ch)
        {
          return (xsputn(&ch, sizeof(CharT), 1) / sizeof(CharT)) == 0 ? Traits::eof() : ch;
        }
        template <typename CharT, typename Traits>
        typename Traits::int_type overflown(const CharT* s, count_t count)
        {
          return (xsputn(s, sizeof(CharT), count) / sizeof(CharT)) != count ? Traits::eof() : CharT();
        }

        template <typename CharT>
        struct underflow_result
        {
          get_area* get_area;
          CharT ch;
        };
        template <typename CharT, typename Traits>
        underflow_result<CharT> underflow() // we reached the end of the get area, get from stream, store first char in stream
        {
          if(!m_get_area.is_allocated())
          {
            m_get_area.allocate();
          }

          if(m_get_area.num_available_to_load() == 0)
          {
            m_get_area.reset();
          }

          const streamsize count_read = xsgetn(m_get_area.current(), sizeof(CharT), 1) / sizeof(CharT);
          m_get_area.inc_end();

          underflow_result<CharT> res {};
          res.get_area = &m_get_area;
          res.ch       = count_read == 0 ? Traits::to_char_type(Traits::eof()) : *res.get_area->current();

          return res;
        }
        template <typename CharT, typename Traits>
        underflow_result<CharT> uflow() // we reached the end of the get area, get from stream, inc pointer
        {
          if(!m_get_area.is_allocated())
          {
            m_get_area.allocate();
          }

          if(m_get_area.num_available_to_load() == 0)
          {
            m_get_area.reset();
          }

          const streamsize count_read = xsgetn(m_get_area.current(), sizeof(CharT), 1) / sizeof(CharT);

          m_get_area.inc_current();
          m_get_area.inc_end();

          underflow_result<CharT> res {};

          res.get_area = &m_get_area;
          res.ch       = count_read == 0 ? Traits::to_char_type(Traits::eof()) : *res.get_area->current();

          return res;
        }
        template <typename CharT>
        struct uflown_result
        {
          get_area* get_area;
          streamsize num_read;
        };
        template <typename CharT, typename Traits>
        uflown_result<CharT> uflown(CharT* s, streamsize count) // we reached the end of the get area, get from stream, inc pointer
        {
          // we're not checking if the get area is allocated because we don't have to.
          // if there's no get area, we load the directly from the character sequence
          // directly into the destination.
          // This means if an invalid read happened, there's no way to put it back

          const streamsize num_available = m_get_area.num_available();
          if(count > num_available)
          {
            // first load the characters in the get area
            rsl::memcpy(s, m_get_area.current(), sizeof(CharT) * num_available);
            m_get_area.reset();
          }

          const streamsize count_read = xsgetn(s, sizeof(CharT), count) / sizeof(CharT);

          uflown_result<CharT> res {};
          res.get_area = &m_get_area;
          res.num_read = count_read;

          return res;
        }

        get_area area() const
        {
          return m_get_area;
        }

      private:
        get_area m_get_area;
        win::handle_t m_handle;
        rsl::io::openmode m_openmode;
      };
    } // namespace internal

    template <typename CharT, typename Traits>
    class basic_filebuf : public basic_streambuf<CharT, Traits>
    {
    private:
      using base = basic_streambuf<char8, char_traits<char8>>;

    public:
      using char_type   = typename base::char_type;
      using traits_type = typename base::traits_type;
      using int_type    = typename base::int_type;
      using pos_type    = typename base::pos_type;
      using off_type    = typename base::off_type;

      basic_filebuf()
          : m_impl()
      {
      }
      basic_filebuf(const basic_filebuf&)  = delete;
      basic_filebuf(basic_filebuf&& other) = default;
      ~basic_filebuf()
      {
        close();
      }
      basic_filebuf& operator=(const basic_filebuf&) = delete;
      basic_filebuf& operator=(basic_filebuf&& rhs);

      void swap(basic_filebuf& other);

      bool is_open() const;

      basic_filebuf* open(const char8* filename, io::openmode mode)
      {
        return m_impl.open(filename, mode) ? this : false;
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (29/Jan/2023)
      // the standard takes a string here, we take a string_view
      basic_filebuf* open(const string_view filename, io::openmode mode)
      {
        return m_impl.open(filename, mode) ? this : false;
      }
      // basic_filebuf* open(const filesystem::path& filename, io::openmode mode)
      //{
      //   m_impl.open(filename, mode);
      // }
      // basic_filebuf* open(const filesystem::path::value_type* filename, io::openmode mode)
      //{
      //   m_impl.open(filename, mode);
      // }

      basic_filebuf* close()
      {
        return m_impl.close() ? this : false;
      }

    protected:
      streamsize xsgetn(char_type* s, streamsize count) final
      {
        return m_impl.xsgetn(s, sizeof(CharT), count);
      }
      streamsize xsputn(const char_type* s, streamsize count) final
      {
        return m_impl.xsputn(s, sizeof(CharT), count);
      }

      int_type overflow(int_type ch) final
      {
        return m_impl.overflow<char_type, traits_type>(traits_type::to_char_type(ch));
      }
      streamsize overflown(const char_type* s, streamsize count) final
      {
        return m_impl.overflown<char_type, traits_type>(s, count);
      }
      int_type underflow() final
      {
        if(base::gptr() && base::gptr() < base::egptr()) // can we still get characters from the get area?
        {
          return traits_type::to_int_type(*base::gptr());
        }
        else // get it from the character sequence
        {
          internal::filebuf_impl::underflow_result<CharT> res = m_impl.underflow<char_type, traits_type>();

          // it's possible we allocated a intermediate buffer, so we have to set the pointers
          base::setg(&res.get_area->begin(), &res.get_area->current(), &res.get_area->end());
          return res.ch;
        }
      }
      int_type uflow() final
      {
        if(base::gptr() && base::gptr() < base::egptr()) // can we still get characters from the get area?
        {
          return traits_type::to_int_type(*base::gptr());
        }
        else // get it from the character sequence
        {
          internal::filebuf_impl::underflow_result<CharT> res = m_impl.uflow<char_type, traits_type>();

          // it's possible we allocated a intermediate buffer, so we have to set the pointers
          base::setg(&res.get_area->begin(), &res.get_area->current(), &res.get_area->end());
          return res.ch;
        }
      }
      streamsize uflown(char_type* s, streamsize count) final
      {
        if(base::gptr() && base::gptr() < base::egptr()) // can we still get characters from the get area?
        {
          return traits_type::to_int_type(*base::gptr());
        }
        else // get it from the character sequence
        {
          internal::filebuf_impl::uflown_result<char_type> res = m_impl.uflown<char_type, traits_type>(s, count);

          // it's possible we allocated a intermediate buffer, so we have to set the pointers
          base::setg(&res.get_area->begin(), &res.get_area->current(), &res.get_area->end());
          return res.num_read;
        }
      }

    private:
      internal::filebuf_impl m_impl;
    };

  } // namespace v1
} // namespace rsl