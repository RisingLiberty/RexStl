// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_allocator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/utility/forward.h"
#include "rex_std/limits.h"
#include "rex_std_test/catch2/catch.hpp"
#include "rex_std/assert.h"
#include "rex_std/internal/algorithm/fill.h"

namespace rsl::test
{
  inline namespace v1
  {
    class test_allocator
    {
    public:
      using size_type = size_t;
      using difference_type = ptrdiff;

      test_allocator() = default;
      test_allocator(const test_allocator&);
      test_allocator(test_allocator&&);

      ~test_allocator() = default;

      test_allocator& operator=(const test_allocator&) = default;
      test_allocator& operator=(test_allocator&&);

      REX_NO_DISCARD void* allocate(const size_type count);
      void deallocate(void* const ptr, size_type size);

      size_type max_size() const;

      // construct an object of type T in allocated uninitialized storage pointer to by p
      template <typename U, typename... Args>
      void construct(U* p, Args&&... args)
      {
        new(static_cast<void*>(p)) U(rsl::forward<Args>(args)...);
      }
      // calls the destructor of the object pointed to by p
      template <typename U>
      void destroy(U* p)
      {
        p->~U();
      }

      card32 num_allocs() const;
      card32 num_frees() const;
      card32 num_bytes_allocated() const;

      static card32 all_num_allocs();
      static card32 all_num_frees();
      static card32 all_num_bytes_allocated();
      static void all_reset();

      void reset();

    private:
      card32 m_num_allocs;
      card32 m_num_frees;
      card32 m_num_bytes_allocated;

      static card32 s_all_num_allocs;
      static card32 s_all_num_frees;
      static card32 s_all_num_bytes_allocated;
    };

    constexpr bool operator==(const test_allocator& /*unused*/, const test_allocator& /*unused*/)
    {
      return true;
    }
    constexpr bool operator!=(const test_allocator& /*unused*/, const test_allocator& /*unused*/)
    {
      return false;
    }


    class malloc_allocator
    {
    public:
      malloc_allocator()
        : m_alloc_count(0), m_free_count(0), m_alloc_volume(0) {}

      malloc_allocator(const malloc_allocator& x)
        : m_alloc_count(x.m_alloc_count), m_free_count(x.m_free_count), m_alloc_volume(x.m_alloc_volume) {}

      malloc_allocator(const malloc_allocator& x, const char*) : malloc_allocator(x) {}

      malloc_allocator& operator=(const malloc_allocator& x)
      {
        m_alloc_count = x.m_alloc_count;
        m_free_count = x.m_free_count;
        m_alloc_volume = x.m_alloc_volume;
        return *this;
      }

      void* allocate(size_t n, int = 0);
      void* allocate(size_t n, size_t, size_t, int = 0); // We don't support alignment, so you can't use this class where alignment is required.
      void deallocate(void* p, size_t n);

      const char* name() const { return "malloc_allocator"; }
      void set_name(const char*) {}

      static void reset_all()
      {
        s_alloc_count_all = 0;
        s_free_count_all = 0;
        s_alloc_volume_all = 0;
        s_last_allocation = nullptr;
      }

    public:
      int32 m_alloc_count;
      int32 m_free_count;
      size_t m_alloc_volume;

      static int s_alloc_count_all;
      static int s_free_count_all;
      static size_t s_alloc_volume_all;
      static void* s_last_allocation;
    };


    constexpr bool operator==(const malloc_allocator& /*unused*/, const malloc_allocator& /*unused*/)
    {
      return true;
    }
    // compares 2 default allocators.
    // default allocators are stateless, so they're always equal
    constexpr bool operator!=(const malloc_allocator& /*unused*/, const malloc_allocator& /*unused*/)
    {
      return false;
    }



    class instance_allocator
    {
    private:
      static constexpr card32 s_multplier = 16;
    public:

      instance_allocator(const char* = nullptr, uint8_t instanceId = 0) 
        : m_instance_id(instanceId)
      {}
      instance_allocator(uint8_t instanceId) 
        : m_instance_id(instanceId) 
      {}
      instance_allocator(const instance_allocator& x)
        : m_instance_id(x.m_instance_id) 
      {}
      instance_allocator(const instance_allocator& x, const char*) 
        : m_instance_id(x.m_instance_id) 
      {}

      instance_allocator& operator=(const instance_allocator& x)
      {
        m_instance_id = x.m_instance_id;
        return *this;
      }

      void* allocate(size_t n, int = 0)
      { // +1 so that we always have space to write m_instance_id.
        uint8_t* p8 = static_cast<uint8_t*>(malloc(n + (s_multplier * (m_instance_id + 1)))); // We make allocations between
                                                                                // different instances incompatible by
                                                                                // tweaking their return values.
        CHECK(p8 != nullptr);
        rsl::fill(p8, p8 + s_multplier, 0xffui8);
        *p8 = m_instance_id;
        return p8 + (s_multplier * (m_instance_id + 1));
      }

      void* allocate(size_t n, size_t, size_t, int = 0)
      { // +1 so that we always have space to write m_instance_id.
        uint8_t* p8 =
          static_cast<uint8_t*>(malloc(n + (s_multplier * (m_instance_id + 1)))); // We make allocations between
                                                                                // different instances incompatible by
                                                                                // tweaking their return values.
        CHECK(p8 != nullptr);
        rsl::fill(p8, p8 + s_multplier, 0xffui8);
        *p8 = m_instance_id;
        return p8 + (s_multplier * (m_instance_id + 1));
      }

      void deallocate(void* p, size_t /*n*/)
      {
        uint8_t* p8 = static_cast<uint8_t*>(p) - (s_multplier * (m_instance_id + 1));
        RSL_ASSERT_X(*p8 == m_instance_id, "invalid instance id for deallocation of ptr"); // m_instance_id must match the id used in allocate(), otherwise the behavior is
                                          // undefined (probably a heap assert).
        if (*p8 == m_instance_id) // It's possible that *p8 coincidentally matches m_instance_id if p8 is offset into memory
                                // we don't control.
          free(p8);
        else
          ++s_mismatch_count;
      }

      rsl::string_view name()
      {
        m_name = rsl::format("instance_allocator {}", m_instance_id);
        return m_name;
      }

      void set_name(const char*) {}

      static void reset_all() { s_mismatch_count = 0; }

    public:
      uint8_t m_instance_id;
      rsl::fmt_stack_string m_name;

      static int32 s_mismatch_count;
    };

    inline bool operator==(const instance_allocator& a, const instance_allocator& b) { return (a.m_instance_id == b.m_instance_id); }
    inline bool operator!=(const instance_allocator& a, const instance_allocator& b) { return (a.m_instance_id != b.m_instance_id); }
  }
}