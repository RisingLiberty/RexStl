// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: condition_variable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <condition_variable>

REX_RSL_BEGIN_NAMESPACE

REX_STD_CLASS_ALIAS(condition_variable);
REX_STD_CLASS_ALIAS(condition_variable_any);
REX_STD_CLASS_ALIAS(cv_status);

REX_STD_FUNC_ALIAS(notify_all_at_thread_exit);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
