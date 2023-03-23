

#ifndef REX_ATOMIC_INTERNAL_FLAG_STANDALONE_H
#define REX_ATOMIC_INTERNAL_FLAG_STANDALONE_H

#pragma once

namespace rsl
{

  ////////////////////////////////////////////////////////////////////////////////
  //
  // bool atomic_flag_test_and_set(rsl::atomic<T>*)
  //
  REX_FORCE_INLINE bool atomic_flag_test_and_set(rsl::atomic_flag* atomicObj)
  {
    return atomicObj->test_and_set();
  }

  template <typename Order>
  REX_FORCE_INLINE bool atomic_flag_test_and_set_explicit(rsl::atomic_flag* atomicObj, Order order)
  {
    return atomicObj->test_and_set(order);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // bool atomic_flag_clear(rsl::atomic<T>*)
  //
  REX_FORCE_INLINE void atomic_flag_clear(rsl::atomic_flag* atomicObj)
  {
    atomicObj->clear();
  }

  template <typename Order>
  REX_FORCE_INLINE void atomic_flag_clear_explicit(rsl::atomic_flag* atomicObj, Order order)
  {
    atomicObj->clear(order);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // bool atomic_flag_test(rsl::atomic<T>*)
  //
  REX_FORCE_INLINE bool atomic_flag_test(rsl::atomic_flag* atomicObj)
  {
    return atomicObj->test();
  }

  template <typename Order>
  REX_FORCE_INLINE bool atomic_flag_test_explicit(rsl::atomic_flag* atomicObj, Order order)
  {
    return atomicObj->test(order);
  }

} // namespace rsl

#endif /* REX_ATOMIC_INTERNAL_FLAG_STANDALONE_H */
