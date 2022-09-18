// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: any.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <any>

REX_RSL_BEGIN_NAMESPACE

    REX_STD_CLASS_ALIAS(any);

    ////REX_STD_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap // Doesn't work because rsl has its own swap
    REX_STD_FUNC_ALIAS(make_any);
    REX_STD_FUNC_ALIAS(any_cast);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
