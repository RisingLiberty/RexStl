// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: handle.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// This is a wrapper around Window's HANDLE structure.
// It enables RAII for HANDLE objects as well as some helper functions
//-----------------------------------------------------------------------------

#pragma once

#include "rex_std/bonus/defines.h"

REX_RSL_BEGIN_NAMESPACE
namespace win
{
    using handle_t = void*;

    class handle
    {
    public:
      handle();
      handle(handle_t handle);
      ~handle();

      bool is_valid() const;
      operator bool() const;

      static handle_t invalid_value();

    private:
      handle_t m_handle;
    };
}
REX_RSL_END_NAMESPACE
