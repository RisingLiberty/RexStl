// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_atomic.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/atomic.h"

namespace rsl::test
{
  inline namespace v1
  {
    class AtomicStandaloneBasicTest
    {
    public:

      int RunTest()
      {
        AtomicSignalFence();

        AtomicThreadFence();

        AtomicCpuPause();

        AtomicCompilerBarrier();

        return nErrorCount;
      }

    private:

      void AtomicSignalFence();

      void AtomicThreadFence();

      void AtomicCpuPause();

      void AtomicCompilerBarrier();

    private:

      int nErrorCount = 0;
    };

    void AtomicStandaloneBasicTest::AtomicSignalFence()
    {
      rsl::atomic_signal_fence(rsl::memory_order_relaxed);

      rsl::atomic_signal_fence(rsl::memory_order_acquire);

      rsl::atomic_signal_fence(rsl::memory_order_release);

      rsl::atomic_signal_fence(rsl::memory_order_acq_rel);

      rsl::atomic_signal_fence(rsl::memory_order_seq_cst);
    }

    void AtomicStandaloneBasicTest::AtomicThreadFence()
    {
      rsl::atomic_thread_fence(rsl::memory_order_relaxed);

      rsl::atomic_thread_fence(rsl::memory_order_acquire);

      rsl::atomic_thread_fence(rsl::memory_order_release);

      rsl::atomic_thread_fence(rsl::memory_order_acq_rel);

      rsl::atomic_thread_fence(rsl::memory_order_seq_cst);
    }

    void AtomicStandaloneBasicTest::AtomicCpuPause()
    {
      rsl::cpu_pause();
    }

    void AtomicStandaloneBasicTest::AtomicCompilerBarrier()
    {
      rsl::compiler_barrier();

      {
        bool ret = false;
        rsl::compiler_barrier_data_dependency(ret);
      }
    }

    class AtomicFlagBasicTest
    {
    public:

      using AtomicType = rsl::atomic_flag;
      using BoolType = bool;

      int RunTest()
      {
        TestAtomicFlagCtor();

        TestAtomicFlagClear();

        TestAtomicFlagTestAndSet();

        TestAtomicFlagTest();

        TestAllMemoryOrders();

        TestAtomicFlagStandalone();

        return nErrorCount;
      }

    private:

      void TestAtomicFlagCtor();

      void TestAtomicFlagClear();

      void TestAtomicFlagTestAndSet();

      void TestAtomicFlagTest();

      void TestAllMemoryOrders();

      void TestAtomicFlagStandalone();

    private:

      int nErrorCount = 0;
    };

    void AtomicFlagBasicTest::TestAtomicFlagCtor()
    {
      {
        AtomicType atomic;

        CHECK(atomic.test(rsl::memory_order_relaxed) == false);
      }

      {
        AtomicType atomic{ false };

        CHECK(atomic.test(rsl::memory_order_relaxed) == false);
      }

      {
        AtomicType atomic{ true };

        CHECK(atomic.test(rsl::memory_order_relaxed) == true);
      }
    }

    void AtomicFlagBasicTest::TestAtomicFlagClear()
    {
      {
        AtomicType atomic;

        atomic.clear(rsl::memory_order_relaxed);

        CHECK(atomic.test(rsl::memory_order_relaxed) == false);
      }

      {
        AtomicType atomic{ true };

        atomic.clear(rsl::memory_order_relaxed);

        CHECK(atomic.test(rsl::memory_order_relaxed) == false);
      }
    }

    void AtomicFlagBasicTest::TestAtomicFlagTestAndSet()
    {
      {
        AtomicType atomic;

        BoolType ret = atomic.test_and_set(rsl::memory_order_relaxed);

        CHECK(ret == false);

        CHECK(atomic.test(rsl::memory_order_relaxed) == true);
      }

      {
        AtomicType atomic{ true };

        BoolType ret = atomic.test_and_set(rsl::memory_order_relaxed);

        CHECK(ret == true);

        CHECK(atomic.test(rsl::memory_order_relaxed) == true);
      }
    }

    void AtomicFlagBasicTest::TestAtomicFlagTest()
    {
      {
        AtomicType atomic;

        CHECK(atomic.test(rsl::memory_order_relaxed) == false);
      }

      {
        AtomicType atomic{ true };

        CHECK(atomic.test(rsl::memory_order_relaxed) == true);
      }
    }

    void AtomicFlagBasicTest::TestAllMemoryOrders()
    {
      {
        AtomicType atomic;

        atomic.clear();

        atomic.clear(rsl::memory_order_relaxed);

        atomic.clear(rsl::memory_order_release);

        atomic.clear(rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        atomic.test_and_set();

        atomic.test_and_set(rsl::memory_order_relaxed);

        atomic.test_and_set(rsl::memory_order_acquire);

        atomic.test_and_set(rsl::memory_order_release);

        atomic.test_and_set(rsl::memory_order_acq_rel);

        atomic.test_and_set(rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType ret = atomic.test();

        ret = atomic.test(rsl::memory_order_relaxed);

        ret = atomic.test(rsl::memory_order_acquire);

        ret = atomic.test(rsl::memory_order_seq_cst);
      }
    }

    void AtomicFlagBasicTest::TestAtomicFlagStandalone()
    {
      {
        AtomicType atomic;

        BoolType ret = atomic_flag_test_and_set(&atomic);

        ret = atomic_flag_test_and_set_explicit(&atomic, rsl::memory_order_relaxed);

        ret = atomic_flag_test_and_set_explicit(&atomic, rsl::memory_order_acquire);

        ret = atomic_flag_test_and_set_explicit(&atomic, rsl::memory_order_release);

        ret = atomic_flag_test_and_set_explicit(&atomic, rsl::memory_order_acq_rel);

        ret = atomic_flag_test_and_set_explicit(&atomic, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        atomic_flag_clear(&atomic);

        atomic_flag_clear_explicit(&atomic, rsl::memory_order_relaxed);

        atomic_flag_clear_explicit(&atomic, rsl::memory_order_release);

        atomic_flag_clear_explicit(&atomic, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType ret = atomic_flag_test(&atomic);

        ret = atomic_flag_test_explicit(&atomic, rsl::memory_order_relaxed);

        ret = atomic_flag_test_explicit(&atomic, rsl::memory_order_acquire);

        ret = atomic_flag_test_explicit(&atomic, rsl::memory_order_seq_cst);
      }
    }

    class AtomicVoidPointerBasicTest
    {
    public:

      using AtomicType = rsl::atomic<void*>;
      using PtrType = void*;

      int RunTest()
      {
        TestAtomicCtor();

        TestAssignmentOperators();

        TestIsLockFree();

        TestStore();

        TestLoad();

        TestExchange();

        TestCompareExchangeWeak();

        TestCompareExchangeStrong();

        TestAllMemoryOrders();

        return nErrorCount;
      }

    private:

      void TestAtomicCtor();

      void TestAssignmentOperators();

      void TestIsLockFree();

      void TestStore();

      void TestLoad();

      void TestExchange();

      void TestCompareExchangeWeak();

      void TestCompareExchangeStrong();

      void TestAllMemoryOrders();

    private:

      int nErrorCount = 0;
    };

    void AtomicVoidPointerBasicTest::TestAtomicCtor()
    {
      {
        AtomicType atomic;

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }

      {
        AtomicType atomic{ (PtrType)0x04 };

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x04);
      }
    }

    void AtomicVoidPointerBasicTest::TestAssignmentOperators()
    {
      {
        AtomicType atomic;

        PtrType ret = atomic = (PtrType)0x04;

        CHECK(ret == (PtrType)0x04);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x04);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic = (PtrType)0x0;

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }
    }

    void AtomicVoidPointerBasicTest::TestIsLockFree()
    {
      {
        AtomicType atomic;

        CHECK(atomic.is_lock_free() == true);

        CHECK(atomic.is_always_lock_free == true);
      }
    }

    void AtomicVoidPointerBasicTest::TestStore()
    {
      {
        PtrType val = (PtrType)0x0;
        AtomicType atomic;

        atomic.store(val, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == val);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic;

        atomic.store(val, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == val);
      }
    }

    void AtomicVoidPointerBasicTest::TestLoad()
    {
      {
        AtomicType atomic{ (PtrType)0x4 };

        PtrType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic == (PtrType)0x4);
      }
    }

    void AtomicVoidPointerBasicTest::TestExchange()
    {
      {
        AtomicType atomic;

        PtrType ret = atomic.exchange((PtrType)0x4, rsl::memory_order_release);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }
    }

    void AtomicVoidPointerBasicTest::TestCompareExchangeWeak()
    {
      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x0;
        bool ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        if (ret)
        {
          CHECK(ret == true);
          CHECK(observed == (PtrType)0x0);
          CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
        }
      }

      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x4;
        bool ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }
    }

    void AtomicVoidPointerBasicTest::TestCompareExchangeStrong()
    {
      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x0;
        bool ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        CHECK(ret == true);
        CHECK(observed == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x4;
        bool ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }
    }

    void AtomicVoidPointerBasicTest::TestAllMemoryOrders()
    {
      {
        AtomicType atomic;
        PtrType val = (PtrType)0x4;

        atomic.store(val);

        atomic.store(val, rsl::memory_order_relaxed);

        atomic.store(val, rsl::memory_order_release);

        atomic.store(val, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.load();

        ret = atomic.load(rsl::memory_order_relaxed);

        ret = atomic.load(rsl::memory_order_acquire);

        ret = atomic.load(rsl::memory_order_seq_cst);

        ret = atomic.load(rsl::memory_order_read_depends);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.exchange((PtrType)0x4);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_relaxed);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_acquire);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_release);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_acq_rel);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;

        bool ret = atomic.compare_exchange_weak(observed, (PtrType)0x4);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_release);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;

        bool ret = atomic.compare_exchange_strong(observed, (PtrType)0x4);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_release);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;
        bool ret;

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;
        bool ret;

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }
    }

    class AtomicPointerBasicTest
    {
    public:

      using AtomicType = rsl::atomic<uint32_t*>;
      using PtrType = uint32_t*;

      int RunTest()
      {
        TestAtomicCtor();

        TestAssignmentOperators();

        TestIsLockFree();

        TestStore();

        TestLoad();

        TestExchange();

        TestCompareExchangeWeak();

        TestCompareExchangeStrong();

        TestAllMemoryOrders();

        TestFetchAdd();
        TestAddFetch();

        TestFetchSub();
        TestSubFetch();

        TestAtomicPointerStandalone();

        return nErrorCount;
      }

    private:

      void TestAtomicCtor();

      void TestAssignmentOperators();

      void TestIsLockFree();

      void TestStore();

      void TestLoad();

      void TestExchange();

      void TestCompareExchangeWeak();

      void TestCompareExchangeStrong();

      void TestAllMemoryOrders();

      void TestFetchAdd();
      void TestAddFetch();

      void TestFetchSub();
      void TestSubFetch();

      void TestAtomicPointerStandalone();

    private:

      int nErrorCount = 0;
    };

    void AtomicPointerBasicTest::TestAtomicCtor()
    {
      {
        AtomicType atomic{};

        PtrType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == nullptr);
      }

      {
        AtomicType atomic{ (PtrType)0x4 };

        PtrType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);
      }
    }

    void AtomicPointerBasicTest::TestAssignmentOperators()
    {
      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType expected = (PtrType)0x8;

        PtrType ret = atomic = expected;

        CHECK(ret == expected);

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        PtrType val = (PtrType)0x0;
        AtomicType atomic{ val };

        PtrType ret = atomic = val;

        CHECK(ret == val);

        CHECK(atomic.load(rsl::memory_order_relaxed) == val);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType expected = (PtrType)0x8;
        PtrType ret = ++atomic;

        CHECK(ret == expected);

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        PtrType val = (PtrType)0x4;

        AtomicType atomic{ val };

        PtrType expected = (PtrType)0x8;
        PtrType ret = atomic++;

        CHECK(ret == val);

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType expected = (PtrType)0x10;
        PtrType ret = atomic += 3;

        CHECK(ret == expected);

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType expected = (PtrType)0x4;
        PtrType ret = atomic += 0;

        CHECK(ret == expected);

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType expected = (PtrType)0x0;
        PtrType ret = atomic -= 1;

        CHECK(ret == expected);

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType expected = (PtrType)0x4;
        PtrType ret = atomic -= 0;

        CHECK(ret == expected);

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }
    }

    void AtomicPointerBasicTest::TestIsLockFree()
    {
      {
        AtomicType atomic;

        CHECK(atomic.is_lock_free() == true);

        CHECK(atomic.is_always_lock_free == true);
      }
    }

    void AtomicPointerBasicTest::TestStore()
    {
      {
        PtrType val = (PtrType)0x0;
        AtomicType atomic;

        atomic.store(val, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == val);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic;

        atomic.store(val, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == val);
      }
    }

    void AtomicPointerBasicTest::TestLoad()
    {
      {
        AtomicType atomic{ (PtrType)0x4 };

        PtrType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic == (PtrType)0x4);
      }
    }

    void AtomicPointerBasicTest::TestCompareExchangeWeak()
    {
      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x0;
        bool ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        if (ret)
        {
          CHECK(ret == true);
          CHECK(observed == (PtrType)0x0);
          CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
        }
      }

      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x4;
        bool ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }
    }

    void AtomicPointerBasicTest::TestCompareExchangeStrong()
    {
      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x0;
        bool ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        CHECK(ret == true);
        CHECK(observed == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType observed = (PtrType)0x4;
        bool ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }
    }

    void AtomicPointerBasicTest::TestExchange()
    {
      {
        AtomicType atomic;

        PtrType ret = atomic.exchange((PtrType)0x4, rsl::memory_order_release);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }
    }

    void AtomicPointerBasicTest::TestAllMemoryOrders()
    {
      {
        AtomicType atomic;
        PtrType val = (PtrType)0x4;

        atomic.store(val);

        atomic.store(val, rsl::memory_order_relaxed);

        atomic.store(val, rsl::memory_order_release);

        atomic.store(val, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.load();

        ret = atomic.load(rsl::memory_order_relaxed);

        ret = atomic.load(rsl::memory_order_acquire);

        ret = atomic.load(rsl::memory_order_seq_cst);

        ret = atomic.load(rsl::memory_order_read_depends);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.fetch_add(0);

        ret = atomic.fetch_add(0, rsl::memory_order_relaxed);

        ret = atomic.fetch_add(0, rsl::memory_order_acquire);

        ret = atomic.fetch_add(0, rsl::memory_order_release);

        ret = atomic.fetch_add(0, rsl::memory_order_acq_rel);

        ret = atomic.fetch_add(0, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.fetch_sub(0);

        ret = atomic.fetch_sub(0, rsl::memory_order_relaxed);

        ret = atomic.fetch_sub(0, rsl::memory_order_acquire);

        ret = atomic.fetch_sub(0, rsl::memory_order_release);

        ret = atomic.fetch_sub(0, rsl::memory_order_acq_rel);

        ret = atomic.fetch_sub(0, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.add_fetch(0);

        ret = atomic.add_fetch(0, rsl::memory_order_relaxed);

        ret = atomic.add_fetch(0, rsl::memory_order_acquire);

        ret = atomic.add_fetch(0, rsl::memory_order_release);

        ret = atomic.add_fetch(0, rsl::memory_order_acq_rel);

        ret = atomic.add_fetch(0, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.sub_fetch(0);

        ret = atomic.sub_fetch(0, rsl::memory_order_relaxed);

        ret = atomic.sub_fetch(0, rsl::memory_order_acquire);

        ret = atomic.sub_fetch(0, rsl::memory_order_release);

        ret = atomic.sub_fetch(0, rsl::memory_order_acq_rel);

        ret = atomic.sub_fetch(0, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic.exchange((PtrType)0x4);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_relaxed);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_acquire);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_release);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_acq_rel);

        ret = atomic.exchange((PtrType)0x4, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;

        bool ret = atomic.compare_exchange_weak(observed, (PtrType)0x4);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_release);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;

        bool ret = atomic.compare_exchange_strong(observed, (PtrType)0x4);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_release);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;
        bool ret;

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;
        PtrType observed = (PtrType)0x0;
        bool ret;

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, (PtrType)0x4, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }
    }

    void AtomicPointerBasicTest::TestFetchAdd()
    {
      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.fetch_add(1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x8);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.fetch_add(0, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }
    }

    void AtomicPointerBasicTest::TestAddFetch()
    {
      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.add_fetch(1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x8);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x8);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.add_fetch(0, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }
    }

    void AtomicPointerBasicTest::TestFetchSub()
    {
      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.fetch_sub(1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.fetch_sub(0, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }
    }

    void AtomicPointerBasicTest::TestSubFetch()
    {
      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.sub_fetch(1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }

      {
        PtrType val = (PtrType)0x4;
        AtomicType atomic{ val };

        PtrType ret = atomic.sub_fetch(0, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }
    }

    void AtomicPointerBasicTest::TestAtomicPointerStandalone()
    {
      {
        AtomicType atomic;

        CHECK(atomic_is_lock_free(&atomic) == true);
      }

      {
        AtomicType atomic;
        PtrType val = (PtrType)0x4;

        atomic_store(&atomic, val);

        CHECK(atomic.load(rsl::memory_order_relaxed) == val);
      }

      {
        AtomicType atomic;
        PtrType val = (PtrType)0x4;

        atomic_store_explicit(&atomic, val, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == val);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_load(&atomic);

        CHECK(ret == (PtrType)0x0);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_load_explicit(&atomic, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x0);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_load_cond(&atomic, [](PtrType /*val*/) { return true; });

        CHECK(ret == (PtrType)0x0);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_load_cond_explicit(&atomic, [](PtrType /*val*/) { return true; }, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x0);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_exchange(&atomic, (PtrType)0x4);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_exchange_explicit(&atomic, (PtrType)0x4, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_add_fetch(&atomic, 1);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_add_fetch_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_fetch_add(&atomic, 1);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType ret = atomic_fetch_add_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic{ (PtrType)0x4 };

        PtrType ret = atomic_fetch_sub(&atomic, 1);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }

      {
        AtomicType atomic{ (PtrType)0x4 };

        PtrType ret = atomic_fetch_sub_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x4);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }

      {
        AtomicType atomic{ (PtrType)0x4 };

        PtrType ret = atomic_sub_fetch(&atomic, 1);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }

      {
        AtomicType atomic{ (PtrType)0x4 };

        PtrType ret = atomic_sub_fetch_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == (PtrType)0x0);

        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x0);
      }

      {
        AtomicType atomic;

        PtrType expected = (PtrType)0x0;
        bool ret = atomic_compare_exchange_strong(&atomic, &expected, (PtrType)0x4);

        CHECK(ret == true);

        CHECK(expected == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType expected = (PtrType)0x0;
        bool ret = atomic_compare_exchange_strong_explicit(&atomic, &expected, (PtrType)0x4, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        CHECK(ret == true);

        CHECK(expected == (PtrType)0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
      }

      {
        AtomicType atomic;

        PtrType expected = (PtrType)0x0;
        bool ret = atomic_compare_exchange_weak(&atomic, &expected, (PtrType)0x4);

        if (ret)
        {
          CHECK(ret == true);

          CHECK(expected == (PtrType)0x0);
          CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
        }
      }

      {
        AtomicType atomic;

        PtrType expected = (PtrType)0x0;
        bool ret = atomic_compare_exchange_weak_explicit(&atomic, &expected, (PtrType)0x4, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        if (ret)
        {
          CHECK(ret == true);

          CHECK(expected == (PtrType)0x0);
          CHECK(atomic.load(rsl::memory_order_relaxed) == (PtrType)0x4);
        }
      }
    }

    struct AtomicNonTriviallyConstructible
    {
      AtomicNonTriviallyConstructible()
        : a(0)
        , b(0)
      {
      }

      AtomicNonTriviallyConstructible(uint16_t a, uint16_t b)
        : a(a)
        , b(b)
      {
      }

      friend bool operator==(const AtomicNonTriviallyConstructible& a, const AtomicNonTriviallyConstructible& b)
      {
        return a.a == b.a && a.b == b.b;
      }

      uint16_t a;
      uint16_t b;
    };

    struct AtomicNonTriviallyConstructibleNoExcept
    {
      AtomicNonTriviallyConstructibleNoExcept() noexcept
        : a(0)
        , b(0)
      {
      }

      AtomicNonTriviallyConstructibleNoExcept(uint16_t a, uint16_t b) noexcept
        : a(a)
        , b(b)
      {
      }

      friend bool operator==(const AtomicNonTriviallyConstructibleNoExcept& a, const AtomicNonTriviallyConstructibleNoExcept& b)
      {
        return a.a == b.a && a.b == b.b;
      }

      uint16_t a;
      uint16_t b;
    };

    struct AtomicUserType16
    {
      uint8_t a;
      uint8_t b;

      friend bool operator==(const AtomicUserType16& a, const AtomicUserType16& b)
      {
        return (a.a == b.a) && (a.b == b.b);
      }
    };

    struct AtomicUserType128
    {
      uint32_t a;
      uint32_t b;
      uint32_t c;
      uint32_t d;

      AtomicUserType128() = default;

      AtomicUserType128(const AtomicUserType128&) = default;

      AtomicUserType128(uint32_t a, uint32_t b)
        : a(a)
        , b(b)
        , c(0)
        , d(0)
      {
      }

      AtomicUserType128& operator=(const AtomicUserType128&) = default;

      friend bool operator==(const AtomicUserType128& a, const AtomicUserType128& b)
      {
        return (a.a == b.a) && (a.b == b.b) && (a.c == b.c) && (a.d == b.d);
      }
    };

    template <typename T>
    class AtomicUserTypeBasicTest
    {
    public:

      using AtomicType = rsl::atomic<T>;
      using UserType = T;

      int RunTest()
      {
        TestAtomicCtor();

        TestAssignmentOperators();

        TestIsLockFree();

        TestStore();

        TestLoad();

        TestExchange();

        TestCompareExchangeWeak();

        TestCompareExchangeStrong();

        TestAllMemoryOrders();

        return nErrorCount;
      }

    private:

      void TestAtomicCtor();

      void TestAssignmentOperators();

      void TestIsLockFree();

      void TestStore();

      void TestLoad();

      void TestExchange();

      void TestCompareExchangeWeak();

      void TestCompareExchangeStrong();

      void TestAllMemoryOrders();

    private:

      int nErrorCount = 0;
    };

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestAtomicCtor()
    {
      {
        AtomicType atomic;
        UserType expected{ 0, 0 };

        UserType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == expected);
      }

      {
        AtomicType atomic{ {5, 8} };
        UserType expected{ 5, 8 };

        UserType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == expected);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestAssignmentOperators()
    {
      {
        AtomicType atomic;
        UserType expected{ 5, 6 };

        atomic = { 5, 6 };

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        AtomicType atomic;
        UserType expected{ 0, 0 };

        atomic = { 0, 0 };

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestIsLockFree()
    {
      {
        AtomicType atomic;

        CHECK(atomic.is_lock_free() == true);

        CHECK(AtomicType::is_always_lock_free == true);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestStore()
    {
      {
        AtomicType atomic;
        UserType expected{ 5, 6 };

        atomic.store(expected, rsl::memory_order_relaxed);

        UserType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == expected);
      }

      {
        AtomicType atomic;
        UserType expected{ 5, 6 };

        atomic.store({ 5, 6 }, rsl::memory_order_relaxed);

        UserType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == expected);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestLoad()
    {
      {
        AtomicType atomic;
        UserType expected{ 0, 0 };

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);

        CHECK(atomic == expected);
      }

      {
        AtomicType atomic{ {5, 6} };
        UserType expected{ 5, 6 };

        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);

        CHECK(atomic == expected);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestExchange()
    {
      {
        AtomicType atomic;

        UserType expected{ 0, 0 };

        UserType ret = atomic.exchange({ 0, 0 }, rsl::memory_order_relaxed);

        CHECK(ret == expected);
      }

      {
        AtomicType atomic;
        UserType expected{ 0, 0 };
        UserType expected2{ 0, 1 };

        UserType ret = atomic.exchange({ 0, 1 }, rsl::memory_order_relaxed);

        CHECK(ret == expected);
        CHECK(atomic.load(rsl::memory_order_relaxed) == expected2);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestCompareExchangeWeak()
    {
      {
        AtomicType atomic;

        UserType observed{ 0, 0 };
        bool ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_relaxed);

        UserType expected{ 0, 0 };
        if (ret)
        {
          CHECK(ret == true);
          CHECK(observed == expected);
          CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
        }
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 0 };
        bool ret = atomic.compare_exchange_weak(observed, { 0, 1 }, rsl::memory_order_relaxed);

        UserType expected{ 0, 1 };
        UserType expected2{ 0, 0 };
        if (ret)
        {
          CHECK(ret == true);
          CHECK(observed == expected2);
          CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
        }
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 1 };
        bool ret = atomic.compare_exchange_weak(observed, { 0, 1 }, rsl::memory_order_relaxed);

        UserType expected{ 0, 0 };

        CHECK(ret == false);
        CHECK(observed == expected);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestCompareExchangeStrong()
    {
      {
        AtomicType atomic;

        UserType observed{ 0, 0 };
        bool ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_relaxed);

        UserType expected{ 0, 0 };

        CHECK(ret == true);
        CHECK(observed == expected);
        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 0 };
        bool ret = atomic.compare_exchange_strong(observed, { 0, 1 }, rsl::memory_order_relaxed);

        UserType expected{ 0, 1 };
        UserType expected2{ 0, 0 };

        CHECK(ret == true);
        CHECK(observed == expected2);
        CHECK(atomic.load(rsl::memory_order_relaxed) == expected);
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 1 };
        bool ret = atomic.compare_exchange_strong(observed, { 0, 1 }, rsl::memory_order_relaxed);

        UserType expected{ 0, 0 };

        CHECK(ret == false);
        CHECK(observed == expected);
      }
    }

    template <typename T>
    void AtomicUserTypeBasicTest<T>::TestAllMemoryOrders()
    {
      {
        AtomicType atomic;
        UserType val{ 0, 1 };

        atomic.store(val);

        atomic.store(val, rsl::memory_order_relaxed);

        atomic.store(val, rsl::memory_order_release);

        atomic.store(val, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        UserType ret = atomic.load();

        ret = atomic.load(rsl::memory_order_relaxed);

        ret = atomic.load(rsl::memory_order_acquire);

        ret = atomic.load(rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        UserType ret = atomic.exchange({ 0, 1 });

        ret = atomic.exchange({ 0, 0 }, rsl::memory_order_relaxed);

        ret = atomic.exchange({ 0, 0 }, rsl::memory_order_acquire);

        ret = atomic.exchange({ 0, 0 }, rsl::memory_order_release);

        ret = atomic.exchange({ 0, 0 }, rsl::memory_order_acq_rel);

        ret = atomic.exchange({ 0, 0 }, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 0 };

        bool ret = atomic.compare_exchange_weak(observed, { 0, 0 });

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_release);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 0 };

        bool ret = atomic.compare_exchange_strong(observed, { 0, 0 });

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_release);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 0 };
        bool ret;

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, { 0, 0 }, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        UserType observed{ 0, 0 };
        bool ret;

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, { 0, 0 }, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }
    }


    class AtomicBoolBasicTest
    {
    public:

      using AtomicType = rsl::atomic<bool>;
      using BoolType = bool;

      int RunTest()
      {
        TestAtomicCtor();

        TestAssignmentOperators();

        TestIsLockFree();

        TestStore();

        TestLoad();

        TestExchange();

        TestCompareExchangeWeak();

        TestCompareExchangeStrong();

        TestAllMemoryOrders();

        return nErrorCount;
      }

    private:

      void TestAtomicCtor();

      void TestAssignmentOperators();

      void TestIsLockFree();

      void TestStore();

      void TestLoad();

      void TestExchange();

      void TestCompareExchangeWeak();

      void TestCompareExchangeStrong();

      void TestAllMemoryOrders();

    private:

      int nErrorCount = 0;
    };

    void AtomicBoolBasicTest::TestAtomicCtor()
    {
      {
        AtomicType atomic{ false };

        BoolType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == false);
      }

      {
        AtomicType atomic{ true };

        BoolType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == true);
      }

      {
        AtomicType atomic;

        BoolType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == false);
      }

      {
        AtomicType atomic{};

        BoolType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == false);
      }
    }

    void AtomicBoolBasicTest::TestAssignmentOperators()
    {
      {
        AtomicType atomic;

        BoolType ret = atomic = true;

        CHECK(ret == true);

        CHECK(atomic.load(rsl::memory_order_relaxed) == true);
      }
    }

    void AtomicBoolBasicTest::TestIsLockFree()
    {
      {
        AtomicType atomic;

        bool ret = atomic.is_lock_free();

        CHECK(ret == true);

        CHECK(AtomicType::is_always_lock_free == true);
      }
    }

    void AtomicBoolBasicTest::TestStore()
    {
      {
        AtomicType atomic;

        atomic.store(true, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == true);
      }
    }

    void AtomicBoolBasicTest::TestLoad()
    {
      {
        AtomicType atomic;

        CHECK(atomic.load(rsl::memory_order_relaxed) == false);
      }

      {
        AtomicType atomic{ true };

        CHECK(atomic.load(rsl::memory_order_relaxed) == true);
      }
    }

    void AtomicBoolBasicTest::TestExchange()
    {
      {
        AtomicType atomic;

        BoolType ret = atomic.exchange(false, rsl::memory_order_relaxed);

        CHECK(ret == false);

        CHECK(atomic.load(rsl::memory_order_relaxed) == false);
      }

      {
        AtomicType atomic;

        BoolType ret = atomic.exchange(true, rsl::memory_order_relaxed);

        CHECK(ret == false);

        CHECK(atomic.load(rsl::memory_order_relaxed) == true);
      }
    }

    void AtomicBoolBasicTest::TestCompareExchangeWeak()
    {
      {
        AtomicType atomic{ false };

        BoolType observed = false;
        bool ret = atomic.compare_exchange_weak(observed, false, rsl::memory_order_relaxed);

        if (ret)
        {
          CHECK(ret == true);
          CHECK(observed == false);
          CHECK(atomic.load(rsl::memory_order_relaxed) == false);
        }
      }

      {
        AtomicType atomic{ false };

        BoolType observed = false;
        bool ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_relaxed);

        if (ret)
        {
          CHECK(ret == true);
          CHECK(observed == false);
          CHECK(atomic.load(rsl::memory_order_relaxed) == true);
        }
      }

      {
        AtomicType atomic{ false };

        BoolType observed = true;
        bool ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == false);
      }
    }

    void AtomicBoolBasicTest::TestCompareExchangeStrong()
    {
      {
        AtomicType atomic{ false };

        BoolType observed = false;
        bool ret = atomic.compare_exchange_weak(observed, false, rsl::memory_order_relaxed);

        CHECK(ret == true);
        CHECK(observed == false);
        CHECK(atomic.load(rsl::memory_order_relaxed) == false);
      }

      {
        AtomicType atomic{ false };

        BoolType observed = false;
        bool ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_relaxed);

        CHECK(ret == true);
        CHECK(observed == false);
        CHECK(atomic.load(rsl::memory_order_relaxed) == true);
      }

      {
        AtomicType atomic{ false };

        BoolType observed = true;
        bool ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == false);
      }
    }

    void AtomicBoolBasicTest::TestAllMemoryOrders()
    {
      {
        AtomicType atomic;

        atomic.store(true);

        atomic.store(true, rsl::memory_order_relaxed);

        atomic.store(true, rsl::memory_order_release);

        atomic.store(true, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType ret = atomic.load();

        ret = atomic.load(rsl::memory_order_relaxed);

        ret = atomic.load(rsl::memory_order_acquire);

        ret = atomic.load(rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType ret = atomic.exchange(true);

        ret = atomic.exchange(true, rsl::memory_order_relaxed);

        ret = atomic.exchange(true, rsl::memory_order_acquire);

        ret = atomic.exchange(true, rsl::memory_order_release);

        ret = atomic.exchange(true, rsl::memory_order_acq_rel);

        ret = atomic.exchange(true, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType observed = false;
        bool ret = atomic.compare_exchange_weak(observed, true);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_release);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType observed = false;
        bool ret = atomic.compare_exchange_strong(observed, true);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_release);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType observed = false;
        bool ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, true, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic;

        BoolType observed = false;
        bool ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_acquire, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_acquire, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_release, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_acq_rel, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_acq_rel, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_seq_cst, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_seq_cst, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, true, rsl::memory_order_seq_cst, rsl::memory_order_seq_cst);
      }
    }


    template <typename T>
    class AtomicIntegralBasicTest
    {
    public:

      using AtomicType = rsl::atomic<T>;
      using IntegralType = T;

      int RunTest()
      {
        TestAtomicCtor();

        TestAtomicFetchAdd();
        TestAtomicAddFetch();

        TestAtomicFetchSub();
        TestAtomicSubFetch();

        TestAtomicFetchAnd();
        TestAtomicAndFetch();

        TestAtomicFetchOr();
        TestAtomicOrFetch();

        TestAtomicFetchXor();
        TestAtomicXorFetch();

        TestAssignmentOperators();

        TestIsLockFree();

        TestStore();

        TestLoad();

        TestExchange();

        TestCompareExchangeWeak();

        TestCompareExchangeStrong();

        TestAllMemoryOrders();

        TestAtomicStandalone();

        return nErrorCount;
      }

    private:

      void TestAtomicCtor();

      void TestAtomicFetchAdd();
      void TestAtomicAddFetch();

      void TestAtomicFetchSub();
      void TestAtomicSubFetch();

      void TestAtomicFetchAnd();
      void TestAtomicAndFetch();

      void TestAtomicFetchOr();
      void TestAtomicOrFetch();

      void TestAtomicFetchXor();
      void TestAtomicXorFetch();

      void TestAssignmentOperators();

      void TestIsLockFree();

      void TestStore();

      void TestLoad();

      void TestExchange();

      void TestCompareExchangeWeak();

      void TestCompareExchangeStrong();

      void TestAllMemoryOrders();

      void TestAtomicStandalone();

    private:

      int nErrorCount = 0;
    };

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicCtor()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }

      {
        AtomicType atomic{ 20 };

        IntegralType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 20);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicFetchAdd()
    {
      {
        AtomicType atomic;

        IntegralType ret = atomic.fetch_add(1, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic.fetch_add(0, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 5 };

        IntegralType ret = atomic.fetch_add(0, rsl::memory_order_relaxed);

        CHECK(ret == 5);

        ret = atomic.fetch_add(4, rsl::memory_order_relaxed);

        CHECK(ret == 5);

        ret = atomic.fetch_add(1, rsl::memory_order_relaxed);

        CHECK(ret == 9);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 10);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicAddFetch()
    {
      {
        AtomicType atomic;

        IntegralType ret = atomic.add_fetch(1, rsl::memory_order_relaxed);

        CHECK(ret == 1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic.add_fetch(0, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 5 };

        IntegralType ret = atomic.add_fetch(0, rsl::memory_order_relaxed);

        CHECK(ret == 5);

        ret = atomic.add_fetch(4, rsl::memory_order_relaxed);

        CHECK(ret == 9);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 9);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicFetchSub()
    {
      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic.fetch_sub(1, rsl::memory_order_relaxed);

        CHECK(ret == 1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic.fetch_sub(0, rsl::memory_order_relaxed);

        CHECK(ret == 1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }

      {
        AtomicType atomic{ 5 };

        IntegralType ret = atomic.fetch_sub(2, rsl::memory_order_relaxed);

        CHECK(ret == 5);

        ret = atomic.fetch_sub(1, rsl::memory_order_relaxed);

        CHECK(ret == 3);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 2);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicSubFetch()
    {
      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic.sub_fetch(1, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic.sub_fetch(0, rsl::memory_order_relaxed);

        CHECK(ret == 1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }

      {
        AtomicType atomic{ 5 };

        IntegralType ret = atomic.sub_fetch(2, rsl::memory_order_relaxed);

        CHECK(ret == 3);

        ret = atomic.sub_fetch(1, rsl::memory_order_relaxed);

        CHECK(ret == 2);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 2);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicFetchAnd()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.fetch_and(0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.fetch_and(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 0xF };

        IntegralType ret = atomic.fetch_and(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0xF);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0X1);
      }

      {
        AtomicType atomic{ 0xF };

        IntegralType ret = atomic.fetch_and(0xF0, rsl::memory_order_relaxed);

        CHECK(ret == 0xF);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicAndFetch()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.and_fetch(0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.and_fetch(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 0xF };

        IntegralType ret = atomic.and_fetch(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }

      {
        AtomicType atomic{ 0xF };

        IntegralType ret = atomic.and_fetch(0xF0, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicFetchOr()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.fetch_or(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic.fetch_or(0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic.fetch_or(0x2, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x3);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicOrFetch()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.or_fetch(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic.or_fetch(0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic.or_fetch(0x2, rsl::memory_order_relaxed);

        CHECK(ret == 0x3);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x3);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicFetchXor()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.fetch_xor(0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic.fetch_xor(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
      }

      {
        AtomicType atomic{ 0x0 };

        IntegralType ret = atomic.fetch_xor(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicXorFetch()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.xor_fetch(0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic.xor_fetch(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
      }

      {
        AtomicType atomic{ 0x0 };

        IntegralType ret = atomic.xor_fetch(0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAssignmentOperators()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = (atomic = 5);

        CHECK(ret == 5);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 5);
      }

      {
        AtomicType atomic{ 0 };

        IntegralType ret = ++atomic;

        CHECK(ret == 1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }

      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic++;

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = --atomic;

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic--;

        CHECK(ret == 1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic += 5;

        CHECK(ret == 5);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 5);
      }

      {
        AtomicType atomic{ 5 };

        IntegralType ret = atomic -= 3;

        CHECK(ret == 2);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 2);
      }

      {
        AtomicType atomic{ 0x0 };

        IntegralType ret = atomic |= 0x1;

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic &= 0x1;

        CHECK(ret == 0x1);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic ^= 0x1;

        CHECK(ret == 0x0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestIsLockFree()
    {
      {
        const AtomicType atomic{ 5 };

        CHECK(atomic.is_lock_free() == true);

        CHECK(AtomicType::is_always_lock_free == true);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestStore()
    {
      {
        AtomicType atomic{ 0 };

        atomic.store(0, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);
      }

      {
        AtomicType atomic{ 0 };

        atomic.store(1, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestLoad()
    {
      {
        AtomicType atomic{ 0 };

        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);

        bool ret = atomic == 0;
        CHECK(ret == true);

        CHECK(atomic == 0);
      }

      {
        AtomicType atomic{ 5 };

        CHECK(atomic.load(rsl::memory_order_relaxed) == 5);

        bool ret = atomic == 5;
        CHECK(ret == true);

        CHECK(atomic == 5);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestExchange()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.exchange(0, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic{ 0 };

        IntegralType ret = atomic.exchange(1, rsl::memory_order_relaxed);

        CHECK(ret == 0);

        ret = atomic.load(rsl::memory_order_relaxed);

        CHECK(ret == 1);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestCompareExchangeWeak()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType observed = 0;
        bool ret = atomic.compare_exchange_weak(observed, 1, rsl::memory_order_relaxed);

        if (ret == true)
        {
          CHECK(ret == true);
          CHECK(observed == 0);
          CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
        }
      }

      {
        AtomicType atomic{ 0 };

        IntegralType observed = 1;
        bool ret = atomic.compare_exchange_weak(observed, 1, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestCompareExchangeStrong()
    {
      {
        AtomicType atomic{ 0 };

        IntegralType observed = 0;
        bool ret = atomic.compare_exchange_strong(observed, 1, rsl::memory_order_relaxed);

        CHECK(ret == true);
        CHECK(observed == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic{ 0 };

        IntegralType observed = 1;
        bool ret = atomic.compare_exchange_strong(observed, 1, rsl::memory_order_relaxed);

        CHECK(ret == false);
        CHECK(observed == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);
      }
    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAllMemoryOrders()
    {
      {
        AtomicType atomic{};

        atomic.store(1);

        atomic.store(1, rsl::memory_order_relaxed);

        atomic.store(1, rsl::memory_order_release);

        atomic.store(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.load();

        ret = atomic.load(rsl::memory_order_relaxed);

        ret = atomic.load(rsl::memory_order_acquire);

        ret = atomic.load(rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.exchange(1);

        ret = atomic.exchange(1, rsl::memory_order_relaxed);

        ret = atomic.exchange(1, rsl::memory_order_acquire);

        ret = atomic.exchange(1, rsl::memory_order_release);

        ret = atomic.exchange(1, rsl::memory_order_acq_rel);

        ret = atomic.exchange(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.fetch_add(1);

        ret = atomic.fetch_add(1, rsl::memory_order_relaxed);

        ret = atomic.fetch_add(1, rsl::memory_order_acquire);

        ret = atomic.fetch_add(1, rsl::memory_order_release);

        ret = atomic.fetch_add(1, rsl::memory_order_acq_rel);

        ret = atomic.fetch_add(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.add_fetch(1);

        ret = atomic.add_fetch(1, rsl::memory_order_relaxed);

        ret = atomic.add_fetch(1, rsl::memory_order_acquire);

        ret = atomic.add_fetch(1, rsl::memory_order_release);

        ret = atomic.add_fetch(1, rsl::memory_order_acq_rel);

        ret = atomic.add_fetch(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.fetch_sub(1);

        ret = atomic.fetch_sub(1, rsl::memory_order_relaxed);

        ret = atomic.fetch_sub(1, rsl::memory_order_acquire);

        ret = atomic.fetch_sub(1, rsl::memory_order_release);

        ret = atomic.fetch_sub(1, rsl::memory_order_acq_rel);

        ret = atomic.fetch_sub(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.sub_fetch(1);

        ret = atomic.sub_fetch(1, rsl::memory_order_relaxed);

        ret = atomic.sub_fetch(1, rsl::memory_order_acquire);

        ret = atomic.sub_fetch(1, rsl::memory_order_release);

        ret = atomic.sub_fetch(1, rsl::memory_order_acq_rel);

        ret = atomic.sub_fetch(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.fetch_and(1);

        ret = atomic.fetch_and(1, rsl::memory_order_relaxed);

        ret = atomic.fetch_and(1, rsl::memory_order_acquire);

        ret = atomic.fetch_and(1, rsl::memory_order_release);

        ret = atomic.fetch_and(1, rsl::memory_order_acq_rel);

        ret = atomic.fetch_and(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.and_fetch(1);

        ret = atomic.and_fetch(1, rsl::memory_order_relaxed);

        ret = atomic.and_fetch(1, rsl::memory_order_acquire);

        ret = atomic.and_fetch(1, rsl::memory_order_release);

        ret = atomic.and_fetch(1, rsl::memory_order_acq_rel);

        ret = atomic.and_fetch(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.fetch_or(1);

        ret = atomic.fetch_or(1, rsl::memory_order_relaxed);

        ret = atomic.fetch_or(1, rsl::memory_order_acquire);

        ret = atomic.fetch_or(1, rsl::memory_order_release);

        ret = atomic.fetch_or(1, rsl::memory_order_acq_rel);

        ret = atomic.fetch_or(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.or_fetch(1);

        ret = atomic.or_fetch(1, rsl::memory_order_relaxed);

        ret = atomic.or_fetch(1, rsl::memory_order_acquire);

        ret = atomic.or_fetch(1, rsl::memory_order_release);

        ret = atomic.or_fetch(1, rsl::memory_order_acq_rel);

        ret = atomic.or_fetch(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.fetch_xor(1);

        ret = atomic.fetch_xor(1, rsl::memory_order_relaxed);

        ret = atomic.fetch_xor(1, rsl::memory_order_acquire);

        ret = atomic.fetch_xor(1, rsl::memory_order_release);

        ret = atomic.fetch_xor(1, rsl::memory_order_acq_rel);

        ret = atomic.fetch_xor(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType ret = atomic.xor_fetch(1);

        ret = atomic.xor_fetch(1, rsl::memory_order_relaxed);

        ret = atomic.xor_fetch(1, rsl::memory_order_acquire);

        ret = atomic.xor_fetch(1, rsl::memory_order_release);

        ret = atomic.xor_fetch(1, rsl::memory_order_acq_rel);

        ret = atomic.xor_fetch(1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType observed = 0;
        bool ret;

        ret = atomic.compare_exchange_weak(observed, 1);

        ret = atomic.compare_exchange_weak(observed, 1, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, 1, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, 1, rsl::memory_order_release);

        ret = atomic.compare_exchange_weak(observed, 1, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_weak(observed, 1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType observed = 0;
        bool ret;

        ret = atomic.compare_exchange_strong(observed, 1);

        ret = atomic.compare_exchange_strong(observed, 1, rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, 1, rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, 1, rsl::memory_order_release);

        ret = atomic.compare_exchange_strong(observed, 1, rsl::memory_order_acq_rel);

        ret = atomic.compare_exchange_strong(observed, 1, rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType observed = 0;
        bool ret;

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_relaxed,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_acquire,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_acquire,
          rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_release,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_acq_rel,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_acq_rel,
          rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_seq_cst,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_seq_cst,
          rsl::memory_order_acquire);

        ret = atomic.compare_exchange_weak(observed, 1,
          rsl::memory_order_seq_cst,
          rsl::memory_order_seq_cst);
      }

      {
        AtomicType atomic{};

        IntegralType observed = 0;
        bool ret;

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_relaxed,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_acquire,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_acquire,
          rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_release,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_acq_rel,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_acq_rel,
          rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_seq_cst,
          rsl::memory_order_relaxed);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_seq_cst,
          rsl::memory_order_acquire);

        ret = atomic.compare_exchange_strong(observed, 1,
          rsl::memory_order_seq_cst,
          rsl::memory_order_seq_cst);
      }

    }

    template <typename T>
    void AtomicIntegralBasicTest<T>::TestAtomicStandalone()
    {
      {
        AtomicType atomic;

        IntegralType expected = 0;
        bool ret = atomic_compare_exchange_weak(&atomic, &expected, 1);

        if (ret)
        {
          CHECK(ret == true);

          CHECK(expected == 0);
          CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
        }
      }

      {
        AtomicType atomic;

        IntegralType expected = 0;
        bool ret = atomic_compare_exchange_weak_explicit(&atomic, &expected, 1, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        if (ret)
        {
          CHECK(ret == true);

          CHECK(expected == 0);
          CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
        }
      }

      {
        AtomicType atomic;

        IntegralType expected = 0;
        bool ret = atomic_compare_exchange_strong(&atomic, &expected, 1);

        CHECK(ret == true);

        CHECK(expected == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType expected = 0;
        bool ret = atomic_compare_exchange_strong_explicit(&atomic, &expected, 1, rsl::memory_order_relaxed, rsl::memory_order_relaxed);

        CHECK(ret == true);

        CHECK(expected == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_fetch_xor(&atomic, 0x1);

        CHECK(ret == 0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_fetch_xor_explicit(&atomic, 0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_xor_fetch(&atomic, 0x1);

        CHECK(ret == 0x1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_xor_fetch_explicit(&atomic, 0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_fetch_or(&atomic, 0x1);

        CHECK(ret == 0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_fetch_or_explicit(&atomic, 0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_or_fetch(&atomic, 0x1);

        CHECK(ret == 0x1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_or_fetch_explicit(&atomic, 0x1, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x1);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic_fetch_and(&atomic, 0x0);

        CHECK(ret == 0x1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x0);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic_fetch_and_explicit(&atomic, 0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0x1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x0);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic_and_fetch(&atomic, 0x0);

        CHECK(ret == 0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x0);
      }

      {
        AtomicType atomic{ 0x1 };

        IntegralType ret = atomic_and_fetch_explicit(&atomic, 0x0, rsl::memory_order_relaxed);

        CHECK(ret == 0x0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0x0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic_fetch_sub(&atomic, 1);

        CHECK(ret == 1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic_fetch_sub_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == 1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic_sub_fetch(&atomic, 1);

        CHECK(ret == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);
      }

      {
        AtomicType atomic{ 1 };

        IntegralType ret = atomic_sub_fetch_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 0);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_fetch_add(&atomic, 1);

        CHECK(ret == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_fetch_add_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_add_fetch(&atomic, 1);

        CHECK(ret == 1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_add_fetch_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == 1);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_exchange(&atomic, 1);

        CHECK(ret == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_exchange_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(ret == 0);
        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_load(&atomic);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_load_explicit(&atomic, rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_load_cond(&atomic, [](IntegralType /*val*/) { return true; });

        CHECK(ret == 0);
      }

      {
        AtomicType atomic;

        IntegralType ret = atomic_load_cond_explicit(&atomic, [](IntegralType /*val*/) { return true; }, rsl::memory_order_relaxed);

        CHECK(ret == 0);
      }

      {
        AtomicType atomic;

        atomic_store(&atomic, 1);

        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        atomic_store_explicit(&atomic, 1, rsl::memory_order_relaxed);

        CHECK(atomic.load(rsl::memory_order_relaxed) == 1);
      }

      {
        AtomicType atomic;

        CHECK(atomic_is_lock_free(&atomic) == true);
      }
    }

    struct AtomicNonDefaultConstructible
    {
      AtomicNonDefaultConstructible(uint8_t a)
        : a(a)
      {
      }

      friend bool operator==(const AtomicNonDefaultConstructible& a, const AtomicNonDefaultConstructible& b)
      {
        return a.a == b.a;
      }

      uint8_t a;
    };

    struct Atomic128LoadType
    {
      friend bool operator==(const Atomic128LoadType& a, const Atomic128LoadType& b)
      {
        return a.a == b.a && a.b == b.b && a.c == b.c && a.d == b.d;
      }

      uint32_t a, b, c, d;
    };

  }
}

TEST_CASE("Test Atomic U8")
{
  rsl::test::AtomicIntegralBasicTest<uint8_t> u8AtomicTest;

  u8AtomicTest.RunTest();
}

TEST_CASE("Test Atomic U16")
{
  rsl::test::AtomicIntegralBasicTest<uint16_t> u16AtomicTest;

  u16AtomicTest.RunTest();
}

TEST_CASE("Test Atomic U32")
{
  rsl::test::AtomicIntegralBasicTest<uint32_t> u32AtomicTest;

  u32AtomicTest.RunTest();
}

TEST_CASE("Test Atomic U64")
{
  rsl::test::AtomicIntegralBasicTest<uint64_t> u64AtomicTest;

  u64AtomicTest.RunTest();
}

TEST_CASE("Test Atomic bool")
{
  rsl::test::AtomicBoolBasicTest boolAtomicTest;

  boolAtomicTest.RunTest();
}

TEST_CASE("Test Atomic UserType16")
{
  rsl::test::AtomicUserTypeBasicTest<rsl::test::AtomicUserType16> userTypeAtomicTest;

  userTypeAtomicTest.RunTest();
}

TEST_CASE("Test Atomic Non Trivially Constructible")
{
  rsl::test::AtomicUserTypeBasicTest<rsl::test::AtomicNonTriviallyConstructible> userTypeAtomicTest;

  userTypeAtomicTest.RunTest();
}

TEST_CASE("Test Atomic Non Trivially Constructible No Except")
{
  rsl::test::AtomicUserTypeBasicTest<rsl::test::AtomicNonTriviallyConstructibleNoExcept> userTypeAtomicTest;

  userTypeAtomicTest.RunTest();
}

TEST_CASE("Test Atomic Pointer")
{
  rsl::test::AtomicPointerBasicTest ptrAtomicTest;

  ptrAtomicTest.RunTest();
}

TEST_CASE("Test Atomic Void Pointer")
{
  rsl::test::AtomicVoidPointerBasicTest voidPtrAtomicTest;

  voidPtrAtomicTest.RunTest();
}

TEST_CASE("Test Atomic Flag")
{
  rsl::test::AtomicFlagBasicTest atomicFlagBasicTest;

  atomicFlagBasicTest.RunTest();
}

TEST_CASE("Test Atomic Standalone")
{
  rsl::test::AtomicStandaloneBasicTest atomicStandaloneBasicTest;

  atomicStandaloneBasicTest.RunTest();
}
TEST_CASE("Test Atomic Non Default Constructible")
{
  {
    rsl::atomic<rsl::test::AtomicNonDefaultConstructible> atomic{ rsl::test::AtomicNonDefaultConstructible{(uint8_t)3} };

    CHECK(atomic.load() == rsl::test::AtomicNonDefaultConstructible{ (uint8_t)3 });
  }

  {
    rsl::atomic<rsl::test::AtomicNonDefaultConstructible> atomic{ rsl::test::AtomicNonDefaultConstructible{(uint8_t)3} };

    atomic.store(rsl::test::AtomicNonDefaultConstructible{ (uint8_t)4 });

    CHECK(atomic.load() == rsl::test::AtomicNonDefaultConstructible{ (uint8_t)4 });
  }

  {
    rsl::atomic<rsl::test::AtomicNonDefaultConstructible> atomic{ rsl::test::AtomicNonDefaultConstructible{(uint8_t)3} };

    CHECK(atomic_load_cond(&atomic, [](rsl::test::AtomicNonDefaultConstructible) { return true; }) == rsl::test::AtomicNonDefaultConstructible{ (uint8_t)3 });
  }

  {
    rsl::atomic<rsl::test::AtomicNonDefaultConstructible> atomic{ rsl::test::AtomicNonDefaultConstructible{(uint8_t)3} };

    CHECK(atomic_load_cond_explicit(&atomic, [](rsl::test::AtomicNonDefaultConstructible) { return true; }, rsl::memory_order_seq_cst) == rsl::test::AtomicNonDefaultConstructible{ (uint8_t)3 });
  }
}
TEST_CASE("Test Atomic Constant Init")
{
  static rsl::atomic<int> sAtomicInt{ 4 };
  static rsl::atomic<void*> sAtomicPtr{ nullptr };

  CHECK(sAtomicInt.load() == 4);
  CHECK(sAtomicPtr == nullptr);
}
