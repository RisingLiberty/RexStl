// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: iter_val.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_traits.h"

REX_RSL_BEGIN_NAMESPACE

template <typename InputIt>
using iter_val_t = typename iterator_traits<InputIt>::value_type::value_type;

REX_RSL_END_NAMESPACE