// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_fstream.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/istream/basic_iostream.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits>
    class basic_fstream : public basic_iostream<CharType, Traits>
    {
    private:
      using base = basic_iostream<CharType, Traits>;

    public:
      // constructs a stream that is not associated with a file
      basic_fstream()
          : basic_iostream<CharType, Traits>(&m_filebuf)
      {
      }

      // associates the stream with a file that has the given filename
      explicit basic_fstream(const char8* filename, io::openmode mode = io::openmode::in | io::openmode::out)
          : basic_ios(&m_filebuf)
          , basic_iostream<CharType, Traits>(&m_filebuf)
      {
        open(filename, mode);
      }
      //// associates the stream with a file that has the given filename
      // explicit basic_fstream(const filesystem::path::value_type* filename, io::openmode mode = io::openmode::in | io::openmode::out)
      //   : base(m_filebuf)
      //{
      //   open(filename, mode)
      // }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (29/Jan/2023)
      // The standard takes in a string, we take in a string_view.
      // associates the stream with a file that has the given filename
      explicit basic_fstream(const string_view filename, io::openmode mode = io::openmode::in | io::openmode::out)
          : base(&m_filebuf)
      {
        open(filename, mode);
      }
      // associates the stream with a file that has the given filename
      // explicit basic_fstream(const filesystem::filepath& filename, io::openmode mode = io::openmode::in | io::openmode::out)
      //  : base(m_filebuf)
      //{
      //  open(filename, mode);
      //}
      basic_fstream(const basic_fstream&) = delete;
      basic_fstream(basic_fstream&& other)
          : base(rsl::move(other))
      {
        m_filebuf = rsl::move(other.rdbuf());
        base::set_rdbuf(m_filebuf);
      }

      // moves the file stream
      basic_fstream& operator=(basic_fstream&& other)
      {
        base::move(other);
        m_filebuf = rsl::move(other.m_filebuf);
      }

      // swaps two file streams
      void swap(basic_fstream& other)
      {
        base::swap(other);
        rdbuf()->swap(other.rdbuf());
      }

      bool is_open() const
      {
        return rdbuf()->is_open();
      }
      void open(const char8* filename, io::openmode mode = io::openmode::in | io::openmode::out)
      {
        rdbuf()->open(filename, mode | io::openmode::in) ? base::clear() : base::setstate(io::iostate::failbit);
      }
      // void open(const filesystem::path::value_type* filename, io::openmode mode = io::openmode::in | io::openmode::out)
      //{
      //   rdbuf()->open(filename, mode | io::openmode::in)
      //     ? base::clear()
      //     : base::setstate(io::iostate::failbit);
      // }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (29/Jan/2023)
      // the standard takes in a string, we take in a string_view
      void open(const string_view filename, io::openmode mode = io::openmode::in | io::openmode::out)
      {
        rdbuf()->open(filename, mode | io::openmode::in) ? base::clear() : base::setstate(io::iostate::failbit);
      }
      // void open(const filesystem::path& filename, io::openmode::mode = io::openmode::in | io::openmode::out)
      //{
      //   rdbuf()->open(filename, mode | io::openmode::in)
      //     ? base::clear()
      //     : base::setstate(io::iostate::failbit);
      // }
      void close()
      {
        rdbuf()->close();
      }

      basic_filebuf<CharType, Traits>* rdbuf()
      {
        return &m_filebuf;
      }

    private:
      basic_filebuf<CharType, Traits> m_filebuf;
    };

    template <typename CharType, typename Traits>
    void swap(basic_fstream<CharType, Traits>& lhs, basic_fstream<CharType, Traits>& rhs)
    {
      basic_fstream<CharType, Traits> tmp = rsl::move(lhs);
      lhs                                 = rsl::move(rhs);
      rhs                                 = rsl::move(tmp);
    }
  } // namespace v1
} // namespace rsl
