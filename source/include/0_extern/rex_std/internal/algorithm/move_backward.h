// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: move_backward.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/utility/move.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename InputIterator, typename OutputIterator>
    OutputIterator move_backward(InputIterator first, InputIterator last, OutputIterator dst_last)
    {
        while (first != last)
        {
            *--dst_last = rsl::move(*--last);
        }

        // dst_last now points to the beginning of the destination sequence instead of the end.
        return dst_last; 
    }

REX_RSL_END_NAMESPACE
