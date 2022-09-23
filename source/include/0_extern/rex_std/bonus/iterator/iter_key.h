// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: iter_key.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename InputIt>
using iter_key_t = typename remove_const_t<typename iterator_traits<InputIt>::value_type>::key_type;

REX_RSL_END_NAMESPACE