// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stopwatch.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std_extra/time/timepoint.h"

REX_RSL_BEGIN_NAMESPACE

class Stopwatch
{
public:
  Stopwatch();

  void stop();
  void pause();
  void resume();

  float32 time_in_seconds() const;
  float32 time_in_ms() const;

private:
  TimePoint m_start;
  TimePoint m_end;

  TimePoint m_pause_start;
  float32 m_paused_time_in_ms;
};

REX_RSL_END_NAMESPACE