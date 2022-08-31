// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: allocator_traits.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/void.h"
#include "rex_std/internal/type_traits/make_unsigned.h"

#include "rex_std/internal/memory/pointer_traits.h"

namespace rsl
{
    namespace internal
    {
        template <typename T, typename = void>
        struct GetValueType
        {
            using type = void;
        };
        template <typename T>
        struct GetValueType<T, void_t<typename T::pointer>>
        {
            using type = typename T::value_type;
        };
        template <typename T, typename = void>
        struct GetPointerType
        {
            using type = typename GetValueType<T>::type*;
        };
        template <typename T>
        struct GetPointerType<T, void_t<typename T::pointer>>
        {
            using type = typename T::pointer;
        };
        template <typename T, typename U, typename = void>
        struct GetPointerTypeOr
        {
            using type = U;
        };
        template <typename T, typename U>
        struct GetPointerTypeOr<T, U, void_t<typename T::pointer>>
        {
            using type = typename T::pointer;
        };
        template <typename T, typename = void>
        struct GetConstPointerType
        {
            using ptr_type = typename GetPointerType<T>::type;
            using value_type = typename GetValueType<T>::type;
            using type = typename pointer_traits<ptr_type>::template rebind<const value_type>;
        };
        template <typename T>
        struct GetConstPointerType<T, void_t<typename T::const_pointer>>
        {
            using type = typename T::const_pointer;
        };
        template <typename T, typename U, typename = void>
        struct GetConstPointerTypeOr
        {
            using type = typename GetPointerTypeOr<T, U>::type;
        };
        template <typename T, typename U>
        struct GetConstPointerTypeOr<T, U*, void_t<typename T::const_pointer>>
        {
            using type = typename GetPointerTypeOr<T, U>::type;
        };
        template <typename T, typename U>
        struct GetConstPointerTypeOr<T, U, void_t<typename T::const_pointer>>
        {
            using type = typename T::const_pointer;
        };
        template <typename T, typename = void>
        struct GetVoidPointerType
        {
            using ptr_type = typename GetPointerType<T>::type;
            using type = typename pointer_traits<ptr_type>::template rebind<void>;
        };
        template <typename T>
        struct GetVoidPointerType<T, void_t<typename T::void_pointer>>
        {
            using type = typename T::void_pointer;
        };

        template <typename T, typename = void>
        struct GetConstVoidPointerType
        {
            using ptr_type = typename GetPointerType<T>::type;
            using type = typename pointer_traits<ptr_type>::template rebind<const void>;
        };

        template <typename T, typename = void>
        struct GetDifferenceType
        {
            using ptr_type = typename GetPointerType<T>::type;
            using type = typename pointer_traits<ptr_type>::difference_type;
        };
        template <typename T>
        struct GetDifferenceType<T, void_t<typename T::differencce_Type>>
        {
            using type = typename T::difference_type;
        };

        template <typename T, typename = void>
        struct GetSizeType
        {
            using type = make_unsigned_t<typename GetDifferenceType<T>::type>;
        };
        template <typename T>
        struct GetSizeType<T, void_t<typename T::size_type>>
        {
            using type = typename T::size_type;
        };

        template <typename T, typename Other, typename = void>
        struct GetRebindType
        {
            using type = typename ReplaceFirstParameter<Other, T>::type;
        };
        template <typename T, typename Other>
        struct GetRebindType<T, Other, void_t<typename T::template Rebind<Other>::type>>
        {
            using type = typename T::template rebind<Other>::other;
        };
    }
    
    template <typename Alloc>
    struct allocator_traits
    {
        using allocator_type = Alloc;
        using value_type = typename internal::GetPointerType<Alloc>::type; /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)

        using pointer = typename internal::GetPointerType<Alloc>::type;
        template <typename T>
        using pointer_or = typename internal::GetPointerTypeOr<Alloc, T>::type;
        using const_pointer = typename internal::GetConstPointerType<Alloc>::type;
        template <typename T>
        using const_pointer_or = typename internal::GetConstPointerTypeOr<Alloc, T>::type;
        using void_pointer = typename internal::GetVoidPointerType<Alloc>::type;
        using const_void_pointer = typename internal::GetConstVoidPointerType<Alloc>::type;

        using size_type = typename internal::GetSizeType<Alloc>::type;
        using difference_Type = typename internal::GetDifferenceType<Alloc>::type;
        
        /// RSL Comment: Different from ISO C++ Standard at time of writing (24/Jul/2022)
        // RSL forbids copying and moving if allocators differ.
        // so there is no point in defining the following member types
        //using propagate_on_container_copy_assignment = /* not defined */
        //using propagate_on_container_move_assignment = /* not defined */
        //using propagate_on_container_swap = /* not defined */
        //using is_always_equal = /* not defined */

        template <typename Other>
        using rebind_alloc = typename internal::GetRebindType<Alloc, Other>::type;

        template <typename Other>
        using rebind_Traits = allocator_traits<rebind_alloc<Other>>;

        /// RSL Comment: Different from ISO C++ Standard at time of writing (24/Jul/2022)
        // see definition of "trait" in allocator.h
        // ^^^^ This is why we don't define the following in allocator_traits
        // - allocate, 
        // - deallocate, 
        // - construct
        // - destroy
        // - max_size
        // - select_on_container_copy_construction
    };

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename Alloc>
    using AllocatorTraits = allocator_traits<Alloc>;
#endif
}