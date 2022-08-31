// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: sstream.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/string/char_traits.h"

#include "rex_std/bonus/memory/typed_allocator.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <sstream>

namespace rsl
{
    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_stringbuf, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_istringstream, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ostringstream, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_stringstream, CharT, Traits, Allocator);

    REX_STD_CLASS_ALIAS(stringbuf);
    REX_STD_CLASS_ALIAS(wstringbuf);

    REX_STD_CLASS_ALIAS(istringstream);
    REX_STD_CLASS_ALIAS(wistringstream);

    REX_STD_CLASS_ALIAS(ostringstream);
    REX_STD_CLASS_ALIAS(wostringstream);
    
    REX_STD_CLASS_ALIAS(stringstream);
    REX_STD_CLASS_ALIAS(wstringstream);

    //REX_STD_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap
}

#include "rex_std/enable_std_checking.h"