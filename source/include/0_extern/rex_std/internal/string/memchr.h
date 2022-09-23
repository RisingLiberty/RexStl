// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: memchr.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

void* memchr(const void* ptr, char8 ch, card32 length);

REX_RSL_END_NAMESPACE
