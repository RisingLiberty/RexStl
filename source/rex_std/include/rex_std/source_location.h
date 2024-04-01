// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: source_location.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/header/source_location
//
// Represents information about source code.
//-----------------------------------------------------------------------------

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/types.h"

#ifdef RSL_ENABLE_WITH_CPP20
  #define RSL_CONSTEVAL_WITH_CPP20 consteval
#else
  #define RSL_CONSTEVAL_WITH_CPP20 constexpr
#endif

namespace rsl
{
  inline namespace v1
  {

    class source_location
    {
    public:
      RSL_CONSTEVAL_WITH_CPP20 source_location()
          : m_line(0)
          , m_column(0)
          , m_file_name()
          , m_function_name()
      {
      }

      static constexpr source_location current(const card32 line = __builtin_LINE(), card32 column = __builtin_COLUMN(), const char8* file = __builtin_FILE(), const char8* function = __builtin_FUNCTION())
      {
        source_location res {};

        res.m_line          = line;
        res.m_column        = column;
        res.m_file_name     = rsl::string_view(file);
        res.m_function_name = rsl::string_view(function);

        return res;
      }

      card32 line() const
      {
        return m_line;
      }
      card32 column() const
      {
        return m_column;
      }
      rsl::string_view file_name() const
      {
        return m_file_name;
      }
      rsl::string_view function_name() const
      {
        return m_function_name;
      }

    private:
      card32 m_line;
      card32 m_column;
      rsl::string_view m_file_name;
      rsl::string_view m_function_name;
    };

    rsl::big_stack_string to_string(const source_location& sourceLoc);
    rsl::wbig_stack_string to_wstring(const source_location& sourceLoc);

  } // namespace v1
} // namespace rsl
