// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: diagnostics.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/diagnostics/assert.h"
#include "rex_std/bonus/diagnostics/console_colors.h"
#include "rex_std/bonus/diagnostics/log_message.h"
#include "rex_std/bonus/diagnostics/logging.h"

#ifdef RSL_PLATFORM_WINDOWS
  #include "rex_std/bonus/diagnostics/win/hr_call.h"
  #include "rex_std/bonus/diagnostics/win/win_call.h"
  #include "rex_std/bonus/diagnostics/win/win_console.h"
  #include "rex_std/bonus/diagnostics/win/win_debug.h"
  #include "rex_std/bonus/diagnostics/win/win_error.h"
  #include "rex_std/bonus/diagnostics/win/win_message_box.h"
  #include "rex_std/bonus/diagnostics/win/win_stack_tracing.h"
#endif