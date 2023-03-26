// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: arch_arm_load.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/arch/arm/arch_arm_load.h"

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
        atomic_fixed_width_type_t<8> arm_atomic_load(atomic_fixed_width_type_t<8>* ptr)
        {
          atomic_fixed_width_type_t<8> retIntegral;
          retIntegral = __iso_volatile_load8(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<8>>(ptr));
  
          return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>(retIntegral);
        }
       
        atomic_fixed_width_type_t<16> arm_atomic_load(atomic_fixed_width_type_t<16>* ptr)
        {
          atomic_fixed_width_type_t<16> retIntegral;
          retIntegral = __iso_volatile_load16(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<16>>(ptr));
  
          return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<16>>(retIntegral);
        }
  
        atomic_fixed_width_type_t<32> arm_atomic_load(atomic_fixed_width_type_t<32>* ptr)
        {
          atomic_fixed_width_type_t<32> retIntegral;
          retIntegral = __iso_volatile_load32(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<32>>(ptr));
  
          return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<32>>(retIntegral);
        }
  
        atomic_fixed_width_type_t<64> arm_atomic_load(atomic_fixed_width_type_t<64>* ptr)
        {
          atomic_fixed_width_type_t<64> retIntegral;
          retIntegral = __iso_volatile_load64(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<64>>(ptr));
  
          return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<64>>(retIntegral);
        }
  #endif

#endif
    }
  }
}
