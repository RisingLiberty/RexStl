// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: typeindex.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include "rex_std/compare.h"

#include <typeindex>

REX_RSL_BEGIN_NAMESPACE

    REX_STD_CLASS_ALIAS(type_index);
    template <typename T>
    struct hash;

REX_RSL_END_NAMESPACE
#include "rex_std/enable_std_checking.h"
