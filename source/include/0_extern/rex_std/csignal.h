// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: csignal.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/bonus/types.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <csignal>

namespace rsl
{
    using sig_atomic = int32;

    REX_STD_FUNC_ALIAS(signal);
    REX_STD_FUNC_ALIAS(raise);
}

#include "rex_std/enable_std_checking.h"