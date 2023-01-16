// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_message_box.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/string_view.h"

REX_RSL_BEGIN_NAMESPACE

int32 message_box(const rsl::StringView msg);
int32 message_box(const rsl::StringView msg, const rsl::StringView title);

// Returns true if yes is pressed
bool yes_no_message_box(const rsl::StringView msg);
bool yes_no_message_box(const rsl::StringView msg, const rsl::StringView title);

REX_RSL_END_NAMESPACE