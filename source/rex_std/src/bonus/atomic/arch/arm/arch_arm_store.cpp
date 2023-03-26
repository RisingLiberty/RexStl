// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: arch_arm_store.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/arch/arm/arch_arm_store.h"

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/compiler.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
#if defined(REX_PLATFORM_ARM64)
  #if defined(REX_COMPILER_MSVC)
      void arm_atomic_store(atomic_fixed_width_type_t<8>* ptr, atomic_fixed_width_type_t<8> val)
      {
        __iso_volatile_store8(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<8>>(ptr), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>(val));
      }
      void arm_atomic_store(atomic_fixed_width_type_t<16>* ptr, atomic_fixed_width_type_t<16> val)
      {
        __iso_volatile_store16(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<16>>(ptr), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<16>>(val));
      }
      void arm_atomic_store(atomic_fixed_width_type_t<32>* ptr, atomic_fixed_width_type_t<32> val)
      {
        __iso_volatile_store32(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<32>>(ptr), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<32>>(val));
      }
      void arm_atomic_store(atomic_fixed_width_type_t<64>* ptr, atomic_fixed_width_type_t<64> val)
      {
        __iso_volatile_store64(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<64>>(ptr), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<64>>(val));
      }
  #endif
#endif
    }
  }
}
