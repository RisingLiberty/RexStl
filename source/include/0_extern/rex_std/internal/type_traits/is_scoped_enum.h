// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_scoped_enum.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/type_traits/integral_constant.h"

#ifdef REX_ENABLE_WITH_CPP23

namespace rsl
{
    template <typename T>
    struct is_scoped_enum : public bool_constant<__is_scoped_enum(T)>
    {};

    template <typename T>
    constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsScopedEnumStruct = is_scoped_enum<T>;

    template <typename T>
    constexpr bool IsScopedEnum = IsScopedEnumStruct<T>::value;
#endif
}

#endif