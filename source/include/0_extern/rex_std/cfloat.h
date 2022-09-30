// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: cfloat.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

/// [22/Jul/2022] RSL Comment: Rex Standard Library doesn't support floating pointer flags yet.
// It's possible some floating point precision error might occur when using rsl.
// Due to time constrains we have different priorities right now.
// Should you have any issues with floating points when using rsl, please contact @nick.debreuck

REX_RSL_BEGIN_NAMESPACE

// Define the floating point precision used.
//
// For x86, results are in double precision (unless /arch:sse2 is used, in which
// case results are in source precision.
//
// For x64 and ARM, results are in source precision.
//
// If the compiler is invoked with /fp:fast, the compiler is allowed to use the
// fastest precision and even mix within a single function, so precision is
// indeterminable.
//
// Note that manipulating the floating point behavior using the float_control/
// fenv_access/fp_contract #pragmas may alter the actual floating point evaluation
// method, which may in turn invalidate the value of FLT_EVAL_METHOD.
#ifdef _M_FP_FAST
  #define REX_FLT_EVAL_METHOD -1
#else
  #ifdef _M_IX86
    #if _M_IX86_FP >= 2
      #define REX_FLT_EVAL_METHOD 0
    #else
      #define REX_FLT_EVAL_METHOD 2
    #endif
  #else
    #define REX_FLT_EVAL_METHOD 0
  #endif
#endif

#define REX_DBL_DECIMAL_DIG 17                      // # of decimal digits of rounding precision
#define REX_DBL_DIG         15                      // # of decimal digits of precision
#define REX_DBL_EPSILON     2.2204460492503131e-016 // smallest such that 1.0+DBL_EPSILON != 1.0
#define REX_DBL_HAS_SUBNORM 1                       // type does support subnormal numbers
#define REX_DBL_MANT_DIG    53                      // # of bits in mantissa
#define REX_DBL_MAX         1.7976931348623158e+308 // max value
#define REX_DBL_MAX_10_EXP  308                     // max decimal exponent
#define REX_DBL_MAX_EXP     1024                    // max binary exponent
#define REX_DBL_MIN         2.2250738585072014e-308 // min positive value
#define REX_DBL_MIN_10_EXP  (-307)                  // min decimal exponent
#define REX_DBL_MIN_EXP     (-1021)                 // min binary exponent
#define REX_DBL_RADIX       2                       // exponent radix
#define REX_DBL_TRUE_MIN    4.9406564584124654e-324 // min positive value

#define REX_FLT_DECIMAL_DIG 9                // # of decimal digits of rounding precision
#define REX_FLT_DIG         6                // # of decimal digits of precision
#define REX_FLT_EPSILON     1.192092896e-07F // smallest such that 1.0+FLT_EPSILON != 1.0
#define REX_FLT_HAS_SUBNORM 1                // type does support subnormal numbers
#define REX_FLT_GUARD       0
#define REX_FLT_MANT_DIG    24               // # of bits in mantissa
#define REX_FLT_MAX         3.402823466e+38F // max value
#define REX_FLT_MAX_10_EXP  38               // max decimal exponent
#define REX_FLT_MAX_EXP     128              // max binary exponent
#define REX_FLT_MIN         1.175494351e-38F // min normalized positive value
#define REX_FLT_MIN_10_EXP  (-37)            // min decimal exponent
#define REX_FLT_MIN_EXP     (-125)           // min binary exponent
#define REX_FLT_NORMALIZE   0
#define REX_FLT_RADIX       2                // exponent radix
#define REX_FLT_TRUE_MIN    1.401298464e-45F // min positive value

#define REX_LDBL_DIG         DBL_DIG         // # of decimal digits of precision
#define REX_LDBL_EPSILON     DBL_EPSILON     // smallest such that 1.0+LDBL_EPSILON != 1.0
#define REX_LDBL_HAS_SUBNORM DBL_HAS_SUBNORM // type does support subnormal numbers
#define REX_LDBL_MANT_DIG    DBL_MANT_DIG    // # of bits in mantissa
#define REX_LDBL_MAX         DBL_MAX         // max value
#define REX_LDBL_MAX_10_EXP  DBL_MAX_10_EXP  // max decimal exponent
#define REX_LDBL_MAX_EXP     DBL_MAX_EXP     // max binary exponent
#define REX_LDBL_MIN         DBL_MIN         // min normalized positive value
#define REX_LDBL_MIN_10_EXP  DBL_MIN_10_EXP  // min decimal exponent
#define REX_LDBL_MIN_EXP     DBL_MIN_EXP     // min binary exponent
#define REX_LDBL_RADIX       DBL_RADIX       // exponent radix
#define REX_LDBL_TRUE_MIN    DBL_TRUE_MIN    // min positive value

#define REX_DECIMAL_DIG DBL_DECIMAL_DIG

REX_RSL_END_NAMESPACE
