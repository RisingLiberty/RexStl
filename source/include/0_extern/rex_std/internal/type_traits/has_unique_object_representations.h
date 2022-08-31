// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: has_unique_object_representations.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/remove_cv.h"
#include "rex_std/internal/type_traits/remove_all_extents.h"

namespace rsl
{
    template <typename T>
	struct has_unique_object_representations : public bool_constant<__has_unique_object_representations(remove_cv_t<remove_all_extents_t<T>>)>
	{};

    template <typename T>
    constexpr bool has_unique_object_representations_v = has_unique_object_representations<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using HasUniqueObjectRepresentationsStruct = has_unique_object_representations<T>;

    template <typename T>
    constexpr bool HasUniqueObjectRepresentations = HasUniqueObjectRepresentationsStruct<T>::value;
#endif
}