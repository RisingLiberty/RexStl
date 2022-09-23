// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: future.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/internal/memory/uses_allocator.h"
#include "rex_std/std_alias_defines.h"

#include <future>

REX_RSL_BEGIN_NAMESPACE

template <typename R>
REX_STD_TEMPLATED_CLASS_ALIAS(promise, R);

template <typename R>
REX_STD_TEMPLATED_CLASS_ALIAS(packaged_task, R);

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(future, T);

template <typename T>
REX_STD_TEMPLATED_CLASS_ALIAS(shared_future, T);

REX_STD_CLASS_ALIAS(launch);
REX_STD_CLASS_ALIAS(future_status);
REX_STD_CLASS_ALIAS(future_errc);

REX_STD_FUNC_ALIAS(async);
REX_STD_FUNC_ALIAS(future_category);
// REX_STD_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap // Doesn't work because rsl has its own swap

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
