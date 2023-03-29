//// ============================================
////
//// REX - STANDARD LIBRARY IMPLEMENTATION
////
//// Author: Nick De Breuck
//// Twitter: @nick_debreuck
////
//// File: arch_x86_load.cpp
//// Copyright (c) Nick De Breuck 2022
////
//// ============================================
//
//#include "rex_std/bonus/atomic/arch/x86/arch_x86_load.h"
//
//#include "rex_std/bonus/atomic/atomic_casts.h"
//#include "rex_std/bonus/compiler.h"
//
//namespace rsl
//{
//  inline namespace v1
//  {
//    namespace internal
//    {
//#if defined(REX_COMPILER_MSVC)
//      atomic_fixed_width_type_t<8> x86_atomic_load(atomic_fixed_width_type_t<8>* ptr)
//      {
//  #if (REX_COMPILER_VERSION >= 1920)
//        atomic_fixed_width_type_t<8> retIntegral = __iso_volatile_load8(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<8>>(ptr));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>(retIntegral);
//  #else
//        atomic_fixed_width_type_t<8> retIntegral = (*(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<8>>(ptr)));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>(retIntegral);
//  #endif
//      }
//
//      atomic_fixed_width_type_t<16> x86_atomic_load(atomic_fixed_width_type_t<16>* ptr)
//      {
//  #if (REX_COMPILER_VERSION >= 1920)
//        atomic_fixed_width_type_t<16> retIntegral = __iso_volatile_load16(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<16>>(ptr));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<16>>(retIntegral);
//  #else
//        atomic_fixed_width_type_t<16> retIntegral = (*(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<16>>(ptr)));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<16>>(retIntegral);
//  #endif
//      }
//
//      atomic_fixed_width_type_t<32> x86_atomic_load(atomic_fixed_width_type_t<32>* ptr)
//      {
//  #if (REX_COMPILER_VERSION >= 1920)
//        atomic_fixed_width_type_t<32> retIntegral = __iso_volatile_load32(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<32>>(ptr));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<32>>(retIntegral);
//  #else
//        atomic_fixed_width_type_t<32> retIntegral = (*(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<32>>(ptr)));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<32>>(retIntegral);
//  #endif
//      }
//
//      atomic_fixed_width_type_t<64> x86_atomic_load(atomic_fixed_width_type_t<64>* ptr)
//      {
//  #if (REX_COMPILER_VERSION >= 1920)
//        atomic_fixed_width_type_t<64> retIntegral = __iso_volatile_load64(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<64>>(ptr));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<64>>(retIntegral);
//  #else
//        atomic_fixed_width_type_t<64> retIntegral = (*(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<64>>(ptr)));
//        return rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<64>>(retIntegral);
//  #endif
//      }
//#endif
//    }
//  }
//} // namespace rsl