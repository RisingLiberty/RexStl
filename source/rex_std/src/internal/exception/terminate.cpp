// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: terminate.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/exception/teminate.h"

#include "rex_std/internal/exception/abort.h"

namespace rsl
{
  inline namespace v1
  {
    void terminate()
    {
      abort();
    }
  }
}