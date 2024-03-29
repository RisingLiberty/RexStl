// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: istream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/istream/basic_istream.h"
#include "rex_std/internal/string/char_traits.h"

namespace rsl
{
  inline namespace v1
  {

    using istream  = basic_istream<char8, char_traits<char8>>;
    using wistream = basic_istream<tchar, char_traits<tchar>>;

  } // namespace v1
} // namespace rsl
