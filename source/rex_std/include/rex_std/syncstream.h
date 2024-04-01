// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: syncstream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP20

  #include "rex_std/bonus/defines.h"
  #include "rex_std/disable_std_checking.h"
  #include "rex_std/internal/memory/allocator.h"
  #include "rex_std/internal/string/char_traits.h"
  #include "rex_std/ostream.h"
  #include "rex_std/std_alias_defines.h"

  #include <syncstream>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>, basic_syncbuf, CharT, Traits, Allocator);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>, basic_osyncstream, CharT, Traits, Allocator);

    RSL_CLASS_ALIAS(syncbuf);
    RSL_CLASS_ALIAS(wsyncbuf);
    RSL_CLASS_ALIAS(osyncstream);
    RSL_CLASS_ALIAS(wosyncstream);

    // RSL_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif // RSL_ENABLE_WITH_CPP20
