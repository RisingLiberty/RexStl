// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fill_n.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    namespace internal
    {
        template <bool IsScalarValue>
        struct FillNImpl
        {
            template <typename OutputIterator, typename Size, typename T>
            static OutputIterator do_fill(OutputIterator first, Size n, const T& value)
            {
                for (; n-- > 0; ++first)
                {
                    *first = value;
                }
                return first;
            }
        };

        template <>
        struct FillNImpl<true>
        {
            template <typename OutputIterator, typename Size, typename T>
            static OutputIterator do_fill(OutputIterator first, Size n, const T& value)
            {
                using value_type = OutputIterator::value_type;

                // We create a temp and fill from that because value might alias to the destination range
                // the compiler would be forced into generating less efficient code
                for (const T tmp = value; n-- > 0; ++first)
                {
                    *first = static_cast<value_type>(tmp);
                }

                return first;
            }
        };
    }

    template <typename OutputIterator, typename Size, typename T>
    OutputIterator fill_n(OutputIterator first, Size n, const T& value)
    {
        return FillNImpl<is_scalar_v<T>>::do_fill(first, n, value);
    }
}
