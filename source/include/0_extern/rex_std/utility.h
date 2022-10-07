// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: utility.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "compare.h"
#include "initializer_list.h"
#include "internal/utility/exchange.h"
#include "internal/utility/forward.h"
#include "internal/utility/move.h"
#include "rex_std/bonus/defines.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename... Ts>
    class tuple;

  }
} // namespace rsl

#include "rex_std/enable_std_checking.h"

#include <utility>