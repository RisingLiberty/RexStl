// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_character.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/type_traits/is_same.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
inline constexpr bool is_character_v = rsl::is_same_v<T, char8> || rsl::is_same_v<T, tchar>;

REX_RSL_END_NAMESPACE
