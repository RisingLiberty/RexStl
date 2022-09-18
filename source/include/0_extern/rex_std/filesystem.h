// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: filesystem.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <filesystem>

REX_RSL_BEGIN_NAMESPACE

    namespace filesystem
    {
        using namespace std::filesystem;
    }

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"