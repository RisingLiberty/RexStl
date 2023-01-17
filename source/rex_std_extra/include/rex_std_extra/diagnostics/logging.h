// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: logging.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std_extra/diagnostics/console_colors.h"
#include "rex_std_extra/diagnostics/win/win_console.h"

REX_RSL_BEGIN_NAMESPACE

StringView seperator();

REX_RSL_END_NAMESPACE

#ifndef LOGGER_NAME
  #define LOGGER_NAME_OUTPUT ""
#else
  #define LOGGER_NAME_OUTPUT LOGGER_NAME ": "
#endif

#ifdef REX_ENABLE_LOGGING
  #define REX_INFO(...) rsl::console().log_line(rsl::console_colors::Info, LOGGER_NAME_OUTPUT, __VA_ARGS__)

  #ifndef REX_TREAT_WARNINGS_AS_ERRORS
    #define REX_WARN(...) rsl::console().log_line(rsl::console_colors::Warning, LOGGER_NAME_OUTPUT, __VA_ARGS__)
  #else
    #define REX_WARN(...) rsl::console().log_line(rsl::console_colors::Warning, LOGGER_NAME_OUTPUT, __VA_ARGS__)
  #endif

  #ifndef REX_TREAT_ERRORS_AS_FATAL
    #define REX_ERROR(...) rsl::console().log_line(rsl::console_colors::Error, LOGGER_NAME_OUTPUT, __VA_ARGS__)
  #else
    #define REX_ERROR(...) rsl::console().log_line(rsl::console_colors::Error, LOGGER_NAME_OUTPUT, __VA_ARGS__)
  #endif

  #define REX_LOG_SPECIAL(color, ...) rsl::console().log_line(color, LOGGER_NAME_OUTPUT, __VA_ARGS__)

  #define REX_TODO(...)                                                                                                                                                                                                                                  \
    rsl::console().log_line(rsl::console_colors::Todo, LOGGER_NAME_OUTPUT, "TODO: ", __VA_ARGS__);                                                                                                                                                       \
    rsl::console().log_line(rsl::console_colors::Todo, LOGGER_NAME_OUTPUT, __FUNCTION__, " Line: ", __LINE__);                                                                                                                                           \
    rsl::console().log_line(rsl::console_colors::Todo, LOGGER_NAME_OUTPUT, __FILE__)

  #define REX_TODO_ONCE(...)                                                                                                                                                                                                                             \
    const char8* func_sig = __FUNCTION__ REX_EXECUTE_ONCE(rsl::console().log_line(rsl::console_colors::Todo, LOGGER_NAME_OUTPUT, "TODO: ", __VA_ARGS__);                                                                                                 \
                                                          rsl::console().log_line(rsl::console_colors::Todo, LOGGER_NAME_OUTPUT, __FUNCTION__, " Line: ", __LINE__); rsl::console().log_line(rsl::console_colors::Todo, LOGGER_NAME_OUTPUT, __FILE__));

  #define REX_INFO_X(condition, ...)                                                                                                                                                                                                                     \
    if(!(condition))                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      CA_INFO(__VA_ARGS__);                                                                                                                                                                                                                              \
    }
  #define REX_WARN_X(condition, ...)                                                                                                                                                                                                                     \
    if(!(condition))                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      CA_WARN(__VA_ARGS__);                                                                                                                                                                                                                              \
    }
  #define REX_ERROR_X(condition, ...)                                                                                                                                                                                                                    \
    if(!(condition))                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      CA_ERROR(__VA_ARGS__);                                                                                                                                                                                                                             \
    }

  #define REX_LOG_NEW_LINE()         rsl::console().log("\n");
  #define REX_LOG_SEPERATOR(color)   rsl::console().log_line(color, rsl::seperator())
  #define REX_LOG_VARIABLE(variable) REX_INFO(#variable, ": ", variable)

#else

  #define REX_TODO(...)                                                                                                                                                                                                                                  \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_TODO_ONCE(...)                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_INFO(...)                                                                                                                                                                                                                                  \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_WARN(...)                                                                                                                                                                                                                                  \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_ERROR(...)                                                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_LOG_SEPCIAL(...)                                                                                                                                                                                                                           \
    {                                                                                                                                                                                                                                                    \
    }

  #define REX_INFO_X(...)                                                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_WARN_X(...)                                                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_ERROR_X(...)                                                                                                                                                                                                                               \
    {                                                                                                                                                                                                                                                    \
    }

  #define REX_LOG_NEW_LINE(...)                                                                                                                                                                                                                          \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_LOG_SEPERATOR(...)                                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_LOG_VARIABLE(...)                                                                                                                                                                                                                          \
    {                                                                                                                                                                                                                                                    \
    }

#endif

#if defined(REX_ENABLE_LOGGING) && defined(REX_ENABLE_TRACE_LOGGING)
  #define REX_TRACE(...) rsl::console().log_line(rsl::console_colors::Trace, LOGGER_NAME_OUTPUT, __VA_ARGS__)
  #define REX_TRACE_X(condition, ...)                                                                                                                                                                                                                    \
    if(!(condition))                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      REX_TRACE(__VA_ARGS__);                                                                                                                                                                                                                            \
    }
#else
  #define REX_TRACE(...)                                                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_TRACE_X(...)                                                                                                                                                                                                                               \
    {                                                                                                                                                                                                                                                    \
    }
#endif

#if defined(REX_ENABLE_LOGGING) && defined(REX_ENABLE_DEBUG_LOGGING)
  #define REX_DEBUG(...) rsl::console().log_line(rsl::console_colors::Debug, LOGGER_NAME_OUTPUT, __VA_ARGS__)
  #define REX_DEBUG_X(condition, ...)                                                                                                                                                                                                                    \
    if(!(condition))                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      REX_DEBUG(__VA_ARGS__);                                                                                                                                                                                                                            \
    }
#else
  #define REX_DEBUG(...)                                                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                                                    \
    }
  #define REX_DEBUG_X(...)                                                                                                                                                                                                                               \
    {                                                                                                                                                                                                                                                    \
    }
#endif