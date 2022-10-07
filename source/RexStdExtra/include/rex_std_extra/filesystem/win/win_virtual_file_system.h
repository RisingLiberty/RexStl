// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_virtual_file_system.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/filesystem.h"
#include "rex_std_extra/filesystem/open_flags.h"
#include "rex_std_extra/time/timepoint.h"
#include "rex_std_extra/utilities/yes_no_enum.h"

REX_RSL_BEGIN_NAMESPACE

namespace win
{
  using FileHandle = void*;
}

// Try to use Path instead of StackString for filepaths
// this avoids copying them into a [atj structure and imrpoves performance

namespace vfs
{
  // the reason mounting code takes in templates is because different projects
  // will use different types passed to the VFS
  // we don't want 1 global enum to be used by multiple projects
  using MountHash = uint32;

  template <typename T, rsl::EnableIf<rsl::is_enum_v<T>, bool> = true>
  REX_NO_DISCARD MountHash create_mount_hash(const T& type)
  {
    static card32 type_id   = static_cast<card32>(typeid(T).hash_code());
    static int64 start_seed = hash_combine(0, type_id);

    card32 hash = static_cast<card32>(rsl::hash<T>()(type));
    int64 seed  = hash_combine(start_seed, hash);

    return static_cast<MountHash>(seed);
  }

  void init(const StringView app_name, StringView root_path);
  void shutdown();

  void set_root_directory(const Path& root);
  void set_root_directory(StringView root);

  REX_NO_DISCARD const Path& root_directory(); // where all our data is stored
  REX_NO_DISCARD Path working_directory();     // working directory, change this in Visual Studio
  REX_NO_DISCARD Path app_directory();         // the directory where the app is located
  REX_NO_DISCARD Path user_app_directory();    // this is appdata on Windows

  // create a path that's relative to the root directory
  // this returns the input path if the ipath is on a different drive as the root dir
  REX_NO_DISCARD Path make_relative_to_root(const rsl::Path& path);

  // querying
  REX_NO_DISCARD UniqueArray<Path> file_names_in_directory(const Path& path);
  REX_NO_DISCARD UniqueArray<Path> file_names_in_directory(const StringView path);

  // helpers
  Path create_path_from_root(const Path& path);
  Path create_path_from_root(const StringView path);

  REX_NO_DISCARD Path create_absolute_file_path(const Path& path);
  REX_NO_DISCARD Path create_absolute_file_path(const StringView path);
  REX_NO_DISCARD Path create_absolute_file_path(const MountHash hash);

  bool is_mounted(MountHash hash);
  template <typename T>
  bool is_mounted(const T& type)
  {
    MountHash hash = create_mount_hash(type);
    return is_mounted(hash);
  }

  MountHash mount(MountHash hash, const StringView path);
  MountHash mount(MountHash hash, const Path& path);

  template <typename T, rsl::EnableIf<rsl::is_enum_v<T>, bool> = true>
  MountHash mount(const T& type, const StringView path)
  {
    MountHash hash = create_mount_hash(type);
    mount(hash, path);
    return hash;
  }
  template <typename T, rsl::EnableIf<rsl::is_enum_v<T>, bool> = true>
  MountHash mount(const T& type, const Path& path)
  {
    MountHash hash = create_mount_hash(type);
    mount(hash, path);
    return hash;
  }

  MountHash remount(MountHash hash, const StringView path);
  MountHash remount(MountHash hash, const Path& path);

  template <typename T, rsl::EnableIf<rsl::is_enum_v<T>, bool> = true>
  MountHash remount(T type, const StringView path)
  {
    MountHash hash = create_mount_hash(type);
    remount(hash, path);
    return hash;
  }
  template <typename T, rsl::EnableIf<rsl::is_enum_v<T>, bool> = true>
  MountHash remount(T type, const Path& path)
  {
    MountHash hash = create_mount_hash(type);
    remount(hash, path);
    return hash;
  }

  MountHash ummount(MountHash hash);
  template <typename T, rsl::EnableIf<rsl::is_enum_v<T>, bool> = true>
  MountHash unmount(const T& type)
  {
    MountHash hash = create_mount_hash(type);
    unmount(hash);
    return hash;
  }

  template <typename T, rsl::EnableIf<rsl::is_enum_v<T>, bool> = true>
  Path get_mount(const T& type)
  {
    MountHash hash = create_mount_hash(type);
    if(!is_mounted(hash))
    {
      REX_ERROR("Trting to get mount that doesn't exist");
      return Path();
    }
    return create_absolute_file_path(hash);
  }

  // creaters
  void create_directory(const Path& path);
  void create_directory(const StringView path);

  void create_directory_recursive(const Path& path);
  void create_directory_recusrive(const StringView path);

  REX_NO_DISCARD win::FileHandle create_file(const Path& path);
  REX_NO_DISCARD win::FileHandle create_file(const StringView path);

  // destroyers
  void delete_directory(const Path& path);
  void delete_directory(const StringView path);

  void delete_file(const Path& path);
  void delete_file(const StringView path);

  // open
  REX_NO_DISCARD win::FileHandle open_existing_file(const Path& path, OpenFlags flags = OpenFlags::ReadWrite);
  REX_NO_DISCARD win::FileHandle open_existing_file(const StringView path, OpenFlags flags = OpenFlags::ReadWrite);

  REX_NO_DISCARD win::FileHandle open_or_create_file(const Path& path, OpenFlags flags = OpenFlags::ReadWrite);
  REX_NO_DISCARD win::FileHandle open_or_create_file(const StringView path, OpenFlags flags = OpenFlags::ReadWrite);

  // closing
  void close_file(win::FileHandle file);

  // IO
  REX_NO_DISCARD UniqueArray<rsl::byte> read_file(card32 size, win::FileHandle file_handle);
  void write_file(const rsl::byte* data, card32 size, win::FileHandle file_handle);
  void append_file(win::FileHandle file);
  void trunc_file(win::FileHandle file);

  DEFINE_YES_NO_ENUM(FailIfExists);
  void copy_file(const Path& src, const Path& dst, FailIfExists fail_if_exists = FailIfExists::No);

  // query
  REX_NO_DISCARD bool does_exist(const Path& path);
  REX_NO_DISCARD bool does_exist(const StringView path);

  REX_NO_DISCARD bool is_directory(const Path& path);
  REX_NO_DISCARD bool is_directory(const StringView path);

  REX_NO_DISCARD bool is_file(const Path& path);
  REX_NO_DISCARD bool is_file(const StringView path);

  REX_NO_DISCARD bool is_readonly(const Path& path);
  REX_NO_DISCARD bool is_readonly(const StringView path);

  REX_NO_DISCARD bool is_valid_handle(win::FileHandle handle);

  REX_NO_DISCARD card32 file_size(win::FileHandle handle);

  REX_NO_DISCARD card64 creation_time(win::FileHandle handle);
  REX_NO_DISCARD card64 creation_time(const Path& path);

  REX_NO_DISCARD card64 modification_time(win::FileHandle handle);
  REX_NO_DISCARD card64 modification_time(const Path& path);

  REX_NO_DISCARD card64 access_time(win::FileHandle handle);
  REX_NO_DISCARD card64 access_time(const Path& path);

  REX_NO_DISCARD TimePoint creation_timepoint(win::FileHandle handle);
  REX_NO_DISCARD TimePoint creation_timepoint(const Path& path);

  REX_NO_DISCARD TimePoint modification_timepoint(win::FileHandle handle);
  REX_NO_DISCARD TimePoint modification_timepoint(const Path& path);

  REX_NO_DISCARD TimePoint access_timepoint(win::FileHandle handle);
  REX_NO_DISCARD TimePoint access_timepoint(const Path& path);

  // attributes
  void add_readonly_attribute(const Path& path);
  void add_readonly_attribute(const StringView path);

  void remove_readonly_attribute(const Path& path);
  void remove_readonly_attribute(const StringView path);
} // namespace vfs

REX_RSL_END_NAMESPACE