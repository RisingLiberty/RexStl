// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: istream.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <istream>

namespace rsl
{
    template <typename CharT>
    class char_traits;

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_istream, CharT, Traits);

    REX_STD_CLASS_ALIAS(istream);
    REX_STD_CLASS_ALIAS(wistream);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_iostream, CharT, Traits);

    REX_STD_CLASS_ALIAS(iostream);
    REX_STD_CLASS_ALIAS(wiostream);

    REX_STD_FUNC_ALIAS(operator>>);
    REX_STD_FUNC_ALIAS(ws);
}

#include "rex_std/enable_std_checking.h"