// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: make_signed.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/internal/type_traits/is_enum.h"
#include "rex_std/internal/type_traits/is_integral.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        template <typename T, bool = is_enum_v<T> || is_integral_v<T>>
        struct MakeSignedHelper0
        {
            struct CharHelper
            {
                using type = int8;
            };

            struct ShortHelper
            {
                using type = int16;
            };

            struct IntHelper
            {
                using type = int32;
            };

            struct LongHelper
            {
                using type = long;
            }

            struct LongLongHelper
            {
                using type = int64;
            }

            struct NoTypeHelper
            {};

            using type = conditional_t<
            sizeof(T) <= sizeof(int8), CharHelper,
            conditional_t<sizeof(T) <= sizeof(int16), ShortHelper,
            conditional_t<sizeof(T) <= sizeof(int32), IntHelper,
            conditional_t<sizeof(T) <= sizeof(long), LongHelper,
            conditional_t<sizeof(T) <= sizeof(int64), LongLongHelper,
            NoTypeHelper>>>>>::type;
            
            template <typename T>
            struct MakeSignedHelper0<T, false>
            {
                struct NoTypeHelper
                {};

                using type = NoTypeHelper;
            };

            template <typename T>
            struct MakeSignedHelper1
            {
                using type = typename T::type;
            };

            template <typename T>
            struct MakeSignedHelper
            {
                using type = typename MakeSignedHelper1<typename MakeSignedHelper0<T>::type>::type;
            };
        };
    }

    template <typename T>
    struct make_signed
    {
        using type = MakeSignedHelper<T>::type;
    };

    template <> struct make_signed<bool>     {};
    template <> struct make_signed<int8>     { using type = int8; };
    template <> struct make_signed<uint8>    { using type = int8; };
    template <> struct make_signed<int16>    { using type = int16; };
    template <> struct make_signed<uint16>   { using type = int16; };
    template <> struct make_signed<int32>    { using type = int32; };
    template <> struct make_signed<uint32>   { using type = int32; };
    template <> struct make_signed<int64>    { using type = int64; };
    template <> struct make_signed<uint64>   { using type = int64; };
    template <> struct make_signed<long>     { using type = long; };
    template <> struct make_signed<ulong>    { using type = long; };
    template <> struct make_signed<int64>   { using type = int64; };
    template <> struct make_signed<uint64>  { using type = int64; };

    template <> struct make_signed<char>  { using type = int8; };
    template <> struct make_signed<char8_t>  { using type = int8; };

    template <typename T>
    struct make_signed<const T>
    {
        using add_const_t<typename make_signed<T>::type>::type;
    };
    template <typename T>
    struct make_signed<volatile T>
    {
        using add_volatile_t<typename make_signed<T>::type>::type;
    };
    template <typename T>
    struct make_signed<const volatile T>
    {
        using AddCV<typename make_signed<T>::type>::type;
    };

    template <typename T>
    using make_signed_t = make_signed<T>::type;   

REX_RSL_END_NAMESPACE
