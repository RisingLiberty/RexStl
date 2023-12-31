// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: source_location.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/source_location.h"

#include "rex_std/string.h"

#include "rex_std/assert.h"

namespace rsl
{
  inline namespace v1
  {
    rsl::big_stack_string to_string(const source_location& sourceLoc)
    {
      rsl::big_stack_string result = ""_big;

      result += sourceLoc.file_name();
      result += "(";
      result += rsl::to_stack_string(sourceLoc.line());
      result += ") ";
      result += sourceLoc.function_name();

      return result;
    }

    rsl::wbig_stack_string to_wstring(const source_location& sourceLoc)
    {
      auto ascii_string = to_string(sourceLoc);

      rsl::wstring res = rsl::to_wstring(ascii_string);

      return rsl::wbig_stack_string(res);
    }
  } // namespace v1
} // namespace rsl