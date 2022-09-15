// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: io_errc.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/io/io_errc
//
// Defines the error codes reported by I/O stream.
//-----------------------------------------------------------------------------

#pragma once

namespace rsl
{
    enum class io_errc
    {
        stream = 1
    };
}