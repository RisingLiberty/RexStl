// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: iostream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/istream/basic_iostream.h"
#include "rex_std/internal/string/char_traits.h"
#include "rex_std/istream.h"
#include "rex_std/ostream.h"
#include "rex_std/assert.h"

namespace rsl
{
  inline namespace v1
  {

    using iostream  = basic_iostream<char8, char_traits<char8>>;
    using wiostream = basic_iostream<tchar, char_traits<tchar>>;

    extern rsl::istream cin; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
    // extern rsl::wistream wcin; /// [08/Sep/2022] RSL Comment: Wide character input not supported yet

    extern rsl::ostream cout; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
    // extern rsl::wostream wcout; /// [08/Sep/2022] RSL Comment: Wide character output not supported yet

    extern rsl::ostream cerr; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
    // extern rsl::wostream wcerr; /// [08/Sep/2022] RSL Comment: Wide character output not supported yet

    extern rsl::ostream clog; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
    // extern rsl::wostream wclog; /// [08/Sep/2022] RSL Comment: Wide character output not supported yet

  } // namespace v1
} // namespace rsl
