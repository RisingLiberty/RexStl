// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: csetjmp.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

// usage of setjmp is highly discouraged, even by Microsoft
// "Because setjmp and longjmp don't support correct destruction of stack frame objects portably between C++ compilers,
// and because they might degrade performance by preventing optimization on local variables, we don't recommend their use in C++ programs. We recommend you use try and catch constructs instead."
// They're basically fancy goto statements in C++.
// goto statement should never be used in C++, therefore we don't implement setjmp in rsl.

static_assert(false, "using csetjmp in rsl is not allowed");
