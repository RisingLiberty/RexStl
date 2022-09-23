// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: type_select.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

REX_RSL_BEGIN_NAMESPACE

template <bool Condition, typename TypeIfTrue, typename TypeIfFalse>
struct type_select
{
  using type = TypeIfTrue;
};

template <typename TypeIfTrue, typename TypeIfFalse>
struct type_select<false, TypeIfTrue, TypeIfFalse>
{
  using type = TypeIfFalse;
};

template <bool Condition, typename TypeIfTrue, typename TypeIfFalse>
using type_select_t = typename type_select<Condition, TypeIfTrue, TypeIfFalse>;

REX_RSL_END_NAMESPACE