// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: ostream.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <ostream>

namespace rsl
{
    template <typename CharT>
    class char_traits;

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ostream, CharT, Traits);

    REX_STD_CLASS_ALIAS(ostream);
    REX_STD_CLASS_ALIAS(wostream);

    REX_STD_FUNC_ALIAS(operator<<);

    REX_STD_FUNC_ALIAS(endl);
    REX_STD_FUNC_ALIAS(ends);
    REX_STD_FUNC_ALIAS(flush);

#ifdef REX_ENABLE_WITH_CPP20
    REX_STD_FUNC_ALIAS(emit_on_flush);
    REX_STD_FUNC_ALIAS(noemit_on_flush);
    REX_STD_FUNC_ALIAS(flush_emit);
#endif // REX_ENABLE_WITH_CPP20
}

#include "rex_std/enable_std_checking.h"