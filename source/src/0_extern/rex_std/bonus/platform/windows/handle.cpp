// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: handle.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/platform/windows/handle.h"

#include <Windows.h>

REX_RSL_BEGIN_NAMESPACE
namespace win
{
  static_assert(sizeof(HANDLE) == sizeof(handle_t), "Rex internal handle should be the same as Windows' HANDLE");
    
    handle::handle()
        : m_handle(invalid_value())
    {}
    handle::handle(handle_t handle)
        : m_handle(handle)
    {}

    handle::~handle()
    {
        CloseHandle(m_handle);
    }

    bool handle::is_valid() const
    {
        return m_handle != invalid_value();
    }
    handle::operator bool() const
    {
        return is_valid();
    }

    handle_t handle::invalid_value()
    {
        return INVALID_HANDLE_VALUE;
    }
}
REX_RSL_END_NAMESPACE