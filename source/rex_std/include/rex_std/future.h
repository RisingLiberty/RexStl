// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: future.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/internal/memory/uses_allocator.h"
#include "rex_std/std_alias_defines.h"

#include <future>

namespace rsl
{
  inline namespace v1
  {

    RSL_TEMPLATED_CLASS_ALIAS(template <typename R>, promise, R);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename R>, packaged_task, R);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, future, T);

    RSL_TEMPLATED_CLASS_ALIAS(template <typename T>, shared_future, T);

    RSL_CLASS_ALIAS(launch);
    RSL_CLASS_ALIAS(future_status);
    RSL_CLASS_ALIAS(future_errc);

    RSL_FUNC_ALIAS(async);
    RSL_FUNC_ALIAS(future_category);
    // RSL_FUNC_ALIAS(swap); // Doesn't work because rsl has its own swap // Doesn't work because rsl has its own swap

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
