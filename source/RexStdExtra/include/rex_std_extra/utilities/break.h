// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: break.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

// Microsoft C/C++ Compiler
#ifdef _MSC_VER
  #define REX_BREAK __debugbreak()
#endif

#define REX_BREAK_INF                                                                                                                                                                                                                                    \
  {                                                                                                                                                                                                                                                      \
    while(true)                                                                                                                                                                                                                                          \
    {                                                                                                                                                                                                                                                    \
      REX_BREAK;                                                                                                                                                                                                                                         \
      using REX_RSL_BEGIN_NAMESPACE::chrono_literals;                                                                                                                                                                                                    \
      rsl::this_thread::sleep_for(1s);                                                                                                                                                                                                                   \
    }                                                                                                                                                                                                                                                    \
  }
#define REX_BREAK_MSG(msg)                                                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                      \
    rsl::message_box(msg);                                                                                                                                                                                                                               \
    REX_BREAK;                                                                                                                                                                                                                                           \
  }