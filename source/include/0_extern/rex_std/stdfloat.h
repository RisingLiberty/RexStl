// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: stdfloat.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#ifdef REX_ENABLE_WITH_CPP23

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <stdfloat>

REX_RSL_BEGIN_NAMESPACE

    REX_STD_CLASS_ALIAS(float16_t);
    REX_STD_CLASS_ALIAS(float32_t);
    REX_STD_CLASS_ALIAS(float64_t);
    REX_STD_CLASS_ALIAS(float128_t);
    REX_STD_CLASS_ALIAS(bfloat16_t);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"

#endif