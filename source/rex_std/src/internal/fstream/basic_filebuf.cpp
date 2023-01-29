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
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/bonus/utility/has_flag.h"
#include "rex_std/bonus/utility/nand.h"

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      DWORD mode_to_creation_disposition(io::openmode mode)
      {
        REX_ASSERT_X(rsl::nand(rsl::has_flag(mode, io::openmode::app), rsl::has_flag(mode, io::openmode::trunc)));

        DWORD result = 0;
        if (rsl::has_flag(mode, io::openmode::trunc))
        {
          result |= TRUNCATE_EXISTING;
        }
        else if (rsl::has_flag(mode, io::openmode::out))
        {
          result |= OPEN_ALWAYS;
        }
        else if (rsl::has_flag(mode, io::openmode::in))
        {
          result |= OPEN_EXISTING;
        }

        return result;
      }

      filebuf_impl::filebuf_impl(win::handle_t handle)
        : m_get_area()
        , m_handle(handle)
      {
      }

      filebuf_impl::filebuf_impl(filebuf_impl&& other)
        : m_get_area(other.m_get_area)
        , m_handle(other.m_handle)
      {
        other.m_get_area = internal::get_area();
        other.m_handle = win::handle_t();
      }

      filebuf_impl::~filebuf_impl()
      {
        m_get_area.deallocate();
      }

      bool filebuf_impl::open(const char8* filename, io::openmode mode)
      {
        // this function opens the file handle but doesn't read anything
        m_handle = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, FILE_GENERIC_READ | FILE_GENERIC_WRITE, NULL, mode_to_creation_disposition(mode), FILE_ATTRIBUTE_NORMAL, nullptr);

        return m_handle != INVALID_HANDLE_VALUE;
      }
      bool filebuf_impl::open(const rsl::string_view filename, io::openmode mode)
      {
        REX_ASSERT_X(filename.length() < sizeof(buff));

        // need to copy this into a temporary buffer because it's possible the string view
        // is not null terminated and would therefore pass in an invalid path
        char8 buff[256] = {};
        rsl::memcpy(buff, filename.data(), filename.length());
        
        return open(buff, mode);
      }
      //bool filebuf_impl::open(const rsl::filesystem::path& filename, io::openmode mode)
      //{
      //
      //}
      //bool filebuf_impl::open(const rsl::filesystem::path::value_type* filename, io::openmode mode)
      //{
      //
      //}

      bool filebuf_impl::close()
      {
        if (m_handle != INVALID_HANDLE_VALUE)
        {
          return CloseHandle(m_handle) != 0;
        }

        return true;
      }

      streamsize filebuf_impl::xsgetn(char8* s, size_t elemSize, streamsize count)
      {
        DWORD num_read = 0;
        ReadFile(m_handle, s, static_cast<DWORD>(count * elemSize), &num_read, nullptr);
        return static_cast<streamsize>(num_read);
      }
      streamsize filebuf_impl::xsputn(const char8* s, size_t elemSize, streamsize count)
      {
        DWORD num_written = 0;
        WriteFile(m_handle, s, static_cast<DWORD>(count * elemSize), &num_written, nullptr);
        return static_cast<streamsize>(num_written);
      }
    }
  }
}