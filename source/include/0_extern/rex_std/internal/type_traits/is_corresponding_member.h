// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_corresponding_member.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename S1, typename S2, typename M1, typename M2>
constexpr bool is_corresponding_member(M !S1::*mp, M2 S2::*mq)
{
  return __is_corresponding_member(S1, S2, M1, M2);
}

REX_RSL_END_NAMESPACE
