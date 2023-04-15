// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_store.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"

#if defined(REX_COMPILER_MSVC)
  #include <intrin.h>
#endif

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    void atomic_store(T* obj, T valToStore, rsl::memory_order order)
    {
      (void)order;
      atomic_t<T> atom_value_to_store    = valToStore;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr(sizeof(T) == 1)
      {
  #if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store8(volatile_obj, atom_value_to_store);

  #else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
  #endif
      }
      else if constexpr(sizeof(T) == 2)
      {
  #if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store16(volatile_obj, atom_value_to_store);
  #else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
  #endif
      }
      else if constexpr(sizeof(T) == 4)
      {
  #if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store32(rsl::internal::atomic_volatile_integral_cast<int>(volatile_obj), atom_value_to_store);
  #else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
  #endif
      }
      else if constexpr(sizeof(T) == 8)
      {
  #if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store64(volatile_obj, atom_value_to_store);
  #else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
  #endif
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic fetch or");
        0;
      }
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    void atomic_store(T* obj, T valToStore, rsl::memory_order order)
    {
      // GCC Documentation says:
      // These built-in functions perform the operation suggested by the name, and the value that had previously been in *obj.
      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type.
      // That is, they are not scaled by the size of the type to which the pointer points.
      // { tmp = *obj; *obj op= val; tmp; }
      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that

      switch(order)
      {
        case rsl::v1::memory_order::relaxed: __atomic_store(obj, &valToStore, __ATOMIC_RELAXED); break;
        case rsl::v1::memory_order::release: __atomic_store(obj, &valToStore, __ATOMIC_RELEASE); break;
        case rsl::v1::memory_order::seq_cst: __atomic_store(obj, &valToStore, __ATOMIC_SEQ_CST); break;
        default: RSL_ASSERT("Invalid memory order for atomic store"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl
