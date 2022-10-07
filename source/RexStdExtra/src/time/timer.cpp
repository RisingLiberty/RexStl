// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timer.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/time/timer.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::Timer::Timer(float32 max_time_in_seconds)
    : m_max_time(max_time_in_seconds * 0.0001f) // convert to milli seconds
    , m_current_time(0.0f)
    , m_prev_time_point(current_timepoint())
{
}

void rsl::Timer::update()
{
  TimePoint now = current_timepoint();
  m_current_time += m_prev_time_point - now;
  m_prev_time_point = now;
}

void rsl::Timer::reset()
{
  m_current_time    = 0.0f;
  m_prev_time_point = current_timepoint();
}

void rsl::Timer::set_max_time(float32 max_time)
{
  m_max_time = max_time;
}

bool rsl::Timer::is_done() const
{
  return m_current_time > m_max_time;
}