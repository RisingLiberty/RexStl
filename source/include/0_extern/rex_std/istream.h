// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: istream.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/istream/basic_istream.h"

REX_RSL_BEGIN_NAMESPACE

using istream  = basic_istream<char8>;
using wistream = basic_istream<tchar>;

REX_RSL_END_NAMESPACE
