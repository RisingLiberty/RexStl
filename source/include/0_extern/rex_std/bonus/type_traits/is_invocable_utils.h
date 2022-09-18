// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_invocable_utils.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/returns_exactly.h"

#include "rex_std/internal/type_traits/integral_constant.h"

#include "rex_std/internal/type_traits/is_void.h"
#include "rex_std/internal/type_traits/conjunction.h"
#include "rex_std/internal/type_traits/disjunction.h"
#include "rex_std/internal/type_traits/is_nothrow_convertible.h"

#include "rex_std/internal/utility/declval.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        template <typename void_t, typename Callable>
        struct InvokeTraitsZero
        {
            using is_invocable_v = false_type;
            using is_nothrow_invocable_v = false_type;
            template <typename Rx>
            using is_invocable_r_v = false_type;
            template <typename Rx>
            using is_nothrow_invocable_r_v = false_type;
        };

        template <typename From, typename To, typename = void>
        struct InvokeConvertible : public false_type
        {};

        template <typename From, typename To>
        struct InvokeConvertible<From, To, void_t<decltype(implicitly_convert_to<To>(returns_exactly<From>()))>> : true_type
        {};

        template <typename From, typename To>
        struct InvokeNothrowConvertible : bool_constant<noexcept(implicitly_convert_to<To>(returns_exactly<From>()))>
        {};

        template <typename Result, bool NoThrow>
        struct InvokeTraitsCommon
        {
            using type = Result;
            using is_invocable_v = true_type;
            using IsNothrowInvocable = bool_constant<NoThrow>;
            template <typename Rx>
            using InInvocableR = bool_constant<disjunction_t<is_void<Rx>, InvokeConvertible<type, Rx>>>;
            template <typename Rx>
            using is_nothrow_invocable_r_v = bool_constant<conjunction_v<IsNothrowInvocable, disjunction<is_void_v<Rx>, conjunction<InvokeConvertible<type, Rx>, InvokeNothrowConvertible<type, Rx>>>>>;
        };

        template <typename Void, typename ... Types>
        struct InvokeTraitsNonZero
        {
            using is_invocable = false_type;
            using is_nothrow_invocable = false_type;
            template <typename Rx>
            using is_invocable_r = false_type;
            template <typename Rx>
            using is_nothrow_invocable_r = false_type;
        };

        template <typename Callable>
        using DecltypeInvokeNonZero = decltype(declval<Callable>()());

        template <typename Callable>
        struct InvokeTraitsNonZero<void_t<DecltypeInvokeNonZero<Callable>>, Callable> : InvokeTraitsCommon<DecltypeInvokeNonZero<Callable>, noexcept(declval<Callable>()())>
        {};
            
        template <typename Callable, typename ... Args>
        using SelectInvokeTraits = conditional_t<sizeof...(Args) == 0, InvokeTraitsZero<void, Callable>, InvokeTraitsNonZero<void, Callable, Args...>>;
    }

REX_RSL_END_NAMESPACE
