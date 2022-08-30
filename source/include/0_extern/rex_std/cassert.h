// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: cassert.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/bonus/defines.h"

#include "rex_std/internal/assert/assert_system.h"
#include "rex_std/internal/type_traits/type_identity.h"

/// RSL Comment: Different from ISO C++ Standard at time of writing (07/Aug/2022)
// the standard only provides 1 assert macro: "assert(...)"
// rex provides a few, depending on the severity of the error/assert

namespace rsl
{
#ifdef REX_ENABLE_ASSERTS

    #define REX_ASSERT_IMPL(/*severity*/, expr, ...) \
    [&, function_sig = __FUNCSIG__]()\
    {                           \
    if (expr)                 \
    {                         \
        return false;            \
    }                         \
                                \
    __debugbreak();              \
    }()

    #define REX_INFO_X(expr, ...) REX_ASSERT_IMPL(::rsl::Severity::Info, expr, __VA_ARGS__)
    #define REX_WARN_X(expr, ...)  REX_ASSERT_IMPL(::rsl::Severity::Warning, expr, __VA_ARGS__)
    #define REX_ERROR_X(expr, ...) REX_ASSERT_IMPL(::rsl::Severity::Error, expr, __VA_ARGS__)
    #define REX_ASSERT_X(expr, ...) REX_ASSERT_IMPL(::rsl::Severity::Fatal, expr, __VA_ARGS__)

    #define REX_INFO(...) REX_ASSERT_IMPL(::rsl::Severity::Info, false, __VA_ARGS__)
    #define REX_WARN(...)  REX_ASSERT_IMPL(::rsl::Severity::Warning, false, __VA_ARGS__)
    #define REX_ERROR(...) REX_ASSERT_IMPL(::rsl::Severity::Error, false, __VA_ARGS__)
    #define REX_ASSERT(...) REX_ASSERT_IMPL(::rsl::Severity::Fatal, false, __VA_ARGS__)

    #define DECLARE_ASSERT_CONTEXT(name) ::rsl::ScopedAssertContext ANONYMOUS_VARIABLE(assert_context) (name)

#else
#define REX_INFO_X(expr, ...) false
#define REX_WARN_X(expr, ...)  false
#define REX_ERROR_X(expr, ...) false
#define REX_ASSERT_X(expr, ...) false

#define REX_INFO(...) false
#define REX_WARN(...)  false
#define REX_ERROR(...) false
#define REX_ASSERT(...) false

#define DECLARE_ASSERT_CONTEXT(name)

#endif
#ifdef REX_ENABLE_DEBUG_BREAK
    #define REX_DEBUG_BREAK() __debugbreak()
    #define REX_BREAK_IF(expr) \
    if ((expr))             \
    {                       \
        REX_DEBUG_BREAK();  \
    }                       
#else
    #define REX_DEBUG_BREAK()
    #define REX_BREAK_IF(expr)
#endif
}