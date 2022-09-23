// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: deque.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/memory/typed_allocator.h"
#include "rex_std/compare.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/initializer_list.h"
#include "rex_std/std_alias_defines.h"

#include <deque>

REX_RSL_BEGIN_NAMESPACE

template <typename T, typename Allocator = typed_allocator<T>>
REX_STD_TEMPLATED_CLASS_ALIAS(deque, T, Allocator);

REX_STD_FUNC_ALIAS(operator==);
REX_STD_FUNC_ALIAS(operator!=);
REX_STD_FUNC_ALIAS(operator<);
REX_STD_FUNC_ALIAS(operator<=);
REX_STD_FUNC_ALIAS(operator>);
REX_STD_FUNC_ALIAS(operator>=);

REX_STD_FUNC_ALIAS(erase);
REX_STD_FUNC_ALIAS(erase_if);

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
