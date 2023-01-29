// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_ifstream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/fstream/basic_filebuf.h"
#include "rex_std/internal/istream/basic_istream.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits>
    class basic_ifstream : public basic_istream<CharType, Traits>
    {
    private:
      using base = basic_istream<CharType, Traits>;

    public:
      // constructs a stream that is not associated with a file
      basic_ifstream()
          : base(m_filebuf)
      {
      }

      // associates the stream with a file that has the given filename
      explicit basic_ifstream(const char8* filename, io::openmode mode = io::openmode::in)
          : base(m_filebuf)
      {
        open(filename, mode);
      }
      // associates the stream with a file that has the given filename
      explicit basic_ifstream(const filesystem::path::value_type* filename, io::openmode mode = io::openmode::in)
          : base(m_filebuf)
      {
        open(filename, mode)
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (29/Jan/2023)
      // The standard takes in a string, we take in a string_view.
      // associates the stream with a file that has the given filename
      explicit basic_ifstream(const string_view filename, io::openmode mode, io::openmode::in)
          : base(m_filebuf)
      {
        open(filename, mode);
      }
      // associates the stream with a file that has the given filename
      explicit basic_ifstream(const filesystem::filepath& filename, io::openmode mode = io::openmode::in)
          : base(m_filebuf)
      {
        open(filename, mode);
      }
      basic_ifstream(const basic_ifstream&) = delete;
      basic_ifstream(basic_ifstream&& other)
          : base(rsl::move(other))
      {
        m_filebuf = rsl::move(other.rdbuf());
        base::set_rdbuf(m_filebuf);
      }

      // moves the file stream
      basic_ifstream& operator=(basic_ifstream&& other)
      {
        base::move(other);
        m_filebuf = rsl::move(other.m_filebuf);
      }

      // swaps two file streams
      void swap(basic_ifstream& other)
      {
        base::swap(other);
        rdbuf()->swap(other.rdbuf());
      }

      bool is_open() const
      {
        return rdbuf()->is_open();
      }
      void open(const char8* filename, io::openmode mode = io::openmode::in)
      {
        rdbuf()->open(filename, mode | io::openmode::in) ? base::clear() : base::setstate(io::iostate::failbit);
      }
      // void open(const filesystem::path::value_type* filename, io::openmode mode = io::openmode::in)
      //{
      //   rdbuf()->open(filename, mode | io::openmode::in)
      //     ? base::clear()
      //     : base::setstate(io::iostate::failbit);
      // }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (29/Jan/2023)
      // the standard takes in a string, we take in a string_view
      void open(const string_view filename, io::openmode mode = io::openmode::in)
      {
        rdbuf()->open(filename, mode | io::openmode::in) ? base::clear() : base::setstate(io::iostate::failbit);
      }
      // void open(const filesystem::path& filename, io::openmode::mode = io::openmode::in)
      //{
      //   rdbuf()->open(filename, mode | io::openmode::in)
      //     ? base::clear()
      //     : base::setstate(io::iostate::failbit);
      // }
      void close()
      {
        rdbuf()->close();
      }

      basic_filebuf<CharT, Traits>* rdbuf() const
      {
        return m_filebuf;
      }

    private:
      basic_filebuf<CharType, Traits> m_filebuf;
    };

    template <typename CharType, typename Traits>
    void swap(basic_ifstream<CharType, Traits>& lhs, basic_ifstream<CharType, Traits>& rhs)
    {
    }
  } // namespace v1
} // namespace rsl
