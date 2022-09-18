// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: memory_resource.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/enable_std_checking.h"

#include <memory_resource>

REX_RSL_BEGIN_NAMESPACE

    namespace pmr
    {
        using namespace std::pmr;
    }

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
