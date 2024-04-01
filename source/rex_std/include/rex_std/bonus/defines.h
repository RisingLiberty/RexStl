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

#define RSL_UNUSED(x) (void)x

#define RSL_STRINGIZE(x)  RSL_STRINGIZE2(x)
#define RSL_STRINGIZE2(x) #x

#define RSL_LINE_TO_STRING(L) #L
#define RSL_CALL_MACRO(M, L)  M(L)

#ifdef RSL_COMPILER_CLANG
  #define RSL_STATIC_WARNING(expr)
#else
  #define RSL_THIS_LINE             RSL_CALL_MACRO(RSL_STRINGIZE2, __LINE__)
  #define RSL_STATIC_WARNING_PREFIX __FILE__ "(" RSL_THIS_LINE "): [WARNING] "
  #define RSL_STATIC_WARNING(expr)  __pragma(message(RSL_STATIC_WARNING_PREFIX##expr))
#endif

#ifdef RSL_COMPILER_CLANG
  #define RSL_STATIC_INFO(expr)
#else
  #define RSL_STATIC_INFO_PREFIX __FILE__ "(" THIS_LINE "): [INFO] "
  #define RSL_STATIC_INFO(expr)  __pragma(message(RSL_STATIC_INFO_PREFIX##expr))
#endif

#define RSL_MERGE(a, b)  RSL_MERGE1(a, b)
#define RSL_MERGE1(a, b) RSL_MERGE2(a, b)
#define RSL_MERGE2(a, b) a##b

#define RSL_FUNC_SIGNATURE __FUNCSIG__

#ifdef __COUNTER__
  #define RSL_ANONYMOUS_VARIABLE(str) RSL_MERGE(str, __COUNTER__)
#else
  #define RSL_ANONYMOUS_VARIABLE(str) RSL_MERGE(str, __LINE__)
#endif

#define RSL_EXECUTE_ONCE(expression)                                                                                                                                                                                                                         \
  static auto RSL_ANONYMOUS_VARIABLE(execute_once_var) = [&]()                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                      \
    expression;                                                                                                                                                                                                                                          \
    return 1;                                                                                                                                                                                                                                            \
  }();

#define RSL_TO_WIDE_STRING(str) L##str

#ifdef RSL_ENABLE_TODO_CHECKING
  #define RSL_STATIC_TODO(msg) static_assert(false, "TODO: ", msg);
#else
  #define RSL_STATIC_TODO(msg)
#endif

#if defined RSL_COMPILER_CLANG
  #define RSL_DEBUG_BREAK() __builtin_trap()
#elif defined RSL_COMPILER_MSVC
  #define RSL_DEBUG_BREAK() __debugbreak()
#else
  #error RSL_DEBUG_BREAK unsupported machine instruction ...
#endif

#define RSL_FORCE_INLINE __forceinline