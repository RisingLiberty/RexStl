// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: span.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <span>

REX_RSL_BEGIN_NAMESPACE

    REX_STD_OBJECT_ALIAS(dynamic_extent);   
    
    template <typename T, size_t Extent = rsl::dynamic_extent>
    REX_STD_TEMPLATED_CLASS_ALIAS(span, T, Extent);

    REX_STD_FUNC_ALIAS(as_bytes);
    REX_STD_FUNC_ALIAS(as_writable_bytes);

    REX_STD_FUNC_ALIAS(begin);
    REX_STD_FUNC_ALIAS(cbegin);
    REX_STD_FUNC_ALIAS(end);
    REX_STD_FUNC_ALIAS(cend);
    REX_STD_FUNC_ALIAS(rbegin);
    REX_STD_FUNC_ALIAS(crbegin);
    REX_STD_FUNC_ALIAS(rend);
    REX_STD_FUNC_ALIAS(crend);
    REX_STD_FUNC_ALIAS(size);
    REX_STD_FUNC_ALIAS(ssize);
    REX_STD_FUNC_ALIAS(empty);
    REX_STD_FUNC_ALIAS(data);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
