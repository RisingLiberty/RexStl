// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: clock.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/time/clock.h"

#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/time/time.h"
#include "rex_std_extra/time/timepoint.h"

rsl::Clock::Clock()
    : m_start_time(current_timepoint())
    , m_current_time(m_start_time)
    , m_is_paused(false)
    , m_delta_time(0.0f)
{
}

void rsl::Clock::update()
{
  TimePoint current_time = rsl::current_timepoint();

  float32 duration = current_time - m_current_time;

  m_delta_time = m_is_paused ? 0 : duration;

  m_current_time = current_time;
}

void rsl::Clock::pause()
{
  m_is_paused = true;
}
void rsl::Clock::resume()
{
  m_is_paused = false;
}

float32 rsl::Clock::delta_time() const
{
  return m_delta_time;
}