// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stop_token.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_ENABLE_WITH_CPP20

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <stop_token>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(stop_token);
    RSL_CLASS_ALIAS(stop_source);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename Callback>, stop_callback, Callback);

    RSL_CLASS_ALIAS(nostopstate_t);

    RSL_OBJECT_ALIAS(nostopstate);

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif // RSL_ENABLE_WITH_CPP20
