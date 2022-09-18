// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_member_function_pointer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_function.h"
#include "rex_std/internal/type_traits/remove_cv.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        template <typename T>
        struct IsMemberFunctionPointerHelper : false_type
        {};

        template <typename T, typename U>
        struct IsMemberFunctionPointerHelper<T U::*> : is_function<T>{};
    }
  
    template <typename T>
    struct is_member_function_pointer : public bool_constant < internal::IsMemberFunctionPointerHelper<remove_cv_t<T>>::value >
    {};

    template <typename T>
    constexpr bool is_member_function_pointer_v =is_member_function_pointer<T>::value;

REX_RSL_END_NAMESPACE
