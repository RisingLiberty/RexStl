// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: stacktrace.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#ifdef REX_ENABLE_WITH_CPP23

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <stacktrace>

namespace rsl
{
    REX_STD_CLASS_ALIAS(stacktrace_entry);

    template <typename Allocator>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_stacktrace, Allocator);

    REX_STD_CLASS_ALIAS(stacktrace);
    namespace pmr
    {
        using stacktrace = std::pmr::stacktrace;
    }

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(hash, T);

    
    REX_STD_FUNC_ALIAS(to_string);
    REX_STD_FUNC_ALIAS(operator<<);
}

#include "rex_std/enable_std_checking.h"

#endif
