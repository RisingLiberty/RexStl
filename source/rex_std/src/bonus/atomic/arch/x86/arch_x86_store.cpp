// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: arch_x86_store.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/arch/x86/arch_x86_store.h"

#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/compiler.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      void x86_atomic_store(atomic_fixed_width_type_t<8>* ptr, atomic_fixed_width_type_t<8> val)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store8(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<8>>(((rsl::internal::atomic_type_cast<char>((ptr))))), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>(((val))));
#else
        atomic_fixed_width_type_t<8> valIntegral = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>(((val)));
        (*rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<8>>((ptr))) = valIntegral;
#endif
      }

      void x86_atomic_store(atomic_fixed_width_type_t<16>* ptr, atomic_fixed_width_type_t<16> val)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store16(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<16>>(((rsl::internal::atomic_type_cast<short>((ptr))))), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<16>>(((val))));
#else
        atomic_fixed_width_type_t<16> valIntegral = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<16>>(((val)));
        (*rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<16>>((ptr))) = valIntegral;
#endif
      }

      void x86_atomic_store(atomic_fixed_width_type_t<32>* ptr, atomic_fixed_width_type_t<32> val)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store32(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<32>>(((rsl::internal::atomic_type_cast<long>((ptr))))), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<32>>(((val))));
#else
        atomic_fixed_width_type_t<32> valIntegral = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<32>>(((val)));
        (*rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<32>>((ptr))) = valIntegral;
#endif
      }

      void x86_atomic_store(atomic_fixed_width_type_t<64>* ptr, atomic_fixed_width_type_t<64> val)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store64(rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<64>>(((rsl::internal::atomic_type_cast<__int64>((ptr))))), rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<64>>(((val))));
#else
        atomic_fixed_width_type_t<64> valIntegral = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<64>>(((val)));
        (*rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<64>>((ptr))) = valIntegral;
#endif
      }
    }
  }
} // namespace rsl