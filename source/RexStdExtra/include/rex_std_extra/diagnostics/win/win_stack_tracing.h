// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_stack_tracing.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

class LineInfo
{
public:
  LineInfo();
  LineInfo(const rsl::StringView file_name, card32 line_nr);

  rsl::StringView file_name() const;
  card32 line_nr() const;

private:
  rsl::BigStackString m_file_name;
  card32 m_line_nr;
};

class StackPointer
{
public:
  StackPointer(void* ptr, const LineInfo& line_info, const BigStackString& undecorated_name, const TinyStackString& module_name);

  const TinyStackString& module_name() const;
  void* address() const;
  const BigStackString& file_name() const;
  const BigStackString& function_name() const;
  card32 line_nr() const;

private:
  rsl::BigStackString m_file_name;
  rsl::BigStackString m_function_name;
  rsl::TinyStackString m_module_name;
  void* m_address;
  card32 m_line_nr;
};

class CallStack
{
public:
  void add_pointer(const StackPointer& stack_ptr);
  void dump(const rsl::StringView file_name = "callstack_dump.txt");

private:
  vector<StackPointer> m_stack_pointers;
};

CallStack stack_trace(card32 frames_to_skip = 0); // stack trace max 100 stack deep
StackPointer prev_func_call();                    // get the previous function call (useful for source location)

REX_RSL_END_NAMESPACE