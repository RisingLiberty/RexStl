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

// NOLINTBEGIN(llvm-include-order)
// clang-format off
#include <Windows.h> // this needs to be included before DbgHelp.h
#include <DbgHelp.h>
// clang-format on
// NOLINTEND(llvm-include-order)

// NOLINTBEGIN(modernize-use-nullptr)
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
        if(!initialised)
        {
          SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_EXACT_SYMBOLS | SYMOPT_LOAD_LINES | SYMOPT_DEBUG | SYMOPT_UNDNAME);
          if(SymInitialize(GetCurrentProcess(), NULL, TRUE) == 0)
          {
            SymCleanup(GetCurrentProcess());
          }

          SymRegisterCallback64(GetCurrentProcess(), symbol_callback, NULL);
          initialised = true;
        }

        return initialised;
      }

      // no inline because we'll skip this stack frame when tracking the callstack
      __declspec(noinline) rsl::array<void*, stacktrace::max_entries()> load_stack_pointers(card32 framesToSkip)
      {
        rsl::array<void*, stacktrace::max_entries()> stacks_pointers;
        const card32 frames_to_skip = framesToSkip + 3;

        CaptureStackBackTrace(frames_to_skip, static_cast<DWORD>(stacks_pointers.size()), stacks_pointers.data(), NULL);

        return stacks_pointers;
      }

      rsl::big_stack_string get_undecorated_name(const char* symbolName)
      {
        rsl::array<char, MAX_SYM_NAME> undecorated_name;
        UnDecorateSymbolName(symbolName, undecorated_name.data(), undecorated_name.size(), UNDNAME_COMPLETE);
        return rsl::big_stack_string(undecorated_name.data());
      }

      stacktrace_entry get_stack_pointer_line_info(HANDLE process, DWORD64 addr, DWORD64* displacement, const char* symbolName)
      {
        const rsl::big_stack_string undecorated_name = get_undecorated_name(symbolName);

        IMAGEHLP_LINE64 line = {sizeof(IMAGEHLP_LINE64)};
        if(SymGetLineFromAddr64(process, addr, reinterpret_cast<DWORD*>(displacement), &line) == TRUE) // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
        {
          return stacktrace_entry(reinterpret_cast<void*>(addr), rsl::big_stack_string(line.FileName), undecorated_name, static_cast<card32>(line.LineNumber)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
        }
        else
        {
          // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
          return stacktrace_entry(reinterpret_cast<void*>(addr), rsl::big_stack_string("Unable to retrieve file name"), rsl::big_stack_string("unable to retrieve func name"), -1);
          // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
        }
      }

      rsl::tiny_stack_string get_module_name(HANDLE process, card64 addr)
      {
        IMAGEHLP_MODULE64 module = {sizeof(IMAGEHLP_MODULE64)};

        return SymGetModuleInfo64(process, addr, &module) != 0 ? rsl::tiny_stack_string(module.ModuleName) : ""_tiny;
      }

      __declspec(noinline) rsl::array<stacktrace_entry, stacktrace::max_entries()> stack_trace(card32 skip, card32 maxDepth)
      {
        static const bool s_initialised = load_symbols();

        rsl::array<void*, stacktrace::max_entries()> stack_pointers = load_stack_pointers(skip);

        HANDLE process             = GetCurrentProcess();
        DWORD64 displacement       = 0;
        constexpr card32 buff_size = (sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64);
        rsl::array<ULONG64, buff_size> buffer;
        PSYMBOL_INFO symbol_info = reinterpret_cast<PSYMBOL_INFO>(buffer.data()); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

        symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol_info->MaxNameLen   = MAX_SYM_NAME;

        rsl::array<stacktrace_entry, stacktrace::max_entries()> resolved_pointers = {};
        const card32 max_count                              = (rsl::min)(resolved_pointers.size(), maxDepth);
        for(card32 i = 0; i < max_count && stack_pointers[i] != nullptr; ++i)
        {
          void* stack_ptr     = stack_pointers[i];
          const uint64_t addr = *reinterpret_cast<uint64_t*>(&stack_ptr); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
          stacktrace_entry stack_entry;

          if(SymFromAddr(process, addr, &displacement, symbol_info) != 0)
          {
            stack_entry = get_stack_pointer_line_info(process, addr, &displacement, symbol_info->Name);
          }

          // rsl::tiny_stack_string module_info = get_module_name(process, addr);

          if(addr != 0xcccccccc)
          {
            resolved_pointers[i] = stack_entry;
          }
        }

        return resolved_pointers;
      }
    } // namespace internal

    stacktrace_entry::stacktrace_entry()
        : m_file()
        , m_function()
        , m_handle(nullptr)
        , m_line_nr()
    {
    }

    stacktrace_entry::stacktrace_entry(native_handle_type handle, const big_stack_string& file, const big_stack_string& func, card32 lineNr)
        : m_file(file)
        , m_function(func)
        , m_handle(handle)
        , m_line_nr(lineNr)
    {
    }

    stacktrace_entry::native_handle_type stacktrace_entry::native_handle() const
    {
      return m_handle;
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Mar/2023)
    // This is implicit in the standard
    stacktrace_entry::operator bool() const
    {
      return m_handle != nullptr;
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Mar/2023)
    // This returns a std::string in the standard
    rsl::big_stack_string stacktrace_entry::description() const
    {
      rsl::big_stack_string result = ""_big;

      result += rsl::to_string(m_handle);
      result += " - ";
      result += m_file;
      result += "(";
      result += rsl::to_stack_string(m_line_nr);
      result += ") ";
      result += m_function;

      return result;
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Mar/2023)
    // This returns a std::string in the standard
    const rsl::big_stack_string& stacktrace_entry::source_file() const
    {
      return m_file;
    }
    card32 stacktrace_entry::source_line() const
    {
      return m_line_nr;
    }

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
  } // namespace v1
} // namespace rsl
// NOLINTEND(modernize-use-nullptr)
