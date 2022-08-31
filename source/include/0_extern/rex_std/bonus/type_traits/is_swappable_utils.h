// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_swappable_utils.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    namespace internal
    {
        struct ArgumentSink
        {
            template <typename ... Args>
            ArgumentSink(Args&&...) {}
        };

        Unused swap(ArgumentSink, ArgumentSink);

    }
}