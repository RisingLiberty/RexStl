// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timer.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/time/timer.h"

rsl::timer::timer(float32 maxTimeInSeconds)
    : m_max_time(maxTimeInSeconds * 0.0001f) // convert to milli seconds
    , m_current_time(0.0f)
    , m_prev_time_point(current_timepoint())
{
}

void rsl::timer::update()
{
  rsl::time_point now = current_timepoint();
  m_current_time += m_prev_time_point - now;
  m_prev_time_point = now;
}

void rsl::timer::reset()
{
  m_current_time    = 0.0f;
  m_prev_time_point = current_timepoint();
}

void rsl::timer::set_max_time(float32 maxTime)
{
  m_max_time = maxTime;
}

bool rsl::timer::is_done() const
{
  return m_current_time > m_max_time;
}