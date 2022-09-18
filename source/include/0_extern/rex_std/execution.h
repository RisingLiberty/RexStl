// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: execution.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <execution>

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(is_execution_policy, T);

    namespace execution
    {
        using namespace std::execution;
    }

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
