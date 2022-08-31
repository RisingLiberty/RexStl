// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: print.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#ifdef REX_ENABLE_WITH_CPP23

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <print>

namespace rsl
{
    REX_STD_FUNC_ALIAS(print);
    REX_STD_FUNC_ALIAS(println);
    REX_STD_FUNC_ALIAS(vprint_unicode);
    REX_STD_FUNC_ALIAS(vprint_nounicode);
}

#include "rex_std/enable_std_checking.h"

#endif // REX_ENABLE_WITH_CPP23