// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: spanstream.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP23

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <spanstream>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename Traits = char_traits<CharT>>, basic_spanbuf, CharT, Traits);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename Traits = char_traits<CharT>>, basic_ispanstream, CharT, Traits);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename Traits = char_traits<CharT>>, basic_ospanstream, CharT, Traits);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename CharT, typename Traits = char_traits<CharT>>, basic_spanstream, CharT, Traits);

    RSL_CLASS_ALIAS(spanbuf);
    RSL_CLASS_ALIAS(wspanbuf);

    RSL_CLASS_ALIAS(ispanstream);
    RSL_CLASS_ALIAS(wispanstream);

    RSL_CLASS_ALIAS(ospanstream);
    RSL_CLASS_ALIAS(wospanstream);

    RSL_CLASS_ALIAS(spanstream);
    RSL_CLASS_ALIAS(wspanstream);

    // RSL_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif // RSL_ENABLE_WITH_CPP23