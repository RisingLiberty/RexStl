// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_error.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

enum class WinError
{
  Success                = 0,
  InvalidFunction        = 1,
  FileNotFound           = 2,
  PathNotFound           = 3,
  AccessDenied           = 5,
  NotEnoughMemory        = 8,
  NoMoreFiles            = 18,
  SharingViolation       = 32,
  NotSupported           = 50,
  FileExists             = 80,
  InvalidParameter       = 87,
  InsufficientBuffer     = 122,
  InvalidName            = 123,
  DirectoryNotEmpty      = 145,
  AlreadyExists          = 183,
  FilenameExceedRange    = 206,
  DirectoryNameIsInvalid = 267
};

REX_RSL_END_NAMESPACE