// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stop_token.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#ifdef REX_ENABLE_WITH_CPP20

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <stop_token>

REX_RSL_BEGIN_NAMESPACE

REX_STD_CLASS_ALIAS(stop_token);
REX_STD_CLASS_ALIAS(stop_source);

template <typename Callback>
REX_STD_TEMPLATED_CLASS_ALIAS(stop_callback, Callback);

REX_STD_CLASS_ALIAS(nostopstate_t);

REX_STD_OBJECT_ALIAS(nostopstate);

REX_RSL_END_NAMESPACE

  #include "rex_std/enable_std_checking.h"

#endif // REX_ENABLE_WITH_CPP20
