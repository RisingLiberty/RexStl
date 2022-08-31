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

namespace rsl
{
    template <typename InputIt>
    using iter_key_t = typename remove_const_t<typename iterator_traits<InputIt>::value_type>::key_type;
    template <typename InputIt>
    using iter_val_t = typename iterator_traits<InputIt>::value_type::value_type;
}