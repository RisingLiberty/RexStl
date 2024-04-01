// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: filesystem.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/filesystem/core_mounts.h"
#include "rex_std/bonus/filesystem/open_flags.h"

#ifdef RSL_PLATFORM_WINDOWS
  #include "rex_std/bonus/filesystem/win/win_file.h"
  #include "rex_std/bonus/filesystem/win/win_virtual_file_system.h"
#endif