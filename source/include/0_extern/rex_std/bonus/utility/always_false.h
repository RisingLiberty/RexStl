// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: always_false.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T>
  constexpr bool always_false = false;
} // namespace internal

REX_RSL_END_NAMESPACE