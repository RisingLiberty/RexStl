// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: open_flags.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

enum class OpenFlags
{
  Read         = (1 << 0),
  Write        = (1 << 1),
  ReadWrite    = (Read | Write),
  Trunc        = (1 << 2),
  App          = (1 << 3),
  OpenExisting = (1 << 4),
};

OpenFlags operator|(const OpenFlags lhs, const OpenFlags rhs);
bool operator&(const OpenFlags lhs, const OpenFlags rhs);

REX_RSL_END_NAMESPACE