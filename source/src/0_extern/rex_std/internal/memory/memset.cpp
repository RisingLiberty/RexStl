// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: memset.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/memory/memset.h"

namespace rsl
{
    void* memset(byte* dest, byte val, card32 len)
    {
        while (len-- > 0)
        {
            *dest++ = val;
        }
        return dest;
    }
}