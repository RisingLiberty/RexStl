// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: common_reference.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/returns_exactly.h"
#include "rex_std/internal/type_traits/common_type.h"
#include "rex_std/internal/type_traits/remove_cvref.h"
#include "rex_std/internal/type_traits/void.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/is_lvalue_reference.h"
#include "rex_std/internal/type_traits/is_convertible.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename ...>
    struct common_reference
    {};

    template <typename ... Types>
    using common_reference_t = common_reference<Types>::type;

    template<>
    struct common_reference<>
    {};

    template <typename T>
    struct common_reference<T>
    {
        using type = T;
    };

    namespace internal
    {
        template <typename T1, typename T2>
        using CondRes = decltype(false ? returns_exactly<T1>() : returns_exactly<T2>());
        
        template <typename T1, typename T2, typename = void>
        struct CommonReference2C : common_type<T1, T2>
        {};

        template <typename T1, typename T2>
        struct CommonReference2C<T1, T2, void_t<CondRes<T1, T2>>>
        {
            using type = CondRes<T1, T2>;
        };

        template <typename, typename, template <typename> typename, template <typename> typename>
        struct BasicCommonReference {};

        template <typename From>
        struct CopyCVImpl 
        {
            template <typename To>
            using Apply = To;
        };
        template <typename From>
        struct CopyCVImpl<const From> 
        {
            template <typename To>
            using Apply = const To;
        };
        template <typename From>
        struct CopyCVImpl<volatile From> 
        {
            template <typename To>
            using Apply = volatile To;
        };
        template <typename From>
        struct CopyCVImpl<const volatile From> 
        {
            template <typename To>
            using Apply = const volatile To;
        };

        template <typename From, typename To>
        using CopyCV = typename CopyCVImpl<From>::template Apply<To>;

        template <typename T1>
        struct AddQualifiers
        {
            template <typename T2>
            using Apply = CopyCV<T1, T2>;
        };
        template <typename T1>
        struct AddQualifiers<T1&>
        {
            template <typename T2>
            using Apply = add_lvalue_reference_t<CopyCV<T1, T2>>;
        };
        template <typename T1>
        struct AddQualifiers<T1&&>
        {
            template <typename T2>
            using Apply = add_rvalue_reference_t<CopyCV<T1, T2>>; 
        };

        template <typename T1, typename T2>
        using BasicSpecialization = typename BasicCommonReference<
        RemoveCVRef<T1>, 
        RemoveCVRef<T2>, 
        AddQualifiers<T1>::template Apply, 
        AddQualifiers<T2>::template Apply>::type;

        template <typename T1, typename T2, typename = void>
        struct CommonReference2B : CommonReference2C<T1, T2>
        {};

        template <typename T1, typename T2>
        struct CommonReference2B<T1, T2, void_t<BasicSpecialization<T1, T2>>>
        {
            using type = BasicSpecialization<T1, T2>;
        };

        template <typename T1, typename T2, class = void>
        struct CommonReference2A : CommonReference2B<T1, T2>
        {};

        template <typename T1, typename T2, typename Result = CondRes<CopyCV<T1, T2>&, CopyCV<T2, T1>&>, enable_if_t<is_lvalue_reference_v<Result>, bool> = true>
        using LLCommonRef = Result;

        template <typename T1, typename T2>
        struct CommonReference2A<T1&, T2&, void_t<LLCommonRef<T1, T2>>>
        {
            using type = LLCommonRef<T1, T2>;
        };

        template <typename T1, typename T2>
        struct CommonReference2A<T1&&, T2&&, enable_if_t<is_convertible_v<T1&&, LLCommonRef<const T1, T2>>>>
        {
            using type = LLCommonRef<const T1, T2>;
        };

        template <typename T1, typename T2>
        struct CommonReference2A<T1&, T2&&, enable_if_t<is_convertible_v<T2&&, LLCommonRef<const T2, T1>>>>
        {
            using type = LLCommonRef<const T2, T1>;
        };

        template <typename T1, typename T2>
        using RRCommonRef = remove_reference_t<LLCommonRef<T1, T2>>&&;

        template <typename T1, typename T2>
        struct CommonReference2A<T1&&, T2&&, enable_if_t<is_convertible_v<T1&&, RRCommonRef<T1, T2>> && is_convertible_v<T2&&, RRCommonRef<T1, T2>>>>
        {
            using type = RRCommonRef<T1, T2>;
        };
        
        template <typename void_t, typename T1, typename T2, typename ... Ts>
        struct FoldCommonReference {};

        template <typename T1, typename T2, typename ... Ts>
        struct FoldCommonReference<void_t<common_reference_t<T1, T2>>, T1, T2, Ts...> : common_reference<common_reference_t<T1, T2>, Ts...>
        {};
    }

    template <typename T1, typename T2>
    struct common_reference<T1, T2> : internal::CommonReference2A<T1, T2>
    {};
    
    template <typename T1, typename T2, typename T3, typename ... Rest>
    struct common_reference<T1, T2, T3, Rest...> : internal::FoldCommonReference<void, T1, T2, T3, Rest...>
    {};
    
REX_RSL_END_NAMESPACE
