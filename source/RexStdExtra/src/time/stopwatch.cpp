// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stopwatch.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/time/stopwatch.h"

#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/time/timepoint.h"

rsl::Stopwatch::Stopwatch()
    : m_start(current_timepoint())
    , m_end(m_start)
    , m_pause_start()
    , m_paused_time_in_ms(0.0f)
{
}

void rsl::Stopwatch::stop()
{
  m_end = current_timepoint();
}

float32 rsl::Stopwatch::time_in_seconds() const
{
  return time_in_ms() * 0.001f;
}
float32 rsl::Stopwatch::time_in_ms() const
{
  float32 duration = m_end - m_start;
  return duration - m_paused_time_in_ms;
}

void rsl::Stopwatch::pause()
{
  m_pause_start = current_timepoint();
}

void rsl::Stopwatch::resume()
{
  TimePoint pause_end = current_timepoint();
  m_paused_time_in_ms += pause_end - m_pause_start;
}