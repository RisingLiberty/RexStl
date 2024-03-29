// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: defines.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"

#define REX_UNUSED(x) REX_MAYBE_UNUSED x

#define STRINGIZE(x)  STRINGIZE2(x)
#define STRINGIZE2(x) #x

#define LINE_TO_STRING(L) #L
#define CALL_MACRO(M, L)  M(L)

#ifdef __clang__
  #define STATIC_WARNING(expr)
#else
  #define THIS_LINE             CALL_MACRO(STRINGIZE2, __LINE__)
  #define STATIC_WARNING_PREFIX __FILE__ "(" THIS_LINE "): [WARNING] "
  #define STATIC_WARNING(expr)  __pragma(message(STATIC_WARNING_PREFIX##expr))
#endif

#ifdef __clang__
  #define STATIC_INFO(expr)
#else
  #define STATIC_INFO_PREFIX __FILE__ "(" THIS_LINE "): [INFO] "
  #define STATIC_INFO(expr)  __pragma(message(STATIC_INFO_PREFIX##expr))
#endif

#define MERGE(a, b)  MERGE1(a, b)
#define MERGE1(a, b) MERGE2(a, b)
#define MERGE2(a, b) a##b

#define FUNC_SIGNATURE __FUNCSIG__

#ifdef __COUNTER__
  #define ANONYMOUS_VARIABLE(str) MERGE(str, __COUNTER__)
#else
MERGE(str, __LINE__)
#endif

#define EXECUTE_ONCE(expression)                                                                                                                                                                                                                         \
  static auto ANONYMOUS_VARIABLE(execute_once_var) = [&]()                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                      \
    expression;                                                                                                                                                                                                                                          \
    return 1;                                                                                                                                                                                                                                            \
  }();

#define TO_WIDE_STRING(str) L##str

#ifdef REX_ENABLE_TODO_CHECKING
  #define REX_STATIC_TODO(msg) static_assert(false, "TODO: ", msg);
#else
  #define REX_STATIC_TODO(msg)
#endif

#if defined REX_COMPILER_CLANG
  #define DEBUG_BREAK() __builtin_trap()
#elif defined REX_COMPILER_MSVC
  #define DEBUG_BREAK() __debugbreak()
#else
  #error DEBUG_BREAK unsupported machine instruction ...
#endif

#define REX_FORCE_INLINE __forceinline