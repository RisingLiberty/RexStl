// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: delete.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

// Can't put this in a namespace
// adding noexcept to avoid warnings on Windows
//void operator delete(void* ptr) noexcept;                  // NOLINT(misc-new-delete-overloads, readability-inconsistent-declaration-parameter-name, readability-redundant-declaration)
//void operator delete(void* ptr, size_t /*size*/) noexcept; // NOLINT(misc-new-delete-overloads, readability-inconsistent-declaration-parameter-name, readability-redundant-declaration)