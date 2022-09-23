// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: unique.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last)
{
  if(first == last)
    return last;

  ForwardIterator result = first;
  while(++first != last)
  {
    if((*result != *first) && ++result != first)
    {
      *result = rsl::move(*first);
    }
  }
  return ++result;
}

template <class ForwardIterator, class Predicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last, Predicate p)
{
  if(first == last)
    return last;

  ForwardIterator result = first;
  while(++first != last)
  {
    if(!p(*result, *first) && ++result != first)
    {
      *result = rsl::move(*first);
    }
  }
  return ++result;
}

REX_RSL_END_NAMESPACE
