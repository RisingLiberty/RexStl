// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: scopeguard.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include <functional>

REX_RSL_BEGIN_NAMESPACE

class ScopeGuard
{
public:
  ScopeGuard(rsl::function<void()> func);
  ~ScopeGuard();

  void release();

private:
  rsl::function<void()> m_function;
  bool m_is_released;
};

REX_RSL_END_NAMESPACE