// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stacktrace.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/stacktrace.h"

#include <Windows.h>
#include <DbgHelp.h>

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      BOOL CALLBACK symbol_callback(HANDLE /*hProcess*/, ULONG /*ActionCode*/, ULONG64 /*CallbackData*/, ULONG64 /*UserContext*/)
      {
        // Nothing to implement yet

        return 0;
      }

      bool load_symbols()
      {
        static bool initialised = false;
        if (!initialised)
        {
          SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_EXACT_SYMBOLS | SYMOPT_LOAD_LINES | SYMOPT_DEBUG | SYMOPT_UNDNAME);
          if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
          {
            SymCleanup(GetCurrentProcess());
          }

          SymRegisterCallback64(GetCurrentProcess(), symbol_callback, NULL);
        }

        return initialised;
      }

      // no inline because we'll skip this stack frame when tracking the callstack
      __declspec(noinline) rsl::array<void*, 100> load_stack_pointers(card32 framesToSkip)
      {
        rsl::array<void*, 100> stacks_pointers;
        card32 frames_to_skip = framesToSkip + 3;

        CaptureStackBackTrace(frames_to_skip, (DWORD)stacks_pointers.size(), stacks_pointers.data(), NULL);

        return stacks_pointers;
      }

      rsl::big_stack_string get_undecorated_name(const char* symbolName)
      {
        char undecorated_name[MAX_SYM_NAME];
        UnDecorateSymbolName(symbolName, &undecorated_name[0], MAX_SYM_NAME, UNDNAME_COMPLETE);
        return rsl::big_stack_string(undecorated_name);
      }

      stacktrace_entry get_stack_pointer_line_info(HANDLE process, card64 addr, DWORD64* displacement, const char* symbolName)
      {
        rsl::big_stack_string undecorated_name = get_undecorated_name(symbolName);

        IMAGEHLP_LINE64 line;
        if (SymGetLineFromAddr64(process, addr, (DWORD*)displacement, &line) == TRUE)
        {
          return stacktrace_entry(reinterpret_cast<void*>(addr), rsl::big_stack_string(line.FileName), undecorated_name, static_cast<card32>(line.LineNumber));
        }
        else
        {
          return stacktrace_entry(reinterpret_cast<void*>(addr), rsl::big_stack_string("Unable to retrieve file name"), rsl::big_stack_string("unable to retrive func name"), -1);
        }
      }

      rsl::tiny_stack_string get_module_name(HANDLE process, card64 addr)
      {
        IMAGEHLP_MODULE64	module = { sizeof(IMAGEHLP_MODULE64) };

        return SymGetModuleInfo64(process, addr, &module)
          ? rsl::tiny_stack_string(module.ModuleName)
          : ""_big;
      }

      __declspec(noinline) rsl::array<stacktrace_entry, 100> stack_trace(card32 skip, card32 maxDepth)
      {
        static bool			initialised = load_symbols();

        rsl::array<void*, 100> stack_pointers = load_stack_pointers(skip);

        HANDLE				process = GetCurrentProcess();
        DWORD64				displacement = 0;
        ULONG64				buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
        PSYMBOL_INFO		symbol_info = (PSYMBOL_INFO)buffer;
        IMAGEHLP_LINE64		line = { sizeof(IMAGEHLP_LINE64) };

        symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol_info->MaxNameLen = MAX_SYM_NAME;

        rsl::array<stacktrace_entry, 100> resolved_pointers = {};
        card32 maxCount = (rsl::min)(resolved_pointers.size(), maxDepth);
        for (card32 i = 0; i < maxCount && stack_pointers[i] != nullptr; ++i)
        {
          void* stack_ptr = stack_pointers[i];
          uint64_t addr = (uint64_t)stack_ptr;
          stacktrace_entry stack_entry;

          if (SymFromAddr(process, addr, &displacement, symbol_info))
          {
            stack_entry = get_stack_pointer_line_info(process, addr, &displacement, symbol_info->Name);
          }
          //rsl::tiny_stack_string module_info = get_module_name(process, addr);

          if ((intptr_t)stack_ptr != 0xcccccccc)
          {
            resolved_pointers[i] = stack_entry;
          }
        }

        return resolved_pointers;
      }
    }

    stacktrace_entry::stacktrace_entry(native_handle_type handle, const big_stack_string& file, const big_stack_string& func, card32 lineNr)
      : m_file(file)
      , m_function(func)
      , m_handle(handle)
      , m_line_nr(lineNr)
    {}

    bool operator==(const stacktrace_entry& lhs, const stacktrace_entry& rhs)
    {
      return lhs.native_handle() == rhs.native_handle();
    }
    bool operator!=(const stacktrace_entry& lhs, const stacktrace_entry& rhs)
    {
      return lhs.native_handle() != rhs.native_handle();
    }

    rsl::big_stack_string to_string(const stacktrace_entry& entry)
    {
      return entry.description();
    }
  }
}