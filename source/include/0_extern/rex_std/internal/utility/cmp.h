// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: cmp.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/type_traits/make_unsigned.h"
#include "rex_std/internal/type_traits/is_signed.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T, typename U>
    constexpr bool cmp_equal(T t, U u)
    {
        using UT = make_unsigned_t<T>;
        using UU = make_unsigned_t<U>;

        if constexpr (is_signed<T> == is_signed<U>)
        {
            return t == u;
        }
        else if constexpr (is_signed<T>)
        {
            return t < 0 ? false : UT(T) == u;
        }
        else
        {
            return u < 0 ? false : t == UU(u);
        }
    }

    template <typename T, typename U>
    constexpr bool cmp_not_equal(T t, U u)
    {
        return !cmp_equal(t, u);
    }

    template <typename T, typename U>
    constexpr bool cmp_less(T t, U u)
    {
        using UT = make_unsigned_t<T>;
        using UU = make_unsigned_t<U>;

        if constexpr (is_signed<T> == is_signed<U>)
        {
            return t < u;
        }
        else if constexpr (is_signed<T>)
        {
            return t < 0 ? true : UT(t) < u;
        }
        else
        {
            return u < 0 ? false : t < UU(u);
        }
    }

    template <typename T, typename U>
    constexpr bool cmp_greater(T t, U u)
    {
        return cmp_less(u, t);
    }
    template <typename T, typename U>
    constexpr bool cmp_less_equal(T t, U u)
    {
        return !cmp_greater(t, u);
    }
    template <typename T, typename U>
    constexpr bool cmp_greater_equal(T t, U u)
    {
        return !cmp_less(t, u);
    }

REX_RSL_END_NAMESPACE
