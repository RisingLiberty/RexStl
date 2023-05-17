// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: basic_filebuf.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/fstream/basic_filebuf.h"

#include <Windows.h>                         // for FILE_BEGIN, FILE_END
// IWYU pragma: no_include <built-in>

#include "rex_std/assert.h"                  // for rex_assert, basic_string_view, string_view, memcpy
#include "rex_std/bonus/utility/has_flag.h"  // for has_flag
#include "rex_std/bonus/utility/nand.h"      // for nand
#include "rex_std/internal/array/array.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/stddef.h"                  // for size_t

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      DWORD mode_to_creation_disposition(io::openmode mode)
      {
        RSL_ASSERT_X(rsl::nand(rsl::has_flag(mode, io::openmode::app), rsl::has_flag(mode, io::openmode::trunc)), "both append and trunc provided as openmode");

        DWORD result = 0;
        if(rsl::has_flag(mode, io::openmode::trunc))
        {
          result |= TRUNCATE_EXISTING;
        }
        else if(rsl::has_flag(mode, io::openmode::out))
        {
          result |= OPEN_ALWAYS;
        }
        else if(rsl::has_flag(mode, io::openmode::in))
        {
          result |= OPEN_EXISTING;
        }

        return result;
      }

      void append_file(HANDLE fileHandle)
      {
        SetFilePointer(fileHandle, 0, nullptr, FILE_END);
      }
      void trunc_file(HANDLE fileHandle)
      {
        SetFilePointer(fileHandle, 0, nullptr, FILE_BEGIN);
      }
      HANDLE open_impl(const char8* filename, io::openmode mode)
      {
        // this function opens the file handle but doesn't read anything
        HANDLE handle = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, mode_to_creation_disposition(mode), FILE_ATTRIBUTE_NORMAL, nullptr);

        if(rsl::has_flag(mode, rsl::io::openmode::app) || rsl::has_flag(mode, rsl::io::openmode::ate))
        {
          append_file(handle);
        }
        else if(rsl::has_flag(mode, rsl::io::openmode::trunc))
        {
          trunc_file(handle);
        }

        return handle;
      }

      filebuf_impl::filebuf_impl()
          : m_get_area()
          , m_handle(INVALID_HANDLE_VALUE)
          , m_openmode(rsl::io::openmode::app) // open in append mode to not accidentally delete file content
      {
      }

      filebuf_impl::filebuf_impl(filebuf_impl&& other)
          : m_get_area(other.m_get_area)
          , m_handle(other.m_handle)
          , m_openmode(other.m_openmode)
      {
        other.m_get_area = internal::get_area();
        other.m_handle   = win::handle_t();
      }

      filebuf_impl::~filebuf_impl()
      {
        m_get_area.deallocate();
      }

      bool filebuf_impl::open(const char8* filename, io::openmode mode)
      {
        m_openmode = mode;

        m_handle = open_impl(filename, mode);

        return m_handle != INVALID_HANDLE_VALUE;
      }
      bool filebuf_impl::open(const rsl::string_view filename, io::openmode mode)
      {
        // need to copy this into a temporary buffer because it's possible the string view
        // is not null terminated and would therefore pass in an invalid path
        rsl::array<char8, 256> buff = {};

        RSL_ASSERT_X(filename.length() < buff.max_size(), "exceeded max filename length of {} characters", buff.max_size());
        rsl::memcpy(buff.data(), filename.data(), filename.length());

        return open(buff.data(), mode);
      }
      // bool filebuf_impl::open(const rsl::filesystem::path& filename, io::openmode mode)
      //{
      //
      // }
      // bool filebuf_impl::open(const rsl::filesystem::path::value_type* filename, io::openmode mode)
      //{
      //
      // }

      bool filebuf_impl::close()
      {
        if(m_handle != INVALID_HANDLE_VALUE)
        {
          return CloseHandle(m_handle) != 0;
        }

        return true;
      }

      streamsize filebuf_impl::xsgetn(char8* s, size_t elemSize, streamsize count)
      {
        if(rsl::has_flag(m_openmode, rsl::io::openmode::binary) == false) // NOLINT(readability-simplify-boolean-expr)
        {
          count--; // don't get the nullchar, as there isn't any
        }

        DWORD num_read = 0;
        ReadFile(m_handle, s, static_cast<DWORD>(count * elemSize), &num_read, nullptr);
        return static_cast<streamsize>(num_read);
      }
      streamsize filebuf_impl::xsputn(const char8* s, size_t elemSize, streamsize count)
      {
        if(rsl::has_flag(m_openmode, rsl::io::openmode::binary) == false) // NOLINT(readability-simplify-boolean-expr)
        {
          count--; // don't write the nullchar
        }

        DWORD num_written = 0;
        WriteFile(m_handle, s, static_cast<DWORD>(count * elemSize), &num_written, nullptr);
        return static_cast<streamsize>(num_written);
      }
    } // namespace internal
  }   // namespace v1
} // namespace rsl