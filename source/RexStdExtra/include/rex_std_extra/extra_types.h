// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: extra_types.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "utilities/strong_type.h"

REX_RSL_BEGIN_NAMESPACE

inline namespace extra
{
  REX_CREATE_STRONG_TYPE(Capacity, card32);
  REX_CREATE_STRONG_TYPE(Size, card32);
} // namespace extra

REX_RSL_END_NAMESPACE

CREATE_LITERAL_FOR_STRONG_TYPE(rsl::Capacity, _cap);
CREATE_LITERAL_FOR_STRONG_TYPE(rsl::Size, _size);