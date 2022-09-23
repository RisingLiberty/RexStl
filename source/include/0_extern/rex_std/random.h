// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: random.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/initializer_list.h"
#include "rex_std/std_alias_defines.h"

#include <random>

REX_RSL_BEGIN_NAMESPACE

template <typename UIntType, UIntType a, UIntType c, UIntType m>
REX_STD_TEMPLATED_CLASS_ALIAS(linear_congruential_engine, UIntType, a, c, m);

template <typename UIntType, size_t w, size_t n, size_t m, size_t r, UIntType a, size_t u, UIntType d, size_t s, UIntType b, size_t t, UIntType c, size_t l, UIntType f>
REX_STD_TEMPLATED_CLASS_ALIAS(mersenne_twister_engine, UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f);

template <typename UIntType, size_t w, size_t s, size_t r>
REX_STD_TEMPLATED_CLASS_ALIAS(subtract_with_carry_engine, UIntType, w, s, r);

template <typename Engine, size_t P, size_t R>
REX_STD_TEMPLATED_CLASS_ALIAS(discard_block_engine, Engine, P, R);

template <typename Engine, size_t W, typename UIntType>
REX_STD_TEMPLATED_CLASS_ALIAS(independent_bits_engine, Engine, W, UIntType);

template <typename Engine, size_t K>
REX_STD_TEMPLATED_CLASS_ALIAS(shuffle_order_engine, Engine, K);

REX_STD_CLASS_ALIAS(minstd_rand0);
REX_STD_CLASS_ALIAS(minstd_rand);
REX_STD_CLASS_ALIAS(mt19937);
REX_STD_CLASS_ALIAS(mt19937_64);
REX_STD_CLASS_ALIAS(ranlux24_base);
REX_STD_CLASS_ALIAS(ranlux48_base);
REX_STD_CLASS_ALIAS(knuth_b);
REX_STD_CLASS_ALIAS(default_random_engine);

REX_STD_CLASS_ALIAS(random_device);

template <typename IntType = int32>
REX_STD_TEMPLATED_CLASS_ALIAS(uniform_int_distribution, IntType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(uniform_real_distribution, RealType);

REX_STD_CLASS_ALIAS(bernoulli_distribution);

template <typename IntType = int32>
REX_STD_TEMPLATED_CLASS_ALIAS(binomial_distribution, IntType);

template <typename IntType = int32>
REX_STD_TEMPLATED_CLASS_ALIAS(negative_binomial_distribution, IntType);

template <typename IntType = int32>
REX_STD_TEMPLATED_CLASS_ALIAS(geometric_distribution, IntType);

template <typename IntType = int32>
REX_STD_TEMPLATED_CLASS_ALIAS(poisson_distribution, IntType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(exponential_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(gamma_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(weibull_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(extreme_value_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(normal_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(lognormal_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(chi_squared_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(cauchy_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(fisher_f_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(student_t_distribution, RealType);

template <typename IntType = int32>
REX_STD_TEMPLATED_CLASS_ALIAS(discrete_distribution, IntType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(piecewise_constant_distribution, RealType);

template <typename RealType = float64>
REX_STD_TEMPLATED_CLASS_ALIAS(piecewise_linear_distribution, RealType);

REX_STD_CLASS_ALIAS(seed_seq);

REX_STD_FUNC_ALIAS(generate_canonical);

REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"