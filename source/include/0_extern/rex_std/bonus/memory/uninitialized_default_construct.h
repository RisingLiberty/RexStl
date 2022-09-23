// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: uninitialized_default_construct.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
void uninitialized_default_construct(T* ptr)
{
  new(ptr) T();
}

REX_RSL_END_NAMESPACE
