// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: void.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename ... Args>
    using void_t = void;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename ... Args>
    using Void = void;
#endif
}
