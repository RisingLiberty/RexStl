#pragma once

namespace rsl
{

  ////////////////////////////////////////////////////////////////////////////////
  //
  // bool atomic_compare_exchange_strong(rsl::atomic<T>*, T* expected, T desired)
  //
  template <typename T>
  REX_FORCE_INLINE bool atomic_compare_exchange_strong(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type* expected, typename rsl::atomic<T>::value_type desired)
  {
    return atomicObj->compare_exchange_strong(*expected, desired);
  }

  template <typename T, typename OrderSuccess, typename OrderFailure>
  REX_FORCE_INLINE bool atomic_compare_exchange_strong_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type* expected, typename rsl::atomic<T>::value_type desired, OrderSuccess orderSuccess, OrderFailure orderFailure)
  {
    return atomicObj->compare_exchange_strong(*expected, desired, orderSuccess, orderFailure);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // bool atomic_compare_exchange_weak(rsl::atomic<T>*, T* expected, T desired)
  //
  template <typename T>
  REX_FORCE_INLINE bool atomic_compare_exchange_weak(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type* expected, typename rsl::atomic<T>::value_type desired)
  {
    return atomicObj->compare_exchange_weak(*expected, desired);
  }

  template <typename T, typename OrderSuccess, typename OrderFailure>
  REX_FORCE_INLINE bool atomic_compare_exchange_weak_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type* expected, typename rsl::atomic<T>::value_type desired, OrderSuccess orderSuccess, OrderFailure orderFailure)
  {
    return atomicObj->compare_exchange_weak(*expected, desired, orderSuccess, orderFailure);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_fetch_xor(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_xor(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg)
  {
    return atomicObj->fetch_xor(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_xor_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg, Order order)
  {
    return atomicObj->fetch_xor(arg, order);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_xor_fetch(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_xor_fetch(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg)
  {
    return atomicObj->xor_fetch(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_xor_fetch_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg, Order order)
  {
    return atomicObj->xor_fetch(arg, order);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_fetch_or(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_or(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg)
  {
    return atomicObj->fetch_or(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_or_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg, Order order)
  {
    return atomicObj->fetch_or(arg, order);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_or_fetch(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_or_fetch(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg)
  {
    return atomicObj->or_fetch(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_or_fetch_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg, Order order)
  {
    return atomicObj->or_fetch(arg, order);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_fetch_and(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_and(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg)
  {
    return atomicObj->fetch_and(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_and_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg, Order order)
  {
    return atomicObj->fetch_and(arg, order);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_and_fetch(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_and_fetch(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg)
  {
    return atomicObj->and_fetch(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_and_fetch_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type arg, Order order)
  {
    return atomicObj->and_fetch(arg, order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_fetch_sub(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_sub(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg)
  {
    return atomicObj->fetch_sub(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_sub_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg, Order order)
  {
    return atomicObj->fetch_sub(arg, order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_sub_fetch(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_sub_fetch(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg)
  {
    return atomicObj->sub_fetch(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_sub_fetch_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg, Order order)
  {
    return atomicObj->sub_fetch(arg, order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_fetch_add(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_add(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg)
  {
    return atomicObj->fetch_add(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_fetch_add_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg, Order order)
  {
    return atomicObj->fetch_add(arg, order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_add_fetch(rsl::atomic<T>*, T arg)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_add_fetch(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg)
  {
    return atomicObj->add_fetch(arg);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_add_fetch_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::difference_type arg, Order order)
  {
    return atomicObj->add_fetch(arg, order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_exchange(rsl::atomic<T>*, T desired)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_exchange(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type desired)
  {
    return atomicObj->exchange(desired);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_exchange_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type desired, Order order)
  {
    return atomicObj->exchange(desired, order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_load(const rsl::atomic<T>*)
  //
  template <typename T>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_load(const rsl::atomic<T>* atomicObj)
  {
    return atomicObj->load();
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_load_explicit(const rsl::atomic<T>* atomicObj, Order order)
  {
    return atomicObj->load(order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // T atomic_load_cond(const rsl::atomic<T>*)
  //
  template <typename T, typename Predicate>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_load_cond(const rsl::atomic<T>* atomicObj, Predicate pred)
  {
    for(;;)
    {
      typename rsl::atomic<T>::value_type ret = atomicObj->load();

      if(pred(ret))
      {
        return ret;
      }

      rsl::cpu_pause();
    }
  }

  template <typename T, typename Predicate, typename Order>
  REX_FORCE_INLINE typename rsl::atomic<T>::value_type atomic_load_cond_explicit(const rsl::atomic<T>* atomicObj, Predicate pred, Order order)
  {
    for(;;)
    {
      typename rsl::atomic<T>::value_type ret = atomicObj->load(order);

      if(pred(ret))
      {
        return ret;
      }

      rsl::cpu_pause();
    }
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // void atomic_store(rsl::atomic<T>*, T)
  //
  template <typename T>
  REX_FORCE_INLINE void atomic_store(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type desired)
  {
    atomicObj->store(desired);
  }

  template <typename T, typename Order>
  REX_FORCE_INLINE void atomic_store_explicit(rsl::atomic<T>* atomicObj, typename rsl::atomic<T>::value_type desired, Order order)
  {
    atomicObj->store(desired, order);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // void rsl::atomic_thread_fence(Order)
  //
  template <typename Order>
  REX_FORCE_INLINE void atomic_thread_fence(Order /*unused*/)
  {
    REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(Order);
  }

  REX_FORCE_INLINE void atomic_thread_fence(rsl::internal::memory_order_relaxed_s /*unused*/)
  {
    rsl::atomic_thread_fence(rsl::memory_order::relaxed);
  }

  REX_FORCE_INLINE void atomic_thread_fence(rsl::internal::memory_order_acquire_s /*unused*/)
  {
    rsl::atomic_thread_fence(rsl::memory_order::acquire);
  }

  REX_FORCE_INLINE void atomic_thread_fence(rsl::internal::memory_order_release_s /*unused*/)
  {
    rsl::atomic_thread_fence(rsl::memory_order::release);
  }

  REX_FORCE_INLINE void atomic_thread_fence(rsl::internal::memory_order_acq_rel_s /*unused*/)
  {
    rsl::atomic_thread_fence(rsl::memory_order::acq_rel);
  }

  REX_FORCE_INLINE void atomic_thread_fence(rsl::internal::memory_order_seq_cst_s /*unused*/)
  {
    rsl::atomic_thread_fence(rsl::memory_order::seq_cst);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // void rsl::atomic_signal_fence(Order)
  //
  template <typename Order>
  REX_FORCE_INLINE void atomic_signal_fence(Order /*unused*/)
  {
    REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(Order);
  }

  REX_FORCE_INLINE void atomic_signal_fence(rsl::internal::memory_order_relaxed_s /*unused*/)
  {
    rsl::atomic_signal_fence(rsl::memory_order::relaxed);
  }

  REX_FORCE_INLINE void atomic_signal_fence(rsl::internal::memory_order_acquire_s /*unused*/)
  {
    rsl::atomic_signal_fence(rsl::memory_order::acquire);
  }

  REX_FORCE_INLINE void atomic_signal_fence(rsl::internal::memory_order_release_s /*unused*/)
  {
    rsl::atomic_signal_fence(rsl::memory_order::release);
  }

  REX_FORCE_INLINE void atomic_signal_fence(rsl::internal::memory_order_acq_rel_s /*unused*/)
  {
    rsl::atomic_signal_fence(rsl::memory_order::acq_rel);
  }

  REX_FORCE_INLINE void atomic_signal_fence(rsl::internal::memory_order_seq_cst_s /*unused*/)
  {
    rsl::atomic_signal_fence(rsl::memory_order::seq_cst);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // void rsl::compiler_barrier()
  //
  // REX_FORCE_INLINE void compiler_barrier()
  //{
  //  REX_ATOMIC_COMPILER_BARRIER();
  //}

  /////////////////////////////////////////////////////////////////////////////////
  //
  // void rsl::compiler_barrier_data_dependency(const T&)
  //
  template <typename T>
  REX_FORCE_INLINE void compiler_barrier_data_dependency(const T& val)
  {
    rsl::compiler_barrier(&val);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  // void rsl::cpu_pause()
  //
  // REX_FORCE_INLINE void cpu_pause()
  //{
  //  rsl::cpu_pause();
  //}

  /////////////////////////////////////////////////////////////////////////////////
  //
  // bool rsl::atomic_is_lock_free(rsl::atomic<T>*)
  //
  template <typename T>
  REX_FORCE_INLINE bool atomic_is_lock_free(const rsl::atomic<T>* atomicObj)
  {
    return atomicObj->is_lock_free();
  }

} // namespace rsl
