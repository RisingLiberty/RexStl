// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: id_generator.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/utilities/id_generator.h"

rsl::ID rsl::id_generator::new_id()
{
  static ID id = 0;
  return id++;
}
