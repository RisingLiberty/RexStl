// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: charconv.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <charconv>

REX_RSL_BEGIN_NAMESPACE

REX_STD_CLASS_ALIAS(chars_format);

REX_STD_FUNC_ALIAS(from_chars);
REX_STD_FUNC_ALIAS(to_chars);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
