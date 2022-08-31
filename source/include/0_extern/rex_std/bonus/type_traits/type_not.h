// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: type_not.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
	template <bool b>
	struct type_not { static const bool value = true; };

	template <>
	struct type_not<true> { static const bool value = false; };
}
