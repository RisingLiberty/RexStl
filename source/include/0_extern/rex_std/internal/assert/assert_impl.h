// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: assert_impl.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// Implementation of the assert function. This is implemented in a different file
// to avoid circular inclusion issues.
//-----------------------------------------------------------------------------

#pragma once

REX_RSL_BEGIN_NAMESPACE

  template <typename ... Args>
  bool assert(bool cond, Args&& ... args)
  {
    return false;
  }

REX_RSL_END_NAMESPACE