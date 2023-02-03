// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: fstream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/fstream/basic_fstream.h"
#include "rex_std/internal/fstream/basic_ifstream.h"
#include "rex_std/internal/fstream/basic_ofstream.h"

namespace rsl
{
  inline namespace v1
  {
    using ifstream = basic_ifstream<char8, char_traits<char8>>;
    using ofstream = basic_ofstream<char8, char_traits<char8>>;
    using fstream  = basic_fstream<char8, char_traits<char8>>;

    using wifstream = basic_ifstream<tchar, char_traits<tchar>>;
    using wofstream = basic_ofstream<tchar, char_traits<tchar>>;
    using wfstream  = basic_fstream<tchar, char_traits<tchar>>;
  } // namespace v1
} // namespace rsl
