// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_store.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/atomic_store.h"
#include "rex_std/bonus/atomic/atomic_casts.h"

#include "rex_std/bonus/compiler.h"

namespace rsl
{
  inline namespace v1
  {
//    void atomic_store(atomic_fixed_width_type_t<8> val)
//    {
//#ifdef REX_COMPILER_MSVC
//
//#else
//#error "Not implemented"
//#endif
//
//
//
//
//      atomic_fixed_width_type_t<8> fixedWidthDesired = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>((val));
//      { 
//        atomic_fixed_width_type_t<8> exchange8; 
//        (void)(exchange8); 
//        { 
//          char retIntegral; 
//          retIntegral = _InterlockedExchange8(rsl::internal::atomic_volatile_integral_cast<char>(((rsl::internal::atomic_type_cast<atomic_fixed_width_type_t<8>>((this->GetAtomicAddress()))))), rsl::internal::atomic_type_pun_cast<char>(((fixedWidthDesired)))); 
//          exchange8 = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>((retIntegral)); 
//        }; 
//      }
//    }
//    void atomic_store(atomic_fixed_width_type_t<16> val)
//    {
//
//    }
//    void atomic_store(atomic_fixed_width_type_t<32> val)
//    {
//
//    }
//    void atomic_store(atomic_fixed_width_type_t<64> val)
//    {
//
//    }
  }
}