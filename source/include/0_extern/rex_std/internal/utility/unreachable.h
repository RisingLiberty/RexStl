// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: unreachable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/attributes.h"

REX_RSL_BEGIN_NAMESPACE

    REX_NO_RETURN void unreachable()
    {
        #if defined(__GNUC__) // GCC, Clang, ICC
            __builtin_unreachable();
        #elif defined(_MSC_VER) // MSVC
            __assume(false);
        #endif
    }

REX_RSL_END_NAMESPACE
