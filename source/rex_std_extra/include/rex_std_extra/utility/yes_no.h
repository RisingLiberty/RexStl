// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: yes_no.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    class yes_no
    {
    public:
      enum eyes_no
      {
        no  = 0,
        yes = 1
      };

      yes_no(eyes_no value); // NOLINT(google-explicit-constructor)

      operator bool() const; // NOLINT(google-explicit-constructor)

    private:
      eyes_no m_value;
    };

  } // namespace v1
} // namespace rsl

#define DEFINE_YES_NO_ENUM(ClassName)                                                                                                                                                                                                                    \
  class ClassName : public rsl::yes_no                                                                                                                                                                                                                   \
  {                                                                                                                                                                                                                                                      \
  public:                                                                                                                                                                                                                                                \
    ClassName(eyes_no value)                                                                                                                                                                                                                             \
        : rsl::yes_no(value)                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                    \
    }                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                         \
    explicit ClassName(bool value)                                                                                                                                                                                                                       \
        : rsl::yes_no(value ? eyes_no::yes : eyes_no::no)                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                    \
    }                                                                                                                                                                                                                                                    \
  }