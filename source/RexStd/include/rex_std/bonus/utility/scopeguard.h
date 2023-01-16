// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: scopeguard.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    template <typename Func>
    class scopeguard
    {
    public:
      scopeguard(Func&& func)
          : m_func(func)
          , m_should_execute(true)
      {
      }

      ~scopeguard()
      {
        if(m_should_execute)
        {
          m_func();
        }
      }

      void release()
      {
        m_should_execute = false;
      }

    private:
      Func m_func;
      bool m_should_execute;
    };
  } // namespace v1
} // namespace rsl
