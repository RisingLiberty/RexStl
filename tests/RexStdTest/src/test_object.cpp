// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_object.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_test/test_object.h"

namespace rsl::test
{
  inline namespace v1
  {
    card32 test_object::s_num_alive = 0; // number of current alive test objects
    card32 test_object::s_num_ctor_calls = 0; // number of constructor calls
    card32 test_object::s_num_dtor_calls = 0; // number of constructor calls
    card32 test_object::s_num_copy_ctor_calls = 0; // number of copy constructor calls
    card32 test_object::s_num_move_ctor_calls = 0; // number of move constructor calls
    card32 test_object::s_num_copy_assignment_calls = 0; // number of copy assignment calls
    card32 test_object::s_num_move_assignment_calls = 0; // number of move assignment calls

    test_object::test_object(card32 x)
      : m_x(x)
    {
      s_num_alive++;
      s_num_ctor_calls++;
    }
    test_object::test_object(const test_object& obj)
      : m_x(obj.m_x)
    {
      s_num_alive++;
      s_num_copy_ctor_calls++;
    }
    test_object::test_object(test_object&& obj)
      : m_x(obj.m_x)
    {
      s_num_alive++;
      s_num_move_ctor_calls++;
    }
    test_object::~test_object()
    {
      s_num_alive--;
      s_num_dtor_calls++;
    }

    test_object& test_object::operator=(const test_object& obj)
    {
      m_x = obj.m_x;
      s_num_copy_assignment_calls++;

      return *this;
    }
    test_object& test_object::operator=(test_object&& obj)
    {
      m_x = obj.m_x;
      s_num_move_assignment_calls++;

      return *this;
    }

    card32 test_object::x() const
    {
      return m_x;
    }

    test_object::operator rsl::v1::card32() const
    {
      return m_x;
    }
    
    void test_object::reset()
    {
      s_num_alive = 0;
      s_num_ctor_calls = 0;
      s_num_dtor_calls = 0;
      s_num_copy_ctor_calls = 0;
      s_num_move_ctor_calls = 0;
      s_num_copy_assignment_calls = 0;
      s_num_move_assignment_calls = 0;
    }

    card32 test_object::num_alive()
    {
      return s_num_alive;
    }
    card32 test_object::num_ctor_calls()
    {
      return s_num_ctor_calls;
    }
    card32 test_object::num_dtor_calls()
    {
      return s_num_dtor_calls;
    }
    card32 test_object::num_copy_ctor_calls()
    {
      return s_num_copy_ctor_calls;
    }
    card32 test_object::num_move_ctor_calls()
    {
      return s_num_move_ctor_calls;
    }
    card32 test_object::num_copy_assignment_calls()
    {
      return s_num_copy_assignment_calls;
    }
    card32 test_object::num_move_assignment_calls()
    {
      return s_num_move_assignment_calls;
    }
  }
}