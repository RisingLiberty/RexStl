// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: min_element.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename InputIterator>
InputIterator min_element(InputIterator first, InputIterator last)
{
  InputIterator smallest = first++;
  InputIterator it       = first;
  while(it != last)
  {
    if(*it < *smallest)
    {
      smallest = it;
    }
  }

  return smallest;
}
template <typename InputIterator, typename Compare>
InputIterator min_element(InputIterator first, InputIterator last, Compare compare)
{
  InputIterator smallest = first++;
  InputIterator it       = first;
  while(it != last)
  {
    if(compare(*it, *smallest))
    {
      smallest = it;
    }
  }

  return smallest;
}

REX_RSL_END_NAMESPACE
