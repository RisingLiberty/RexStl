// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: streambuf.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/bonus/types.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <streambuf>

namespace rsl
{
    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_streambuf, CharT, Traits);

    REX_STD_CLASS_ALIAS(streambuf);
    REX_STD_CLASS_ALIAS(wstreambuf);
}

#include "rex_std/enable_std_checking.h"