// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_file.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/filesystem.h"
#include "rex_std/iostream.h"
#include "rex_std_extra/filesystem/open_flags.h"

REX_RSL_BEGIN_NAMESPACE

namespace win
{
  using FileHandle = void*;
}

class File : public IOStream
{
public:
  File();
  File(const Path& path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);
  File(const StringView path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);
  File(const char8* path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);

  File(const File& other) = delete; // files behave as unique oqners, so having a copy ctor doesn't make sense
  File(File&& other) noexcept;

  ~File();

  File& operator=(const File& other) = delete; // files behave as unique owners, so having a copy assignement operator doesn't make sense
  File& operator=(File&& other) noexcept;

  void flush() final;

  const Path& path() const;
  const rsl::byte* data() const;
  const rsl::byte* read_cursor_pos_data() const;
  rsl::String data_as_string() const;

  REX_NO_DISCARD UniqueArray<String> lines() const;
  REX_NO_DISCARD UniqueArray<StringView> line_views() const;

  bool open(const StringView path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);
  bool open(const Path& path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);
  bool open(const char8* path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);

  bool is_open() const;
  void append();
  void trunc();
  void close();
  void skip(card32 bytes);

  bool eof() const;
  card32 file_size() const;

  void read(void* read, card32 size);

  // be careful using the following function
  // in rare cases, rvo(return value optimization) might be skipped (eg. debug config)
  // which wil affect performance
  template <typename T>
  T read()
  {
    T value;
    read(&value, sizeof(value));
    return value;
  }

  void write_string(StringView str);
  String read_string();

  bool is_readonly() const;
  void add_readonly_attribute();
  void remove_readonly_attribute();

  template <typename T>
  void write(const T& value)
  {
    write(&value, sizeof(value));
  }
  void write(const void* data, size_t size);

  void save_to_disk();

private:
  void reset_file_ptr();
  void append_file_ptr();
  void init_file_data();
  void read_file_data();

private:
  win::FileHandle m_file_handle;
  Path m_path;
  bool m_is_open;
  bool m_is_read_only_at_startup;
  OpenFlags m_open_flags;
};

class IFile : public IStream
{
public:
  IFile();
  IFile(const Path& path);
  IFile(const StringView path);
  IFile(const char8* path);

  IFile(const IFile& other) = delete; // files behave as unique oqners, so having a copy ctor doesn't make sense
  IFile(IFile&& other) noexcept;

  ~IFile();

  IFile& operator=(const IFile& other) = delete; // files behave as unique owners, so having a copy assignement operator doesn't make sense
  IFile& operator=(IFile&& other) noexcept;

  const Path& path() const;
  const rsl::byte* data() const;
  const rsl::byte* read_cursor_pos_data() const;
  rsl::String data_as_string() const;

  REX_NO_DISCARD UniqueArray<String> lines() const;
  REX_NO_DISCARD UniqueArray<StringView> line_views() const;

  bool open(const StringView path);
  bool open(const Path& path);
  bool open(const char8* path);

  bool is_open() const;
  void close();
  void skip(card32 bytes);

  bool eof() const;
  card32 file_size() const;

  void read(void* read, card32 size);

  // be careful using the following function
  // in rare cases, rvo(return value optimization) might be skipped (eg. debug config)
  // which wil affect performance
  template <typename T>
  T read()
  {
    T value;
    read(&value, sizeof(value));
    return value;
  }

  String read_string();

  bool is_readonly() const;
  void add_readonly_attribute();
  void remove_readonly_attribute();

private:
  void read_file_data();

private:
  win::FileHandle m_file_handle;
  Path m_path;
  bool m_is_open;
  bool m_is_read_only_at_startup;
  OpenFlags m_open_flags;
};

class OFile : public OStream
{
public:
  OFile();
  OFile(const Path& path, OpenFlags open_flags = OpenFlags::Trunc);
  OFile(const StringView path, OpenFlags open_flags = OpenFlags::Trunc);
  OFile(const char8* path, OpenFlags open_flags = OpenFlags::Trunc);

  OFile(const OFile& other) = delete; // files behave as unique oqners, so having a copy ctor doesn't make sense
  OFile(OFile&& other) noexcept;

  ~OFile();

  OFile& operator=(const OFile& other) = delete; // files behave as unique owners, so having a copy assignement operator doesn't make sense
  OFile& operator=(OFile&& other) noexcept;

  void flush() final;

  const Path& path() const;
  const rsl::byte* data() const;

  bool open(const StringView path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);
  bool open(const Path& path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);
  bool open(const char8* path, OpenFlags open_flags = OpenFlags::App | OpenFlags::ReadWrite);

  bool is_open() const;
  void append();
  void trunc();
  void close();

  card32 file_size() const;
  bool is_readonly() const;
  void add_readonly_attribute();
  void remove_readonly_attribute();

  void write(const void* data, size_t size);
  void write_string(StringView str);

  void save_to_disk();

private:
  void reset_file_ptr();
  void append_file_ptr();
  void init_file_data();
  void read_file_data();

private:
  win::FileHandle m_file_handle;
  Path m_path;
  bool m_is_open;
  bool m_is_read_only_at_startup;
  OpenFlags m_open_flags;
};

REX_RSL_END_NAMESPACE