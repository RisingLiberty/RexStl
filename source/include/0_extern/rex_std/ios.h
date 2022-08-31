// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: ios.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/bonus/types.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <ios>

namespace rsl
{
    REX_STD_CLASS_ALIAS(ios_base);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ios, CharT, Traits);

    REX_STD_CLASS_ALIAS(ios);
    REX_STD_CLASS_ALIAS(wios);

    template <typename State>
    REX_STD_TEMPLATED_CLASS_ALIAS(fpos, State);

    REX_STD_CLASS_ALIAS(io_errc);

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(is_error_code_enum, T);

    REX_STD_FUNC_ALIAS(iostream_category);
    REX_STD_FUNC_ALIAS(make_error_code);
    REX_STD_FUNC_ALIAS(make_error_condition);
    REX_STD_FUNC_ALIAS(boolalpha);
    REX_STD_FUNC_ALIAS(noboolalpha);
    REX_STD_FUNC_ALIAS(showbase);
    REX_STD_FUNC_ALIAS(noshowbase);
    REX_STD_FUNC_ALIAS(showpoint);
    REX_STD_FUNC_ALIAS(noshowpoint);
    REX_STD_FUNC_ALIAS(skipws);
    REX_STD_FUNC_ALIAS(noskipws);
    REX_STD_FUNC_ALIAS(uppercase);
    REX_STD_FUNC_ALIAS(nouppercase);
    REX_STD_FUNC_ALIAS(unitbuf);
    REX_STD_FUNC_ALIAS(nounitbuf);
    //REX_STD_FUNC_ALIAS(internal); // this doesn't work due to the internal namespace
    REX_STD_FUNC_ALIAS(left);
    REX_STD_FUNC_ALIAS(right);
    REX_STD_FUNC_ALIAS(dec);
    REX_STD_FUNC_ALIAS(hex);
    REX_STD_FUNC_ALIAS(oct);
    REX_STD_FUNC_ALIAS(fixed);
    REX_STD_FUNC_ALIAS(scientific);
    REX_STD_FUNC_ALIAS(hexfloat);
    REX_STD_FUNC_ALIAS(defaultfloat);
}

#include "rex_std/enable_std_checking.h"