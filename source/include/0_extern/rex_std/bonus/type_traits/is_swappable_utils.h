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

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  struct ArgumentSink
  {
    template <typename... Args>
    ArgumentSink(Args&&...)
    {
    }
  };

  Unused swap(ArgumentSink, ArgumentSink);

} // namespace internal

REX_RSL_END_NAMESPACE
