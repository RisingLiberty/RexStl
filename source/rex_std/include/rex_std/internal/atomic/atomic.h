// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

// Rex Standard Library atomic implementation is heavily inspired by EASTL's implementation of atomic
// https://github.com/electronicarts/EASTL/tree/master/include/EASTL/internal/atomic
// But instead of using macros, we move our implementation to cpp files for easier debugging capabilities
// This also gives us the benefit of moving platform includes (eg. Windows.h) to cpp files so they're not exposed
// in client code

#include "rex_std/bonus/atomic/atomic.h"
#include "rex_std/bonus/atomic/atomic_flag.h"
#include "rex_std/bonus/atomic/atomic_flag_standalone.h"
#include "rex_std/bonus/atomic/atomic_standalone.h"
