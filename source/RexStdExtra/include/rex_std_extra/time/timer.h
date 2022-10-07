// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std_extra/time/timepoint.h"

REX_RSL_BEGIN_NAMESPACE

class Timer
{
public:
  Timer(float32 max_time_in_seconds);

  void update();
  void reset();

  void set_max_time(float32 max_time_in_seconds);

  bool is_done() const;

private:
  float32 m_max_time;
  float32 m_current_time;

  TimePoint m_prev_time_point;
};

REX_RSL_END_NAMESPACE