// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: flags.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl { inline namespace v1 {

template <typename T = card32>
T no_flags()
{
  return 0;
}

}}