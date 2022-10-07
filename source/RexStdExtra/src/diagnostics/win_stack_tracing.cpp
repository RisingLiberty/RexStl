// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_stack_tracing.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/diagnostics/win/win_stack_tracing.h"

#include "rex_std_extra/diagnostics/win/win_call.h"
#include "rex_std_extra/filesystem/filepath.h"
#include "rex_std_extra/filesystem/win/win_file.h"
#include "rex_std_extra/filesystem/win/win_virtual_file_system.h"
#include "rex_std_extra/memory/memory_size.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

#include <DbgHelp.h>
#include <windows.h>

REX_RSL_BEGIN_NAMESPACE

BOOL CALLBACK symbol_callback(HANDLE /*hProcess*/, ULONG /*action_code*/, ULONG64 /*callback_data*/, ULONG64 /*user_context*/)
{
  // Nothing to implement
  return 0;
}

void log_symbol_search_path()
{
  char buffer[4_kib] = {};
  SymGetSearchPath(GetCurrentProcess(), buffer, sizeof(buffer));

  REX_INFO("Symbol search paths:");
  String path;
  card32 start = 0;
  card32 end   = 0;
  card32 i     = 0;
  for(; i < 4_kib; ++i)
  {
    if(buffer[i] == '\0')
      break;

    if(buffer[i] == ';')
    {
      end = i;
      path.resize(end - start);
      rsl::memcpy(path.data(), &buffer[start], end - start);
      REX_INFO(path);
      start = end;
      ++start;
    }

    ++end;
  }

  path.resize(end - start);
  rsl::memcpy(path.data(), &buffer[start + i], end - start);
}

bool load_symbols()
{
  static bool initialised = false;
  if(!initialised)
  {
    SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_EXACT_SYMBOLS | SYMOPT_LOAD_LINES | SYMOPT_DEBUG | SYMOPT_UNDNAME);
    if(!SymInitialize(GetCurrentProcess(), NULL, TRUE))
    {
      SymCleanup(GetCurrentProcess());
    }

    SymRegisterCallback64(GetCurrentProcess(), symbol_callback, NULL);
  }
  return initialised;
}

// no inline because we'll skip this stack frame when tracking the callstack
__declspec(noinline) rsl::Array<void*, 100> load_stack_pointers(card32 frames_to_skip)
{
  rsl::Array<void*, 100> stack_pointers;
  const card32 FramesToSkip = frames_to_skip + 2;

  CaptureStackBackTrace(FramesToSkip, (DWORD)stack_pointers.size(), stack_pointers.data(), NULL);

  return stack_pointers;
}

rsl::LineInfo get_stack_pointer_line_info(HANDLE process, card64 addr, DWORD64* displacement)
{
  IMAGEHLP_LINE64 line;
  if(WIN_SUCCESS(SymGetLineFromAddr64(process, addr, (DWORD*)displacement, &line)))
  {
    return {rsl::BigStackString(line.FileName), static_cast<card32>(line.LineNumber)};
  }
  else
  {
    return {rsl::BigStackString("Unable to retrive file name"), -1};
  }
}

rsl::BigStackString get_undecorated_name(const char* symbol_name)
{
  char undecorated_name[MAX_SYM_NAME];
  UnDecorateSymbolName(symbol_name, undecorated_name, MAX_SYM_NAME, UNDNAME_COMPLETE);
  return rsl::BigStackString(undecorated_name);
}

rsl::TinyStackString get_module_name(HANDLE process, card64 addr)
{
  IMAGEHLP_MODULE64 module = {sizeof(IMAGEHLP_MODULE64)};

  return SymGetModuleInfo64(process, addr, &module) ? rsl::TinyStackString(module.ModuleName) : ""_tiny;
}

REX_RSL_END_NAMESPACE

rsl::LineInfo::LineInfo() = default;
rsl::LineInfo::LineInfo(const StringView file_name, card32 line_nr)
    : m_file_name(file_name)
    , m_line_nr(line_nr)
{
}

rsl::StringView rsl::LineInfo::file_name() const
{
  return m_file_name;
}
card32 rsl::LineInfo::line_nr() const
{
  return m_line_nr;
}

rsl::StackPointer::StackPointer(void* ptr, const LineInfo& line_info, const BigStackString& undecorated_name, const TinyStackString& module_name)
    : m_file_name(line_info.file_name())
    , m_function_name(undecorated_name)
    , m_module_name(module_name)
    , m_address(ptr)
    , m_line_nr(line_info.line_nr())
{
}

const rsl::TinyStackString& rsl::StackPointer::module_name() const
{
  return m_module_name;
}
void* rsl::StackPointer::address() const
{
  return m_address;
}
const rsl::BigStackString& rsl::StackPointer::file_name() const
{
  return m_file_name;
}
const rsl::BigStackString& rsl::StackPointer::function_name() const
{
  return m_function_name;
}
card32 rsl::StackPointer::line_nr() const
{
  return m_line_nr;
}

void rsl::CallStack::add_pointer(const StackPointer& stack_ptr)
{
  m_stack_pointers.push_back(stack_ptr);
}
void rsl::CallStack::dump(const rsl::StringView file_name)
{
  const Path dump_folder = "debug";

  if(!rsl::vfs::does_exist(dump_folder))
  {
    rsl::vfs::create_directory(dump_folder);
  }

  rsl::Path path = dump_folder / file_name;
  rsl::OFile dump_file(path);

  if(m_stack_pointers.empty())
  {
    dump_file << "<< No frame pointers to show >>";
  }

  for(const StackPointer& stack_ptr: m_stack_pointers)
  {
    dump_file << "MODULE: " << stack_ptr.module_name() << "\n";
    dump_file << "ADDRESS: " << stack_ptr.address() << "\n";
    dump_file << "FILE NAME: " << stack_ptr.file_name() << "\n";
    dump_file << "FUNTION: " << stack_ptr.function_name() << "\n";
    dump_file << "LINE: " << stack_ptr.line_nr() << "\n";
    dump_file << "\n";
  }
}

__declspec(noinline) rsl::CallStack rsl::stack_trace(card32 frames_to_skip)
{
  static bool initialised = load_symbols();

  rsl::Array<void*, 100> stack_pointers = load_stack_pointers(frames_to_skip);

  HANDLE process       = GetCurrentProcess();
  DWORD64 displacement = 0;
  ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
  PSYMBOL_INFO symbol_info = (PSYMBOL_INFO)buffer;
  IMAGEHLP_LINE64 line     = {sizeof(IMAGEHLP_LINE64)};

  symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
  symbol_info->MaxNameLen   = MAX_SYM_NAME;

  CallStack call_stack;

  for(card32 i = 0; i < stack_pointers.size() && stack_pointers[i] != nullptr; ++i)
  {
    void* stack_ptr = stack_pointers[i];
    uint64_t addr   = (uint64_t)stack_ptr;
    rsl::LineInfo line_info;
    rsl::BigStackString undecorated_name;

    if(SymFromAddr(process, addr, &displacement, symbol_info))
    {
      line_info        = get_stack_pointer_line_info(process, addr, &displacement);
      undecorated_name = get_undecorated_name(symbol_info->Name);
    }
    rsl::TinyStackString module_info = get_module_name(process, addr);

    if((intptr_t)stack_ptr != 0xcccccccc)
    {
      call_stack.add_pointer({stack_ptr, line_info, undecorated_name, module_info});
    }
  }

  return call_stack;
}

__declspec(noinline) rsl::StackPointer rsl::prev_func_call()
{
  static bool initialised = load_symbols();

  void* stack_ptr;
  card32 frames_to_skip = 2;
  CaptureStackBackTrace(frames_to_skip, (DWORD)1, &stack_ptr, NULL);

  HANDLE process       = GetCurrentProcess();
  DWORD64 displacement = 0;
  ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
  PSYMBOL_INFO symbol_info = (PSYMBOL_INFO)buffer;
  IMAGEHLP_LINE64 line     = {sizeof(IMAGEHLP_LINE64)};

  symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
  symbol_info->MaxNameLen   = MAX_SYM_NAME;

  uint64_t addr = (uint64_t)stack_ptr;
  rsl::LineInfo line_info;
  rsl::BigStackString undecorated_name;

  if(SymFromAddr(process, addr, &displacement, symbol_info))
  {
    line_info        = get_stack_pointer_line_info(process, addr, &displacement);
    undecorated_name = get_undecorated_name(symbol_info->Name);
  }
  rsl::TinyStackString module_info = get_module_name(process, addr);

  return StackPointer {stack_ptr, line_info, undecorated_name, module_info};
}