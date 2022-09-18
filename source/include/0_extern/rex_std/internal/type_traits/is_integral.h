// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_integral.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/remove_cv.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        template <typename T>
        struct IsIntegralHelper : public false_type {};

        template <> struct IsIntegralHelper<int8> : public true_type {};
        template <> struct IsIntegralHelper<int16> : public true_type {};
        template <> struct IsIntegralHelper<int32> : public true_type {};
        template <> struct IsIntegralHelper<int64> : public true_type {};

        template <> struct IsIntegralHelper<uint8> : public true_type {};
        template <> struct IsIntegralHelper<uint16> : public true_type {};
        template <> struct IsIntegralHelper<uint32> : public true_type {};
        template <> struct IsIntegralHelper<uint64> : public true_type {};

        template <> struct IsIntegralHelper<bool> : public true_type {};
        template <> struct IsIntegralHelper<char8> : public true_type {};

        // other types that aren't really used by rex engine, but we still need regardless
        template <> struct IsIntegralHelper<tchar> : public true_type {};
        template <> struct IsIntegralHelper<char8_t> : public true_type {};
        template <> struct IsIntegralHelper<char16_t> : public true_type {};
        template <> struct IsIntegralHelper<char32_t> : public true_type {};

        template <> struct IsIntegralHelper<long> : public true_type {};
        template <> struct IsIntegralHelper<ulong> : public true_type {};
    }

    template <typename T>
    struct is_integral : public internal::IsIntegralHelper<typename remove_cv_t<T>> {};

    template <typename T>
    constexpr bool is_integral_v = is_integral<T>::value;

REX_RSL_END_NAMESPACE

