// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: logging.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/diagnostics/logging.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

REX_RSL_BEGIN_NAMESPACE

const StringView SeperationTokens = "##############################";

REX_RSL_END_NAMESPACE

rsl::StringView rsl::seperator()
{
  return SeperationTokens;
}