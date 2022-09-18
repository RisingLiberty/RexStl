// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: functional.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

// This header heavily differs from the C++ Standard.
// main reason for this is because the C++ standard needs to remain
// backwards compatible, they haven't removed functions like std::bind.
// While rsl is starting from scratch, we don't have support legacy code
// which is generally agreed to be poor code to use.

#pragma once

#include "rex_std/internal/functional/function.h"

#include "rex_std/internal/functional/equal_to.h"
#include "rex_std/internal/functional/hash.h"

#include "rex_std/internal/iterator/iterator_traits.h"

/// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
// the placeholders namespace is not defined in rsl as it is mainly used with std::bind.
// namespace placeholders {}

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <functional>

REX_RSL_BEGIN_NAMESPACE

    REX_STD_FUNC_ALIAS(mem_fn);

    template <typename ForwardIt, typename BinaryPredicate = rsl::equal_to<>>
    REX_STD_TEMPLATED_CLASS_ALIAS(default_searcher, ForwardIt, BinaryPredicate);
    template <typename RandomIt1, typename Hash = rsl::hash<typename rsl::iterator_traits<RandomIt1>::value_type>, typename BinaryPredicate = rsl::equal_to<>>
    REX_STD_TEMPLATED_CLASS_ALIAS(boyer_moore_searcher, RandomIt1, Hash, BinaryPredicate);
    template <typename RandomIt1, typename Hash = rsl::hash<typename rsl::iterator_traits<RandomIt1>::value_type>, typename BinaryPredicate = rsl::equal_to<>>
    REX_STD_TEMPLATED_CLASS_ALIAS(boyer_moore_horspool_searcher, RandomIt1, Hash, BinaryPredicate);

    // Leaving out bind_front, bind_back and bind because people should be using lambdas

#ifdef REX_ENABLE_WITH_CPP23

    REX_STD_TEMPLATED_CLASS_ALIAS(move_only_function, typename ...);

    REX_STD_FUNC_ALIAS(invoke_r);

#endif // REX_ENABLE_WITH_CPP23


REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"