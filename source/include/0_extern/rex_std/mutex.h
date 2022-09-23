// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mutex.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <mutex>

REX_RSL_BEGIN_NAMESPACE

REX_STD_CLASS_ALIAS(mutex);
REX_STD_CLASS_ALIAS(timed_mutex);
REX_STD_CLASS_ALIAS(recursive_mutex);
REX_STD_CLASS_ALIAS(recursive_timed_mutex);

template <typename Mutex>
REX_STD_TEMPLATED_CLASS_ALIAS(lock_guard, Mutex);
template <typename Mutex>
REX_STD_TEMPLATED_CLASS_ALIAS(unique_lock, Mutex);
template <typename... Mutexes>
REX_STD_TEMPLATED_CLASS_ALIAS(scoped_lock, Mutexes...);

REX_STD_CLASS_ALIAS(defer_lock_t);
REX_STD_CLASS_ALIAS(try_to_lock_t);
REX_STD_CLASS_ALIAS(adopt_lock_t);

REX_STD_CLASS_ALIAS(once_flag);

REX_STD_OBJECT_ALIAS(defer_lock);
REX_STD_OBJECT_ALIAS(try_to_lock);
REX_STD_OBJECT_ALIAS(adopt_lock);

REX_STD_FUNC_ALIAS(try_lock);
REX_STD_FUNC_ALIAS(lock);
REX_STD_FUNC_ALIAS(call_once);
// REX_STD_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
