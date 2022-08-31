// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: move_iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <iterator>

namespace rsl
{
    template <typename Iterator>
    REX_STD_TEMPLATED_CLASS_ALIAS(move_iterator, Iterator);
}

#include "rex_std/enable_std_checking.h"
