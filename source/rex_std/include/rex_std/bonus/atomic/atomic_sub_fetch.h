// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_sub_fetch.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/types.h"

#if defined(REX_COMPILER_MSVC)
  #include <intrin.h>
#endif

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    atomic_t<T> atomic_sub_fetch(T* obj, T valToSub, rsl::memory_order /*unused*/)
    {
      T value_to_sub                     = internal::atomic_negate_operand(valToSub);
      atomic_t<T> atom_value_to_sub      = value_to_sub;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      atomic_t<T> res = 0;
      if constexpr(sizeof(T) == 1)
      {
        res = _InterlockedExchangeAdd8(volatile_obj, atom_value_to_sub);
      }
      else if constexpr(sizeof(T) == 2)
      {
        res = _InterlockedExchangeAdd16(volatile_obj, atom_value_to_sub);
      }
      else if constexpr(sizeof(T) == 4)
      {
        res = _InterlockedExchangeAdd(volatile_obj, atom_value_to_sub);
      }
      else if constexpr(sizeof(T) == 8)
      {
        res = _InterlockedExchangeAdd64(volatile_obj, atom_value_to_sub);
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic fetch or");
        return 0;
      }

      return res + atom_value_to_sub; // atomc_value_to_sub is negative, so we need to add, not subtract
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_sub_fetch(T* obj, T valToSub, rsl::memory_order order)
    {
      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_sub_fetch(obj, valToSub, __ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_sub_fetch(obj, valToSub, __ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_sub_fetch(obj, valToSub, __ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::release: return __atomic_sub_fetch(obj, valToSub, __ATOMIC_RELEASE);
        case rsl::v1::memory_order::acq_rel: return __atomic_sub_fetch(obj, valToSub, __ATOMIC_ACQ_REL);
        case rsl::v1::memory_order::seq_cst: return __atomic_sub_fetch(obj, valToSub, __ATOMIC_SEQ_CST);
        default: RSL_ASSERT("Invalid memory order for atomic sub_fetch"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl
