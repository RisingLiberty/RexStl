// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_member_pointer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/remove_cv.h"

namespace rsl
{
	namespace internal
	{
        template <typename>
        struct IsMemberPointerHelper : public false_type { };

        template <typename T, typename U>
        struct IsMemberPointerHelper<T U::*> : public true_type { };
    }

	template <typename T>
	struct is_member_pointer : public internal::IsMemberPointerHelper<remove_cv_t<T>>::type
	{};

    template <typename T>
    constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsMemberPointerStruct = is_member_pointer<T>;

    template <typename T>
    constexpr bool IsMemberPointer = IsMemberPointerStruct<T>::value;
#endif
}
