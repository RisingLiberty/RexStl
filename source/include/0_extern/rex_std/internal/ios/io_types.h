// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: io_types.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/io/streamoff
// https://en.cppreference.com/w/cpp/io/streamsize
//
// streamoff -> type of sufficient size to represent the maximum possible file size.
// streamsize -> represent the number of characters transferred in an I/O operation
// or the size of an I/O buffer
//-----------------------------------------------------------------------------

#pragma once

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

using streamoff  = card32;
using streamsize = count_t;

using wint_t = int32;

REX_RSL_END_NAMESPACE