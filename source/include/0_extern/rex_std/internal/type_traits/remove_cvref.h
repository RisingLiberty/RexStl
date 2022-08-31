// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_cvref.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/remove_cv.h"
#include "rex_std/internal/type_traits/remove_reference.h"

namespace rsl
{
    namespace internal
    {
        template <typename T>
        using RemoveCVRefHelper = remove_cv_t<remove_reference_t<T>>;
    }

    template <typename T>
    using remove_cv_ref_t = internal::RemoveCVRefHelper<T>;

    template <typename T>
    struct remove_cv_ref
    {
        using type = remove_cv_ref_t<T>;
    };

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using RemoveCVRefStruct = remove_cv_ref<T>;

    template <typename T>
    using RemoveCVRef = typename remove_cv_ref<T>::type;
#endif
}