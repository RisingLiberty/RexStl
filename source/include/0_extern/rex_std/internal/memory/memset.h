// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: memset.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

void* memset(void* dest, char val, count_t len);

REX_RSL_END_NAMESPACE
