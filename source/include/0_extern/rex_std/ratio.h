// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: ratio.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/bonus/types.h"
#include "rex_std/bonus/type_traits/sign_of.h"

#include "rex_std/internal/type_traits/integral_constant.h"

#include "rex_std/cstdint.h"

namespace rsl
{
    template <intmax Num, intmax Den>
    struct ratio;
    
    namespace internal
    {
        template <intmax Val>
        struct Abs : integral_constant<intmax, (Val < 0 ? -Val : Val)>
        {};

        template <intmax X, intmax Y>
        struct GcdX : GcdX<Y, X % Y>::type
        {};

        template <intmax Val>
        struct GcdX<Val, 0> : integral_constant<intmax, Val>
        {};

        template <intmax X, intmax Y>
        struct Gcd : GcdX<Abs<X>::value, Abs<Y>::value>::type
        {};

        // specialization to avoid division by 0
        template<>
        struct Gcd<0, 0> : integral_constant<intmax, 1>
        {};

      

        template <typename T>
        constexpr bool IsRatio = false;

        template <intmax R1, intmax R2>
        constexpr bool IsRatio<ratio<R1, R2>> = true;

        template <intmax X, intmax Y>
        struct Lcm
        {
            static const intmax value = (X * (Y / Gcd<X, Y>::value));
        };

        template <typename Period1, typename Period2>
        struct RatioGcd
        {
            static_assert(IsRatio<Period1>::value, "Period1 is not a ratio type");
            static_assert(IsRatio<Period2>::value, "Period2 is not a ratio type");

            using type = ratio<Gcd<Period1::num, Period2::num>::value, Lcm<Period1::den, Period2::den>::value>;
        };

        template <intmax X, intmax Y>
        struct AdditionOverFlow
        {
            static const bool DifferentSigns = (X <= 0 && 0 <= Y) || (Y < 0 && 0 < X);
            static const bool InrangeOfIntMax = Abs<Y>::value <= INTMAX_MAX - Abs<X>::value;
            static const bool value = DifferentSigns || InrangeOfIntMax;
        };

        template <intmax X, intmax Y>
        struct MultiplyOverFlow
        {
            static const bool value = (Abs<X>::value <= (INTMAX_MAX / Abs<Y>::value));
        };

        template <intmax X, intmax Y>
        struct ct_add
        {
            static_assert(AdditionOverFlow<x, Y>::value, "compile-time addition overflow");
            static const intmax value = X + Y;
        };

        template <intmax X, intmax Y>
        struct ct_sub
        {
            static_assert(AdditionOverFlow<X, -Y>::value, "compile-time addition overflow");
            static const intmax value = X - Y;
        };

        template <intmax X, intmax Y>
        struct ct_multi
        {
            static_assert(MultiplyOverFlow<X, Y>::value, "compile-time multiply overflow");
            static const intmax value = X * Y;
        };

        template <class R1>
        struct ct_simplify
        {
            static const intmax divisor = internal::Gcd<R1::num, R1::den>::value;
            static const intmax num = R1::num / divisor;
            static const intmax den = R1::den / divisor;

            using ratio_type = ratio<num, den>;
            using this_type = ct_simplify<R1>;
        };
    }
    
    template <intmax Num, intmax Den = 1>
    struct ratio
    {
        static_assert(Den != 0, "zero denominator");
        static_assert(Num > -INTMAX_MAX, "numerator too negative");
        static_assert(Den > -INTMAX_MAX, "denominator too negative");

        static constexpr intmax num = sign_of_v<Num> * sign_of_v<Den> * internal::Abs<Num>::value / internal::Gcd<Num, Den>::value;
        static constexpr intmax den = internal::Abs<Den>::value / internal::Gcd<Num, Den>::value;

        using type = ratio<num, den>;
    };

    template <typename R1, typename R2>
    struct RatioAddStruct
    {
        using type = typename internal::ct_simplify
        <
            typename ratio
            <
                internal::ct_add
                <
                    internal::ct_multi<R1::num, R2::den>::value, 
                    internal::ct_multi<R2::num, R1::den>::value
                >::value,
                internal::ct_multi<R1::den, R2::den>::value
            >::type
        >::ratio_type;
    };

    template <typename R1, typename R2>
    struct RatioSubtractStruct
    {
        using type = typename internal::ct_simplify
        <
            typename ratio
            <
                internal::ct_sub
                <
                    internal::ct_sub
                    <
                        internal::ct_multi<R1::num, R2::den>::value,
                        internal::ct_multi<R2::num, R1::den>::value
                    >::value,
                    internal::ct_multi<R1::den, R2::den>::value
                >::value
            >::type
        >::ratio_type;
        
    };

    template <typename R1, typename R2>
    struct RatioMultiplyStruct
    {
        using type = typename internal::ct_simplify
        <
            typename ratio
            <
                internal::ct_multi<R1::num, R2::num>::value,
                internal::ct_multi<R1::den, R2::den>::value
            >::type
        >::ratio_type;
    };

    template <typename R1, typename R2>
    struct RatioDivideStruct
    {
        using type = typename internal::ct_simplify
        <
            typename ratio
            <
                internal::ct_multi<R1::num, R2::den>::value,
                internal::ct_multi<R1::den, R2::num>::value
            >::type
        >::ratio_type;
    };

    template <typename R1, typename R2>
    struct RatioEqualStruct
    {
        using sr1 = internal::ct_simplify<R1>;
        using sr2 = internal::ct_simplify<R2>;

        static const bool value = (sr1::num == sr2::num) && (sr1::den == sr2::den);
    };

    template <typename R1, typename R2>
    struct RatioLessStruct
    {
        static const bool value = (R1::num * R2::den) < (R2::num * R1::den);
    };

    template <typename R1, typename R2> using RatioAdd = typename RatioAddStruct<R1, R2>::type;
    template <typename R1, typename R2> using RatioSubtract = typename RatioSubtractStruct<R1, R2>::type;
    template <typename R1, typename R2> using RatioMultiply = typename RatioMultiplyStruct<R1, R2>::type;
    template <typename R1, typename R2> using RatioDivide = typename RatioDivideStruct<R1, R2>::type;

    template <typename R1, typename R2> struct RatioEqual : public bool_constant<RatioEqualStruct<R1, R2>::value> {};
    template <typename R1, typename R2> struct RatioNotEqual : public bool_constant<!RatioEqual<R1, R2>::value> {};
    template <typename R1, typename R2> struct RatioLess : public bool_constant<RatioLessStruct<R1, R2>::value> {};
    template <typename R1, typename R2> struct RatioLessEqual : public bool_constant<!RatioLess<R2, R1>::value> {};
    template <typename R1, typename R2> struct RatioGreater : public bool_constant<RatioLess<R2, R1>::value> {};
    template <typename R1, typename R2> struct RatioGreaterEqual : public bool_constant<!RatioLess<R1, R2>::value> {};

	// using yocto = ratio<1, 1000000000000000000000000>;   // not supported, too big for intmax
	// using zepto = ratio<1, 1000000000000000000000   >;   // not supported, too big for intmax
	using atto  = ratio<1, 1000000000000000000      >;
	using femto = ratio<1, 1000000000000000         >;
	using pico  = ratio<1, 1000000000000            >;
	using nano  = ratio<1, 1000000000               >;
	using micro = ratio<1, 1000000                  >;
	using milli = ratio<1, 1000                     >;
	using centi = ratio<1, 100                      >;
	using deci  = ratio<1, 10                       >;
	using deca  = ratio<10, 1                       >;
	using hecto = ratio<100, 1                      >;
	using kilo  = ratio<1000, 1                     >;
	using mega  = ratio<1000000, 1                  >;
	using giga  = ratio<1000000000, 1               >;
	using tera  = ratio<1000000000000, 1            >;
	using peta  = ratio<1000000000000000, 1         >;
	using exa   = ratio<1000000000000000000, 1      >;
	// using zetta = ratio<1000000000000000000000, 1   >;   // not supported, too big for intmax
	// using yotta = ratio<1000000000000000000000000, 1>;   // not supported, too big for intmax
}
