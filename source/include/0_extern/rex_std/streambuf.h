// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: streambuf.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/streambuf/basic_streambuf.h"

REX_RSL_BEGIN_NAMESPACE

using streambuf  = basic_streambuf<char8>;
using wstreambuf = basic_streambuf<tchar>;

REX_RSL_END_NAMESPACE
