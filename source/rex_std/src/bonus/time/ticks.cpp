// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: ticks.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/time/ticks.h"

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      int64 get_time_in_ticks()
      {
        constexpr int64 epoch = 0x19DB1DED53E8000LL;
        FILETIME ft;
        GetSystemTimePreciseAsFileTime(&ft);
        return ((static_cast<int64>(ft.dwHighDateTime)) << 32) + static_cast<int64>(ft.dwLowDateTime) - epoch; // NOLINT(hicpp-signed-bitwise)
      }
    } // namespace internal
  }   // namespace v1
} // namespace rsl