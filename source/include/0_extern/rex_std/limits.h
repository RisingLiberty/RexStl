// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: limits.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/types.h"
#include "rex_std/type_traits.h"

#include "rex_std/cfloat.h"
#include "rex_std/climits.h"
#include "rex_std/cstdint.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        constexpr auto SignedInt8Min = SCHAR_MIN;
        constexpr auto SignedInt8Max = SCHAR_MAX;

        constexpr auto SignedInt16Min = SHRT_MIN;
        constexpr auto SignedInt16Max = SHRT_MAX;

        constexpr auto SignedInt32Min = INT_MIN;
        constexpr auto SignedInt32Max = INT_MAX;

        constexpr auto SignedInt64Min = LLONG_MIN;
        constexpr auto SignedInt64Max = LLONG_MAX;

        constexpr auto UnsignedInt8Max = UCHAR_MAX;
        constexpr auto UnsignedInt16Max = USHRT_MAX;
        constexpr auto UnsignedInt32Max = UINT_MAX;
        constexpr auto UnsignedInt64Max = ULLONG_MAX;

        constexpr auto ExponentRadix = 2;

        constexpr auto WCharMin = 0x0000;
        constexpr auto WCharMax = 0xffff;
        constexpr auto WIntMax = 0xffff;

        constexpr auto SignedLongMin = -2147483648L;
        constexpr auto SignedLongMax = 2147483647L;
        constexpr auto UnsignedLongMax = 0xffffffffUL;
        constexpr auto SignedLongLongMin = (-9223372036854775808i64);
        constexpr auto SignedLongLongMax = 9223372036854775807i64;
        constexpr auto UnsignedLongLongMax = 0xffffffffffffffffui64;

        constexpr auto DoubleDecimalDigits = DBL_DECIMAL_DIG; // # of decimal digits of rounding precision
        constexpr auto DoubleDigits = DBL_DIG; // # of decimal digits of precision
        constexpr auto DoubleEpsilon = DBL_EPSILON; // smallest such that 1.0+DoubleEpsilon != 1.0
        constexpr auto DoubleHasSubnorm = DBL_HAS_SUBNORM; // type does support subnormal numbers
        constexpr auto DoubleMantissaDigits = DBL_MANT_DIG; // # of bits in mantissa
        constexpr auto DoubleMax = DBL_MAX; // max value
        constexpr auto DoubleMax10Exp = DBL_MAX_10_EXP; // max decimal exponent
        constexpr auto DoubleMaxExp = DBL_MAX_EXP; // max binary exponent
        constexpr auto DoubleMin = DBL_MIN; // min positive value
        constexpr auto DoubleMin10Exp = DBL_MIN_10_EXP; // min decimal exponent
        constexpr auto DoubleMinExp = DBL_MIN_EXP; // min binary exponent
        constexpr auto DoubleRadix = _DBL_RADIX; // exponent radix
        constexpr auto DoubleTrueMin = DBL_TRUE_MIN; // min positive value

        constexpr auto FloatDecimalDigits = FLT_DECIMAL_DIG; // # of decimal digits of rounding precision
        constexpr auto FloatDigits = FLT_DIG; // # of decimal digits of precision
        constexpr auto FloatEpsilon = FLT_EPSILON; // smallest such that 1.0+FloatEpsilon != 1.0
        constexpr auto FloatHasSubnorm = FLT_HAS_SUBNORM; // type does support subnormal numbers
        constexpr auto FloatGuard = FLT_GUARD;
        constexpr auto FloatMantissaDigits = FLT_MANT_DIG; // # of bits in mantissa
        constexpr auto FloatMax = FLT_MAX; // max value
        constexpr auto FloatMax10Exp = FLT_MAX_10_EXP; // max decimal exponent
        constexpr auto FloatMaxExp = FLT_MAX_EXP; // max binary exponent
        constexpr auto FloatMin = FLT_MIN; // min normalized positive value
        constexpr auto FloatMin10Exp = FLT_MIN_10_EXP; // min decimal exponent
        constexpr auto FloatMinExpr = FLT_MIN_EXP; // min binary exponent
        constexpr auto FloatNormalize = FLT_NORMALIZE;
        constexpr auto FloatRadix = FLT_RADIX; // exponent radix
        constexpr auto FloatTrueMin = FLT_TRUE_MIN; // min positive value

        constexpr auto LongDoubleDigits = DoubleDigits; // # of decimal digits of precision
        constexpr auto LongDoubleEpsilon = DoubleEpsilon; // smallest such that 1.0+LDBL_EPSILON != 1.0
        constexpr auto LongDoubleHasSubnorm = DoubleHasSubnorm; // type does support subnormal numbers
        constexpr auto LongDoubleMantissaDigits = DoubleMantissaDigits; // # of bits in mantissa
        constexpr auto LongDoubleMax = DoubleMax; // max value
        constexpr auto LongDoubleMax10Exp = DoubleMax10Exp; // max decimal exponent
        constexpr auto LongDoubleMaxExp = DoubleMaxExp; // max binary exponent
        constexpr auto LongDoubleMin = DoubleMin; // min normalized positive value
        constexpr auto LongDoubleMin10Exp = DoubleMin10Exp; // min decimal exponent
        constexpr auto LongDoubleMinExp = DoubleMinExp; // min binary exponent
        constexpr auto LongDoubleRadix = DoubleRadix; // exponent radix
        constexpr auto LongDoubleTrueMin = DoubleTrueMin; // min positive value

        constexpr auto NrOfBitsInAByte = CHAR_BIT;

        // ENUM FloatDenormStyle
        // constants for different IEEE float denormalization
        // styles
        enum class FloatDenormStyle
        { 
            DenormIndeterminate = -1,
            DenormAbsent = 0,
            DenormPresent = 1
        };

        // ENUM FloatRoundStyle
        // constants for different IEEE rounding styles
        enum class FloatRoundStyle
        { 
            RoundIndeterminate = -1,
            RoundTowardZero = 0,
            RoundToNearest = 1,
            RoundTowardInfinity = 2,
            RoundTowardNegInfinity = 3
        };

        // STRUCT NumBase
        struct NumBase
        { // base for all types, with common defaults
            static constexpr FloatDenormStyle has_denorm = FloatDenormStyle::DenormAbsent;
            static constexpr bool has_denorm_loss = false;
            static constexpr bool has_infinity = false;
            static constexpr bool has_quiet_nan = false;
            static constexpr bool has_signaling_nan = false;
            static constexpr bool is_bounded = false;
            static constexpr bool is_exact = false;
            static constexpr bool is_iec559 = false;
            static constexpr bool is_integer = false;
            static constexpr bool is_modulo = false;
            static constexpr bool is_signed = false;
            static constexpr bool is_specialized = false;
            static constexpr bool tinyness_before = false;
            static constexpr bool trap = false;
            static constexpr FloatRoundStyle round_style = FloatRoundStyle::RoundTowardZero;
            static constexpr int32 digits = 0;
            static constexpr int32 digits10 = 0;
            static constexpr int32 max_digits10 = 0;
            static constexpr int32 max_exponent = 0;
            static constexpr int32 max_exponent10 = 0;
            static constexpr int32 min_exponent = 0;
            static constexpr int32 min_exponent10 = 0;
            static constexpr int32 radix = 0;
        };

        // STRUCT NumIntBase
        struct NumIntBase : NumBase
        { // base for integer types
            static constexpr bool is_bounded = true;
            static constexpr bool is_exact = true;
            static constexpr bool is_integer = true;
            static constexpr bool is_specialized = true;
            static constexpr int32 radix = 2;
        };

        // STRUCT NumFloatBase
        struct NumFloatBase : NumBase
        { // base for floating-point types
            static constexpr FloatDenormStyle has_denorm = FloatDenormStyle::DenormPresent;
            static constexpr bool has_infinity = true;
            static constexpr bool has_quiet_nan = true;
            static constexpr bool has_signaling_nan = true;
            static constexpr bool is_bounded = true;
            static constexpr bool is_iec559 = true;
            static constexpr bool is_signed = true;
            static constexpr bool is_specialized = true;
            static constexpr FloatRoundStyle round_style = FloatRoundStyle ::RoundToNearest;
            static constexpr int32 radix = ExponentRadix;
        };

        // the min possible value of T
        template <typename T> constexpr auto MinSigned = (T)1 << NrOfDigits<T>;
        template <typename T> constexpr auto MinUnSigned = (T)0;
        template <typename T> constexpr auto Min = rsl::is_signed<T> ? MinSigned<T> : MinUnSigned<T>;

        // the max possible value of T
        template <typename T> constexpr auto MaxSigned = (T)(((((T)1 << (NrOfDigits<T> -1)) - 1) << 1) + 1);
        template <typename T> constexpr auto MaxUnigned = ((T)~(T)0);
        template <typename T> constexpr auto Max = rsl::is_signed<T> ? MaxSigned<T> : MaxUnigned<T>;

        // the number of bits in the represenation of T
        template <typename T> constexpr auto NrOfDigitsSigned = (sizeof(T) * internal::NrOfBitsInAByte) - 1;
        template <typename T> constexpr auto NrOfDigitsUnsigned = (sizeof(T) * internal::NrOfBitsInAByte);
        template <typename T> constexpr auto NrOfDigits = rsl::is_signed<T> ? NrOfDigitsSigned<T> : NrOfDigitsUnsigned<T>;

        // the number of decimal digits that can be represented by T
        template <typename T> constexpr auto NrOfDigits10Signed = (NrOfDigitsSigned<T> *643L) / 2136; // ( 643 / 2136 ) ~= log10(2)
        template <typename T> constexpr auto NrOfDigits10Unsigned = (NrOfDigitsUnsigned<T> *643L) / 2136; // ( 643 / 2136 ) ~= log10(2)
        template <typename T> constexpr auto NrOfDigits10 = rsl::is_signed<T> ? NrOfDigits10Signed<T> : NrOfDigits10Unsigned<T>;
    }

    // CLASS TEMPLATE numeric_limits
    template <class T> class numeric_limits : public internal::NumBase
    { // numeric limits for arbitrary type
      // T (say little or nothing)
    public:
        REX_NO_DISCARD static constexpr T(min)() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T(max)() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T lowest() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T epsilon() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T round_error() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T denorm_min() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T infinity() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T quiet_NaN() noexcept { return T(); }

        REX_NO_DISCARD static constexpr T signaling_NaN() noexcept { return T(); }
    };

    template <class T>
    class numeric_limits<const T> : public numeric_limits<T>
    {
    }; // numeric limits for const types

    template <class T>
    class numeric_limits<volatile T> : public numeric_limits<T>
    {
    }; // numeric limits for volatile types

    template <class T>
    class numeric_limits<const volatile T> : public numeric_limits<T>
    {
    }; // numeric limits for const volatile types

    // CLASS numeric_limits<bool>
    template <> class numeric_limits<bool> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr bool(min)() noexcept { return false; }

        REX_NO_DISCARD static constexpr bool(max)() noexcept { return true; }

        REX_NO_DISCARD static constexpr bool lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr bool epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr bool round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr bool denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr bool infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr bool quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr bool signaling_NaN() noexcept { return 0; }

        static constexpr int32 digits = 1;
    };

    // CLASS numeric_limits<char>
    template <> class numeric_limits<char> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr char(min)() noexcept { return internal::SignedInt8Min; }

        REX_NO_DISCARD static constexpr char(max)() noexcept { return internal::SignedInt8Max; }

        REX_NO_DISCARD static constexpr char lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr char epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char signaling_NaN() noexcept { return 0; }

        static constexpr bool is_signed = internal::SignedInt8Min != 0;
        static constexpr bool is_modulo = internal::SignedInt8Min == 0;
        static constexpr int32 digits = 8 - (internal::SignedInt8Min != 0);
        static constexpr int32 digits10 = 2;
    };

    // CLASS numeric_limits<signed char>
    template <> class numeric_limits<signed char> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr signed char(min)() noexcept
        {
            return internal::SignedInt8Min;
        }

        REX_NO_DISCARD static constexpr signed char(max)() noexcept
        {
            return internal::SignedInt8Max;
        }

        REX_NO_DISCARD static constexpr signed char lowest() noexcept
        {
            return (min)();
        }

        REX_NO_DISCARD static constexpr signed char epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr signed char round_error() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr signed char denorm_min() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr signed char infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr signed char quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr signed char signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_signed = true;
        static constexpr int32 digits = 7;
        static constexpr int32 digits10 = 2;
    };

    // CLASS numeric_limits<unsigned char>
    template <> class numeric_limits<unsigned char> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr unsigned char(min)() noexcept { return 0; }

        REX_NO_DISCARD static constexpr unsigned char(max)() noexcept
        {
            return internal::UnsignedInt8Max;
        }

        REX_NO_DISCARD static constexpr unsigned char lowest() noexcept
        {
            return (min)();
        }

        REX_NO_DISCARD static constexpr unsigned char epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr unsigned char round_error() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned char denorm_min() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned char infinity() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned char quiet_NaN() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned char signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 8;
        static constexpr int32 digits10 = 2;
    };

#ifdef __cpp_char8_t
    // CLASS numeric_limits<char8_t>
    template <> class numeric_limits<char8_t> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr char8_t(min)() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char8_t(max)() noexcept { return internal::UnsignedInt8Max; }

        REX_NO_DISCARD static constexpr char8_t lowest() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char8_t epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char8_t round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char8_t denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char8_t infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char8_t quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char8_t signaling_NaN() noexcept { return 0; }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 8;
        static constexpr int32 digits10 = 2;
    };
#endif // __cpp_char8_t

    // CLASS numeric_limits<char16_t>
    template <> class numeric_limits<char16_t> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr char16_t(min)() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char16_t(max)() noexcept { return internal::UnsignedInt16Max; }

        REX_NO_DISCARD static constexpr char16_t lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr char16_t epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char16_t round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char16_t denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char16_t infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char16_t quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char16_t signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 16;
        static constexpr int32 digits10 = 4;
    };

    // CLASS numeric_limits<char32_t>
    template <> class numeric_limits<char32_t> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr char32_t(min)() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char32_t(max)() noexcept { return internal::UnsignedInt32Max; }

        REX_NO_DISCARD static constexpr char32_t lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr char32_t epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char32_t round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char32_t denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char32_t infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char32_t quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr char32_t signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 32;
        static constexpr int32 digits10 = 9;
    };

    // CLASS numeric_limits<wchar_t>
    template <> class numeric_limits<wchar_t> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr wchar_t(min)() noexcept { return internal::WCharMin; }

        REX_NO_DISCARD static constexpr wchar_t(max)() noexcept { return internal::WCharMax; }

        REX_NO_DISCARD static constexpr wchar_t lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr wchar_t epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr wchar_t round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr wchar_t denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr wchar_t infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr wchar_t quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr wchar_t signaling_NaN() noexcept { return 0; }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 16;
        static constexpr int32 digits10 = 4;
    };

    // CLASS numeric_limits<short>
    template <> class numeric_limits<short> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr short(min)() noexcept { return internal::SignedInt16Min; }

        REX_NO_DISCARD static constexpr short(max)() noexcept { return internal::SignedInt16Max; }

        REX_NO_DISCARD static constexpr short lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr short epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr short round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr short denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr short infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr short quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr short signaling_NaN() noexcept { return 0; }

        static constexpr bool is_signed = true;
        static constexpr int32 digits = 15;
        static constexpr int32 digits10 = 4;
    };

    // CLASS numeric_limits<int32>
    template <> class numeric_limits<int32> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr int32(min)() noexcept { return internal::SignedInt32Min; }

        REX_NO_DISCARD static constexpr int32(max)() noexcept { return internal::SignedInt32Max; }

        REX_NO_DISCARD static constexpr int32 lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr int32 epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr int32 round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr int32 denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr int32 infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr int32 quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr int32 signaling_NaN() noexcept { return 0; }

        static constexpr bool is_signed = true;
        static constexpr int32 digits = 31;
        static constexpr int32 digits10 = 9;
    };

    // CLASS numeric_limits<long>
    template <> class numeric_limits<long> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr long(min)() noexcept { return internal::SignedLongMin; }

        REX_NO_DISCARD static constexpr long(max)() noexcept { return internal::SignedLongMax; }

        REX_NO_DISCARD static constexpr long lowest() noexcept { return (min)(); }

        REX_NO_DISCARD static constexpr long epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long signaling_NaN() noexcept { return 0; }

        static_assert(sizeof(int32) == sizeof(long), "LongLP64 assumption");
        static constexpr bool is_signed = true;
        static constexpr int32 digits = 31;
        static constexpr int32 digits10 = 9;
    };

    // CLASS numeric_limits<long long>
    template <> class numeric_limits<long long> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr long long(min)() noexcept
        {
            return internal::SignedLongLongMin;
        }

        REX_NO_DISCARD static constexpr long long(max)() noexcept
        {
            return internal::SignedLongLongMax;
        }

        REX_NO_DISCARD static constexpr long long lowest() noexcept
        {
            return (min)();
        }

        REX_NO_DISCARD static constexpr long long epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long long round_error() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long long denorm_min() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long long infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long long quiet_NaN() noexcept { return 0; }

        REX_NO_DISCARD static constexpr long long signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_signed = true;
        static constexpr int32 digits = 63;
        static constexpr int32 digits10 = 18;
    };

#ifdef _NATIVE_WCHAR_T_DEFINED
    // CLASS numeric_limits<unsigned short>
    template <> class numeric_limits<unsigned short> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr unsigned short(min)() noexcept { return 0; }

        REX_NO_DISCARD static constexpr unsigned short(max)() noexcept
        {
            return internal::UnsignedInt16Max;
        }

        REX_NO_DISCARD static constexpr unsigned short lowest() noexcept
        {
            return (min)();
        }

        REX_NO_DISCARD static constexpr unsigned short epsilon() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned short round_error() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned short denorm_min() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned short infinity() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned short quiet_NaN() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned short signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 16;
        static constexpr int32 digits10 = 4;
    };
#endif // _NATIVE_WCHAR_T_DEFINED

    // CLASS numeric_limits<uint32>
    template <> class numeric_limits<uint32> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr uint32(min)() noexcept { return 0; }

        REX_NO_DISCARD static constexpr uint32(max)() noexcept
        {
            return internal::UnsignedInt32Max;
        }

        REX_NO_DISCARD static constexpr uint32 lowest() noexcept
        {
            return (min)();
        }

        REX_NO_DISCARD static constexpr uint32 epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr uint32 round_error() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr uint32 denorm_min() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr uint32 infinity() noexcept { return 0; }

        REX_NO_DISCARD static constexpr uint32 quiet_NaN() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr uint32 signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 32;
        static constexpr int32 digits10 = 9;
    };

    // CLASS numeric_limits<unsigned long>
    template <> class numeric_limits<unsigned long> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr unsigned long(min)() noexcept { return 0; }

        REX_NO_DISCARD static constexpr unsigned long(max)() noexcept
        {
            return internal::UnsignedLongMax;
        }

        REX_NO_DISCARD static constexpr unsigned long lowest() noexcept
        {
            return (min)();
        }

        REX_NO_DISCARD static constexpr unsigned long epsilon() noexcept { return 0; }

        REX_NO_DISCARD static constexpr unsigned long round_error() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long denorm_min() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long infinity() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long quiet_NaN() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long signaling_NaN() noexcept
        {
            return 0;
        }

        static_assert(sizeof(uint32) == sizeof(unsigned long), "LongLP64 assumption");
        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 32;
        static constexpr int32 digits10 = 9;
    };

    // CLASS numeric_limits<unsigned long long>
    template <> class numeric_limits<unsigned long long> : public internal::NumIntBase
    {
    public:
        REX_NO_DISCARD static constexpr unsigned long long(min)() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long long(max)() noexcept
        {
            return internal::UnsignedLongLongMax;
        }

        REX_NO_DISCARD static constexpr unsigned long long lowest() noexcept
        {
            return (min)();
        }

        REX_NO_DISCARD static constexpr unsigned long long epsilon() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long long round_error() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long long denorm_min() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long long infinity() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long long quiet_NaN() noexcept
        {
            return 0;
        }

        REX_NO_DISCARD static constexpr unsigned long long signaling_NaN() noexcept
        {
            return 0;
        }

        static constexpr bool is_modulo = true;
        static constexpr int32 digits = 64;
        static constexpr int32 digits10 = 19;
    };

    // CLASS numeric_limits<float>
    template <> class numeric_limits<float> : public internal::NumFloatBase
    {
    public:
        REX_NO_DISCARD static constexpr float(min)() noexcept { return internal::FloatMin; }

        REX_NO_DISCARD static constexpr float(max)() noexcept { return internal::FloatMax; }

        REX_NO_DISCARD static constexpr float lowest() noexcept { return -(max)(); }

        REX_NO_DISCARD static constexpr float epsilon() noexcept
        {
            return internal::FloatEpsilon;
        }

        REX_NO_DISCARD static constexpr float round_error() noexcept { return 0.5F; }

        REX_NO_DISCARD static constexpr float denorm_min() noexcept
        {
            return internal::FloatTrueMin;
        }

        REX_NO_DISCARD static constexpr float infinity() noexcept
        {
            return __builtin_huge_valf();
        }

        REX_NO_DISCARD static constexpr float quiet_NaN() noexcept
        {
            return __builtin_nanf("0");
        }

        REX_NO_DISCARD static constexpr float signaling_NaN() noexcept
        {
            return __builtin_nansf("1");
        }

        static constexpr int32 digits = internal::FloatMantissaDigits;
        static constexpr int32 digits10 = internal::FloatDigits;
        static constexpr int32 max_digits10 = 9;
        static constexpr int32 max_exponent = internal::FloatMaxExp;
        static constexpr int32 max_exponent10 = internal::FloatMax10Exp;
        static constexpr int32 min_exponent = internal::FloatMinExpr;
        static constexpr int32 min_exponent10 = internal::FloatMin10Exp;
    };

    // CLASS numeric_limits<double>
    template <> class numeric_limits<double> : public internal::NumFloatBase
    {
    public:
        REX_NO_DISCARD static constexpr double(min)() noexcept { return internal::DoubleMin; }

        REX_NO_DISCARD static constexpr double(max)() noexcept { return internal::DoubleMax; }

        REX_NO_DISCARD static constexpr double lowest() noexcept { return -(max)(); }

        REX_NO_DISCARD static constexpr double epsilon() noexcept
        {
            return internal::DoubleEpsilon;
        }

        REX_NO_DISCARD static constexpr double round_error() noexcept { return 0.5; }

        REX_NO_DISCARD static constexpr double denorm_min() noexcept
        {
            return internal::DoubleTrueMin;
        }

        REX_NO_DISCARD static constexpr double infinity() noexcept
        {
            return __builtin_huge_val();
        }

        REX_NO_DISCARD static constexpr double quiet_NaN() noexcept
        {
            return __builtin_nan("0");
        }

        REX_NO_DISCARD static constexpr double signaling_NaN() noexcept
        {
            return __builtin_nans("1");
        }

        static constexpr int32 digits = internal::DoubleMantissaDigits;
        static constexpr int32 digits10 = internal::DoubleDigits;
        static constexpr int32 max_digits10 = 17;
        static constexpr int32 max_exponent = internal::DoubleMaxExp;
        static constexpr int32 max_exponent10 = internal::DoubleMax10Exp;
        static constexpr int32 min_exponent = internal::DoubleMinExp;
        static constexpr int32 min_exponent10 = internal::DoubleMin10Exp;
    };

    // CLASS numeric_limits<long double>
    template <> class numeric_limits<long double> : public internal::NumFloatBase
    {
    public:
        REX_NO_DISCARD static constexpr long double(min)() noexcept
        {
            return internal::LongDoubleMin;
        }

        REX_NO_DISCARD static constexpr long double(max)() noexcept
        {
            return internal::LongDoubleMax;
        }

        REX_NO_DISCARD static constexpr long double lowest() noexcept
        {
            return -(max)();
        }

        REX_NO_DISCARD static constexpr long double epsilon() noexcept
        {
            return internal::LongDoubleEpsilon;
        }

        REX_NO_DISCARD static constexpr long double round_error() noexcept
        {
            return 0.5L;
        }

        REX_NO_DISCARD static constexpr long double denorm_min() noexcept
        {
            return internal::LongDoubleTrueMin;
        }

        REX_NO_DISCARD static constexpr long double infinity() noexcept
        {
            return __builtin_huge_val();
        }

        REX_NO_DISCARD static constexpr long double quiet_NaN() noexcept
        {
            return __builtin_nan("0");
        }

        REX_NO_DISCARD static constexpr long double signaling_NaN() noexcept
        {
            return __builtin_nans("1");
        }

        static constexpr int32 digits = internal::LongDoubleMantissaDigits;
        static constexpr int32 digits10 = internal::LongDoubleDigits;
        static constexpr int32 max_digits10 = 17;
        static constexpr int32 max_exponent = internal::LongDoubleMaxExp;
        static constexpr int32 max_exponent10 = internal::LongDoubleMax10Exp;
        static constexpr int32 min_exponent = internal::LongDoubleMinExp;
        static constexpr int32 min_exponent10 = internal::LongDoubleMin10Exp;
    };

REX_RSL_END_NAMESPACE
