// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: shared_mutex.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <shared_mutex>

namespace rsl
{
    REX_STD_CLASS_ALIAS(shared_mutex);
    REX_STD_CLASS_ALIAS(shared_timed_mutex);
    
    template <typename Mutex>
    REX_STD_TEMPLATED_CLASS_ALIAS(shared_lock, Mutex);

    //REX_STD_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap
}

#include "rex_std/enable_std_checking.h"