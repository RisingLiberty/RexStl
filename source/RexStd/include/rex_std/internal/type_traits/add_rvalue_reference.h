// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: add_rvalue_reference.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/add_reference.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct add_rvalue_reference
    {
      using type = typename bonus::add_reference<T>::rvalue;
    };

    template <typename T>
    using add_rvalue_reference_t = typename bonus::add_reference<T>::rvalue;

  } // namespace v1
} // namespace rsl
