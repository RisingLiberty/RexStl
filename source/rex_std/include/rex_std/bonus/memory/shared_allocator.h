// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: shared_allocator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename Alloc>
    class SharedAlloc
    {
    public:
      using size_type = typename Alloc::size_type;
      using pointer   = typename Alloc::pointer;

      SharedAlloc(Alloc& alloc)
          : m_alloc(alloc)
      {
      }

      REX_NO_DISCARD pointer allocate(const size_type size)
      {
        return m_alloc.allocate(size);
      }
      void deallocate(pointer ptr, const size_type size)
      {
        m_alloc.deallocate(ptr, size);
      }

      constexpr bool operator==(const SharedAlloc& rhs) const
      {
        return m_alloc == rhs.m_alloc;
      }
      constexpr bool operator!=(const SharedAlloc& rhs) const
      {
        return m_alloc != rhs.m_alloc;
      }

    private:
      Alloc& m_alloc;
    };

  } // namespace v1
} // namespace rsl