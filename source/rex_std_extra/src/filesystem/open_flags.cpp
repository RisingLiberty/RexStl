// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: open_flags.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/filesystem/open_flags.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::OpenFlags rsl::operator|(const OpenFlags lhs, const OpenFlags rhs)
{
  card32 lhs_card = static_cast<card32>(lhs);
  card32 rhs_card = static_cast<card32>(rhs);

  return static_cast<OpenFlags>(lhs_card | rhs_card);
}
bool rsl::operator&(const OpenFlags lhs, const OpenFlags rhs)
{
  card32 lhs_card = static_cast<card32>(lhs);
  card32 rhs_card = static_cast<card32>(rhs);

  return lhs_card & rhs_card;
}
