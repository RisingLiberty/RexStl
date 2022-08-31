// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_trivially_copyable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct is_trivially_copyable { static constexpr bool value = __is_trivially_copyable(T); };

    template <typename T>
    constexpr bool is_trivially_copyable_v = is_trivially_copyable::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsTriviallyCopyableStruct = is_trivially_copyable<T>;

    template <typename T>
    constexpr bool IsTriviallyCopyable = is_trivially_copyable<T>::value;
#endif
}
