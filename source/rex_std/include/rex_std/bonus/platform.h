// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: platform.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#ifdef RSL_PLATFORM_WINDOWS
  #include "rex_std/bonus/platform/windows/handle.h"
#endif

#ifdef RSL_PLATFORM_ARM64
  #define RSL_NOT_IMPLEMENTED_FOR_ARM() static_assert(false, "Logic needed here isn't implemented yet for platforms using ARM")
#else
  #define RSL_NOT_IMPLEMENTED_FOR_ARM()
#endif