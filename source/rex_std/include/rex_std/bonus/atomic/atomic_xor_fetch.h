// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_xor_fetch.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
#if defined(RSL_COMPILER_MSVC)
    template <typename T>
    atomic_t<T> atomic_xor_fetch(T* obj, T mask, rsl::memory_order order)
    {
      (void)order;
      atomic_t<T> atom_mask              = mask;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr(sizeof(T) == 1)
      {
        return _InterlockedXor8_np(volatile_obj, atom_mask) ^ atom_mask;
      }
      else if constexpr(sizeof(T) == 2)
      {
        return _InterlockedXor16_np(volatile_obj, atom_mask) ^ atom_mask;
      }
      else if constexpr(sizeof(T) == 4)
      {
        return _InterlockedXor_np(volatile_obj, atom_mask) ^ atom_mask;
      }
      else if constexpr(sizeof(T) == 8)
      {
        return _InterlockedXor64_np(volatile_obj, atom_mask) ^ atom_mask;
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic add fetch");
        return 0;
      }
    }
#elif defined(RSL_COMPILER_GCC) || defined(RSL_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_xor_fetch(T* obj, T mask, rsl::memory_order order)
    {
      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_xor_fetch(obj, mask, __ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_xor_fetch(obj, mask, __ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_xor_fetch(obj, mask, __ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::release: return __atomic_xor_fetch(obj, mask, __ATOMIC_RELEASE);
        case rsl::v1::memory_order::acq_rel: return __atomic_xor_fetch(obj, mask, __ATOMIC_ACQ_REL);
        case rsl::v1::memory_order::seq_cst: return __atomic_xor_fetch(obj, mask, __ATOMIC_SEQ_CST);
        default: RSL_ASSERT("Invalid memory order for atomic xor_fetch"); break;
      }
    }
#endif
  } // namespace v1
} // namespace rsl
