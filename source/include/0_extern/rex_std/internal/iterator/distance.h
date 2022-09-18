// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: distance.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_tags.h"
#include "rex_std/internal/iterator/iterator_traits.h"

#include "rex_std/internal/type_traits/is_base_of.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        template <typename Iterator>
        auto random_access_distance(Iterator lhs, Iterator rhs)
        {
            return rhs - lhs;
        }

        template <typename Iterator>
        auto non_random_access_distance(Iterator lhs, Iterator rhs)
        {
            typename iterator_traits<Iterator>::difference_type result = 0;
            while (lhs != rhs)
            {
                ++lhs;
                ++result;
            }
            return result;
        }
    }

    template <typename Iterator>
    auto distance(Iterator lhs, Iterator rhs)
    {
        if constexpr (is_base_of_v<random_access_iterator_tag, typename iterator_traits<Iterator>::iterator_category>)
        {
            return internal::random_access_distance(lhs, rhs);
        }
        else
        {
            return internal::non_random_access_distance(lhs, rhs);
        }
    }

REX_RSL_END_NAMESPACE
