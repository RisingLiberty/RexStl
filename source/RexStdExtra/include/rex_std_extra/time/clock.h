// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: clock.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std_extra/time/timepoint.h"

REX_RSL_BEGIN_NAMESPACE

class Clock
{
public:
  Clock();

  void update();
  void pause();
  void resume();

  float32 delta_time() const;

private:
  TimePoint m_start_time;
  TimePoint m_current_time;

  bool m_is_paused;

  // delta time is expressed in seconds
  float32 m_delta_time;
};

REX_RSL_END_NAMESPACE