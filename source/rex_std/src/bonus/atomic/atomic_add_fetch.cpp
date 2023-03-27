

// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_add_fetch.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/atomic_add_fetch.h"

#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"

#include "rex_std/atomic.h"

namespace rsl
{
  inline namespace v1
  {
    // uint8
    void atomic_add_fetch_relaxed(uint8* obj, uint8 valToAdd)
    {
#if defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_fixed_width_type_t<8> retIntegral;
      atomic_fixed_width_type_t<8> valIntegral = REX_ATOMIC_TYPE_PUN_CAST(integralType, (val));

      retIntegral = fetchIntrinsic(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(integralType, (ptr)), valIntegral, gccMemoryOrder);

      ret = REX_ATOMIC_TYPE_PUN_CAST(type, retIntegral);
#elif defined(REX_COMPILER_MSVC))


      char c;
      char c2 = 1;

      { 
        char retIntegral; 
        char valCompute; 
        valCompute = ((1)); 
        const char valIntegral = rsl::internal::atomic_type_pun_cast<char>((valCompute)); 
        retIntegral = _InterlockedExchangeAdd8(rsl::internal::atomic_volatile_integral_cast<char>(((&c2))), valIntegral); 
        c = rsl::internal::atomic_type_pun_cast<char>((retIntegral));
        c = (c)+((1)); 
      };










      char c;
      char c2 = 1;
      { 
        // prepare by casting everything to the right type
        atomic_fixed_width_type_t<8> valCompute = valToAdd; 
        const atomic_fixed_width_type_t<8> valIntegral = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>((valCompute));
        volatile atomic_fixed_width_type_t<8>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_fixed_width_type_t<8>>(obj);

        // perform the atomic operatoins
        atomic_fixed_width_type_t<8> retIntegral = _InterlockedExchangeAdd8(volatile_obj, valIntegral);

        // cleanup by casting everything back to the right type and performing the add
        c = rsl::internal::atomic_type_pun_cast<atomic_fixed_width_type_t<8>>((retIntegral));
        c = (c) + valToAdd; 
      };
#endif
    }
    void atomic_add_fetch_acquire(uint8 val, uint8* address)
    {

    }
    void atomic_add_fetch_release(uint8 val, uint8* address)
    {

    }
    void atomic_add_fetch_acq_rel(uint8 val, uint8* address)
    {

    }
    void atomic_add_fetch_seq_cst(uint8 val, uint8* address)
    {

    }

    // int8
    void atomic_add_fetch_relaxed(int8 val, int8* address)
    {

    }
    void atomic_add_fetch_acquire(int8 val, int8* address)
    {

    }
    void atomic_add_fetch_release(int8 val, int8* address)
    {

    }
    void atomic_add_fetch_acq_rel(int8 val, int8* address)
    {

    }
    void atomic_add_fetch_seq_cst(int8 val, int8* address)
    {

    }

    // uint16
    void atomic_add_fetch_relaxed(uint16 val, uint16* address)
    {

    }
    void atomic_add_fetch_acquire(uint16 val, uint16* address)
    {

    }
    void atomic_add_fetch_release(uint16 val, uint16* address)
    {

    }
    void atomic_add_fetch_acq_rel(uint16 val, uint16* address)
    {

    }
    void atomic_add_fetch_seq_cst(uint16 val, uint16* address)
    {

    }

    // int16
    void atomic_add_fetch_relaxed(int16 val, int16* address)
    {

    }
    void atomic_add_fetch_acquire(int16 val, int16* address)
    {

    }
    void atomic_add_fetch_release(int16 val, int16* address)
    {

    }
    void atomic_add_fetch_acq_rel(int16 val, int16* address)
    {

    }
    void atomic_add_fetch_seq_cst(int16 val, int16* address)
    {

    }

    // uint32
    void atomic_add_fetch_relaxed(uint32 val, uint32* address)
    {

    }
    void atomic_add_fetch_acquire(uint32 val, uint32* address)
    {

    }
    void atomic_add_fetch_release(uint32 val, uint32* address)
    {

    }
    void atomic_add_fetch_acq_rel(uint32 val, uint32* address)
    {

    }
    void atomic_add_fetch_seq_cst(uint32 val, uint32* address)
    {

    }

    // int32
    void atomic_add_fetch_relaxed(int32 val, int32* address)
    {

    }
    void atomic_add_fetch_acquire(int32 val, int32* address)
    {

    }
    void atomic_add_fetch_release(int32 val, int32* address)
    {

    }
    void atomic_add_fetch_acq_rel(int32 val, int32* address)
    {

    }
    void atomic_add_fetch_seq_cst(int32 val, int32* address)
    {

    }

    // uint64
    void atomic_add_fetch_relaxed(uint64 val, uint64* address)
    {

    }
    void atomic_add_fetch_acquire(uint64 val, uint64* address)
    {

    }
    void atomic_add_fetch_release(uint64 val, uint64* address)
    {

    }
    void atomic_add_fetch_acq_rel(uint64 val, uint64* address)
    {

    }
    void atomic_add_fetch_seq_cst(uint64 val, uint64* address)
    {

    }

    // int64
    void atomic_add_fetch_relaxed(int64 val, int64* address)
    {

    }
    void atomic_add_fetch_acquire(int64 val, int64* address)
    {

    }
    void atomic_add_fetch_release(int64 val, int64* address)
    {

    }
    void atomic_add_fetch_acq_rel(int64 val, int64* address)
    {

    }
    void atomic_add_fetch_seq_cst(int64 val, int64* address)
    {

    }
  }
}