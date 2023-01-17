// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_virtual_file_system.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/filesystem/win/win_virtual_file_system.h"

#include "rex_std_extra/containers/vector.h"
#include "rex_std_extra/diagnostics/win/win_call.h"
#include "rex_std_extra/rex_stl_extra_pch.h"
#include "rex_std_extra/time/win/win_time_functions.h"

#define NOMINMAX
#include <ShlObj.h>
#include <Windows.h>

REX_RSL_BEGIN_NAMESPACE::vfs::internal
{
  MediumStackString g_app_name;
  Path g_root_path = ".";
  rsl::unordered_map<MountHash, Path> g_mounts;

  bool does_exist(const char8* path);
  bool is_directory(const char8* path);
  bool is_file(const char8* path);
  bool is_readonly(const char8* path);

  // checks without using create_file_path
  bool does_exist_no_ext(const char8* path);
  bool is_directory_no_ext(const char8* path);
  bool is_file_no_ext(const char8* path);
  bool is_readonly_no_ext(const char8* path);

  Path create_absolute_file_path(const Path& path);

  void add_attribute(const char8* path, DWORD attribute)
  {
    DWORD attributes = GetFileAttributesA(path);
    WIN_CALL(SetFileAttributesA(path, attributes | attribute));
  }
  void remove_attribute(const char8* path, DWORD attribute)
  {
    DWORD attributes = GetFileAttributesA(path);
    WIN_CALL(SetFileAttributesA(path, attributes & !attribute));
  }

  void set_root_directory(const Path& root_path)
  {
    if(root_path.is_absolute())
    {
      g_root_path = root_path;
    }
    else
    {
      Path working_dir = working_directory();
      g_root_path      = working_dir / root_path;
    }
  }

  UniqueArray<Path> file_names_in_directory(const char8* path)
  {
    rsl::vector<Path> file_names;
    WIN32_FIND_DATA find_data_result;

    // find the first file in the directory
    Path directory = internal::create_absolute_file_path(Path(path));

    directory += "\\*"; // this is needed to check for every file

    HANDLE dir_handle = WIN_CALL(FindFirstFileA(directory.data(), &find_data_result));
    if(dir_handle == INVALID_HANDLE_VALUE)
    {
      // empty directory
      return {};
    }

    // list all the files in the directory with some info about them
    do
    {
      if(!(find_data_result.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      {
        file_names.push_back(find_data_result.cFileName);
      }
    } while(WIN_CALL_IGNORE(FindNextFileA(dir_handle, &find_data_result), ERROR_NO_MORE_FILES) != 0);

    // for some reason, FindNextFileA sets the last error code twice
    win::clear_win_errors();
    WIN_CALL(FindClose(dir_handle));

    // unfortunately we have to copy these over
    // we might want to return a vector instead
    UniqueArray<Path> result = make_unique<Path[]>(file_names.size());
    rsl::copy(file_names.cbegin(), file_names.cend(), result.get());
    return result;
  }

  Path create_path_from_root(const char8* path)
  {
    return g_root_path / path;
  }
  Path create_absolute_file_path(const Path& path)
  {
    if(path.is_absolute())
    {
      return path;
    }

    Path temp = create_path_from_root(path.data());

    if(temp.is_absolute())
      return temp;

    Path working_dir = working_directory();
    return working_dir / temp;
  }

  void create_directory(const char8* path)
  {
    Path directory = create_absolute_file_path(StringView(path));
    WIN_CALL(CreateDirectoryA(directory.data(), NULL));
  }

  void create_directory_recursive(const char8* path)
  {
    vector<StringView> folder_names;

    Path full_path                         = create_absolute_file_path(StringView(path));
    const Path::string_type& full_path_str = full_path.as_string();

    auto start = full_path_str.cbegin();
    auto end   = full_path_str.cbegin();
    for(auto it = full_path_str.cbegin(); it != full_path_str.cend(); ++it)
    {
      if(*it == '/')
      {
        const char8* start_ptr = const_iterator_to_pointer(start);
        const char8* end_ptr   = const_iterator_to_pointer(end);
        StringView folder_name(start_ptr, static_cast<card32>(end_ptr - start_ptr));

        if(folder_name.length() > 0)
        {
          folder_names.push_back(folder_name);
        }
        start = end;
        start++;
      }

      ++end;
    }

    const char8* start_ptr = const_iterator_to_pointer(start);
    const char8* end_ptr   = const_iterator_to_pointer(end);

    StringView name(start_ptr, static_cast<card32>(end_ptr - start_ptr));

    if(name.length() > 0)
    {
      folder_names.push_back(name);
    }

    Path::string_type directory;
    for(StringView folder_name: folder_names)
    {
      directory += folder_name;
      WIN_CALL_IGNORE(CreateDirectoryA(directory.data(), NULL), ERROR_ALREADY_EXISTS);
      directory += "/";
    }
  }

  win::FileHandle create_file(const char8* path)
  {
    Path directory = create_absolute_file_path(StringView(path));

    return WIN_CALL(CreateFileA(directory.data(),             // path to file
                                GENERIC_READ | GENERIC_WRITE, // generic read and write access
                                FILE_SHARE_READ,              // other processes can also read the file
                                NULL,                         // no SECURITY_ATTRIBUTES
                                CREATE_NEW,                   // create a new file, error when it already exists
                                FILE_FLAG_SEQUENTIAL_SCAN,    // files will be read from beginning to end
                                NULL                          // no template file
                                ));
  }

  void delete_directory(const char8* path)
  {
    Path directory = create_absolute_file_path(StringView(path));
    WIN_CALL(RemoveDirectoryA(directory.data()));
  }
  void delete_file(const char8* path)
  {
    Path directory = create_absolute_file_path(StringView(path));
    WIN_CALL(DeleteFileA(directory.data()));
  }

  win::FileHandle open_existing_file(const char8* path, OpenFlags open_flags)
  {
    // Remember, this might fail if a file is marked readonly
    // and we read it without the read only attribute

    // working directory is added in vfs::does_exist
    Path full_path = create_absolute_file_path(StringView(path));

    if(!does_exist_no_ext(full_path.data()))
    {
      REX_ERROR("Trying to open non-existing file");
      REX_ERROR("Path: ", create_absolute_file_path(StringView(path)));
      return INVALID_HANDLE_VALUE;
    }

    DWORD access_flags = 0;
    if(open_flags & OpenFlags::Read)
      access_flags |= GENERIC_READ;
    if(open_flags & OpenFlags::Write)
      access_flags |= GENERIC_WRITE;

    DWORD attributes = FILE_FLAG_SEQUENTIAL_SCAN; // files will be read from beginning to end
    if(is_readonly_no_ext(full_path.data()))
    {
      if(open_flags & OpenFlags::Write)
      {
        REX_WARN("Trying to open readonly file with write access");
        REX_WARN("<", path, ">");
        return INVALID_HANDLE_VALUE;
      }
      attributes |= FILE_ATTRIBUTE_READONLY;
    }

    return WIN_CALL_IGNORE(CreateFileA(full_path.data(), // path to file
                                       access_flags,     // general read and/or write access
                                       FILE_SHARE_READ,  // other processes can also read the file
                                       NULL,             // no SECURITY_ATTRIBUTES
                                       OPEN_EXISTING,    // open existing file, error if doesn't exist
                                       attributes,       // attributes, how to read the file
                                       NULL              // no template file
                                       ),
                           ERROR_ALREADY_EXISTS);
  }
  win::FileHandle open_or_create_file(const char8* path, OpenFlags open_flags)
  {
    if(open_flags & OpenFlags::OpenExisting)
    {
      return open_existing_file(path, open_flags);
    }

    DWORD access_flags = 0;

    if(open_flags & OpenFlags::Read)
      access_flags |= GENERIC_READ;
    if(open_flags & OpenFlags::Write)
      access_flags |= GENERIC_WRITE;

    DWORD attributes = FILE_FLAG_SEQUENTIAL_SCAN; // files will be read from beginning to end
    Path directory   = create_absolute_file_path(StringView(path));

    if(does_exist_no_ext(directory.data()) && is_readonly_no_ext(directory.data()))
    {
      if(open_flags & OpenFlags::Write)
      {
        REX_WARN("Trying to open readonly file with write access");
        REX_WARN("<", path, ">");
        return INVALID_HANDLE_VALUE;
      }
      attributes |= FILE_ATTRIBUTE_READONLY;
    }

    return WIN_CALL_IGNORE(CreateFileA(directory.data(), // path to file
                                       access_flags,     // general read and write access
                                       FILE_SHARE_READ,  // other processes can also read the file
                                       NULL,             // no SECURITY_ATTRIBUTES
                                       OPEN_ALWAYS,      // always open the file
                                       attributes,       // attributes, how to read the file
                                       NULL              // no template file
                                       ),
                           ERROR_ALREADY_EXISTS);
  }

  void copy_file(const char8* src, const char8* dst, FailIfExists fail_if_exists)
  {
    Path src_path = create_absolute_file_path(StringView(src));
    Path dst_path = create_absolute_file_path(StringView(dst));

    if(!does_exist_no_ext(src_path.data()))
    {
      REX_ERROR("vfs::copy_file: src path does not exist: ", src);
    }

    if(!does_exist_no_ext(dst_path.data()))
    {
      REX_ERROR("vfs::copy_file: dst path does not exist: ", dst);
    }

    WIN_CALL(CopyFileA(src_path.data(), dst_path.data(), fail_if_exists));
  }

  bool does_exist(const char8* path)
  {
    Path full_path = create_absolute_file_path(StringView(path));
    return does_exist_no_ext(full_path.data());
  }
  bool is_directory(const char8* path)
  {
    Path full_path = create_absolute_file_path(StringView(path));
    return is_directory_no_ext(full_path.data());
  }
  bool is_file(const char8* path)
  {
    Path full_path = create_absolute_file_path(StringView(path));
    return is_file_no_ext(full_path.data());
  }
  bool is_readonly(const char8* path)
  {
    Path full_path = create_absolute_file_path(StringView(path));
    return is_readonly_no_ext(full_path.data());
  }

  bool does_exist_no_ext(const char8* path)
  {
    DWORD attribs = GetFileAttributesA(path);
    return !(attribs & FILE_ATTRIBUTE_DEVICE);
  }
  bool is_directory_no_ext(const char8* path)
  {
    DWORD attribs = GetFileAttributesA(path);
    return attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY);
  }
  bool is_file_no_ext(const char8* path)
  {
    DWORD attribs = GetFileAttributesA(path);
    return attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY);
  }
  bool is_readonly_no_ext(const char8* path)
  {
    DWORD attribs = GetFileAttributesA(path);
    return attribs & FILE_ATTRIBUTE_READONLY;
  }

  void add_readonly_attribute(const char8* path)
  {
    Path dir = create_absolute_file_path(StringView(path));
    add_attribute(dir.data(), FILE_ATTRIBUTE_READONLY);
  }
  void remove_readonly_attribute(const char8* path)
  {
    Path dir = create_absolute_file_path(StringView(path));
    remove_attribute(dir.data(), FILE_ATTRIBUTE_READONLY);
  }

  bool is_mounted(MountHash hash)
  {
    return g_mounts.contains(hash);
  }

  void mount(MountHash hash, const char8* path)
  {
    REX_ASSERT_X(!is_mounted(hash), "trying to mount hash that's already mounted");

    g_mounts.emplace(hash, path);
  }
  void remount(MountHash hash, const char8* path)
  {
    g_mounts[hash] = path;
  }
  void unmount(MountHash hash)
  {
    REX_ASSERT_X(g_mounts.contains(hash), "Trying to unmount hash that doesn't exists");
    g_mounts.erase(hash);
  }
}

void rsl::vfs::set_root_directory(const Path& root)
{
  internal::set_root_directory(root);
}
void rsl::vfs::set_root_directory(StringView root)
{
  internal::set_root_directory(Path(root));
}

void rsl::vfs::init(const StringView name, StringView root_path)
{
  internal::g_app_name = name;
  set_root_directory(root_path);
}

void rsl::vfs::shutdown() {}

const rsl::Path& rsl::vfs::root_directory()
{
  return internal::g_root_path;
}
rsl::Path rsl::vfs::working_directory()
{
  rsl::Path::string_type dir;
  WIN_CALL(GetCurrentDirectoryA((DWORD)dir.max_size(), dir.data()));
  dir.reset_null_termination_offset();
  return Path(dir);
}
rsl::Path rsl::vfs::app_directory()
{
  rsl::Path::string_type app_directory;
  GetModuleFileNameA(NULL, app_directory.data(), (DWORD)app_directory.size());
  return Path(app_directory);
}
rsl::Path rsl::vfs::user_app_directory()
{
  rsl::Path::string_type appdata_path;
  SHGetFolderPathA(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, appdata_path.data());
  appdata_path.reset_null_termination_offset();
  Path app_dir(appdata_path);

  return app_dir /= internal::g_app_name;
}

rsl::Path rsl::vfs::make_relative_to_root(const Path& path)
{
  Path target_path = path.relative(root_directory());

  if(target_path.empty())
  {
    target_path = path;
  }

  return target_path;
}

rsl::UniqueArray<rsl::Path> rsl::vfs::file_names_in_directory(const Path& path)
{
  return internal::file_names_in_directory(path.data());
}
rsl::UniqueArray<rsl::Path> rsl::vfs::file_names_in_directory(const StringView path)
{
  return internal::file_names_in_directory(path.data());
}

rsl::Path rsl::vfs::create_path_from_root(const Path& path)
{
  return internal::create_path_from_root(path.data());
}
rsl::Path rsl::vfs::create_path_from_root(const StringView path)
{
  return internal::create_path_from_root(path.data());
}

rsl::Path rsl::vfs::create_absolute_file_path(const Path& path)
{
  return internal::create_absolute_file_path(path);
}
rsl::Path rsl::vfs::create_absolute_file_path(const StringView path)
{
  return internal::create_absolute_file_path(path);
}
rsl::Path rsl::vfs::create_absolute_file_path(const MountHash hash)
{
  return internal::create_absolute_file_path(Path(internal::g_mounts.at(hash)));
}

bool rsl::vfs::is_mounted(MountHash hash)
{
  return internal::is_mounted(hash);
}

rsl::vfs::MountHash rsl::vfs::mount(MountHash hash, const StringView path)
{
  rsl::vfs::internal::mount(hash, path.data());
  return hash;
}
rsl::vfs::MountHash rsl::vfs::mount(MountHash hash, const Path& path)
{
  internal::mount(hash, path.data());
  return hash;
}

rsl::vfs::MountHash rsl::vfs::remount(MountHash hash, const StringView path)
{
  internal::remount(hash, path.data());
  return hash;
}
rsl::vfs::MountHash rsl::vfs::remount(MountHash hash, const Path& path)
{
  internal::remount(hash, path.data());
  return hash;
}

rsl::vfs::MountHash rsl::vfs::ummount(MountHash hash)
{
  internal::unmount(hash);
  return hash;
}

void rsl::vfs::create_directory(const Path& path)
{
  internal::create_directory(path.data());
}
void rsl::vfs::create_directory(const StringView path)
{
  internal::create_directory(path.data());
}

void rsl::vfs::create_directory_recursive(const Path& dir)
{
  internal::create_directory_recursive(dir.data());
}
void rsl::vfs::create_directory_recusrive(const StringView dir)
{
  internal::create_directory_recursive(dir.data());
}

rsl::win::FileHandle rsl::vfs::create_file(const Path& path)
{
  return internal::create_file(path.data());
}
rsl::win::FileHandle rsl::vfs::create_file(const StringView path)
{
  return internal::create_file(path.data());
}

void rsl::vfs::delete_directory(const Path& path)
{
  internal::delete_directory(path.data());
}
void rsl::vfs::delete_directory(const StringView path)
{
  internal::delete_directory(path.data());
}

void rsl::vfs::delete_file(const Path& path)
{
  internal::delete_file(path.data());
}
void rsl::vfs::delete_file(const StringView path)
{
  internal::delete_file(path.data());
}

rsl::win::FileHandle rsl::vfs::open_existing_file(const Path& path, OpenFlags open_flags)
{
  return internal::open_existing_file(path.data(), open_flags);
}
rsl::win::FileHandle rsl::vfs::open_existing_file(const StringView path, OpenFlags open_flags)
{
  return internal::open_existing_file(path.data(), open_flags);
}

rsl::win::FileHandle rsl::vfs::open_or_create_file(const Path& path, OpenFlags open_flags)
{
  return internal::open_or_create_file(path.data(), open_flags);
}
rsl::win::FileHandle rsl::vfs::open_or_create_file(const StringView path, OpenFlags open_flags)
{
  return internal::open_or_create_file(path.data(), open_flags);
}

void rsl::vfs::close_file(win::FileHandle file_handle)
{
  WIN_CALL(CloseHandle(file_handle));
}

rsl::UniqueArray<rsl::byte> rsl::vfs::read_file(card32 size, win::FileHandle file_handle)
{
  UniqueArray<rsl::byte> buffer = make_unique<rsl::byte[]>(size);

  DWORD bytes_read = 0;
  WIN_CALL(ReadFile(file_handle, buffer.get(), size, &bytes_read, NULL));

  REX_ASSERT_X(bytes_read == static_cast<DWORD>(size), "the number of bytes read doesn't match the file size");
  return buffer;
}
void rsl::vfs::write_file(const rsl::byte* data, card32 size, win::FileHandle file_handle)
{
  DWORD bytes_written = 0;
  WIN_CALL(WriteFile(file_handle, data, size, &bytes_written, NULL));
}
void rsl::vfs::append_file(win::FileHandle file)
{
  WIN_CALL(SetFilePointer(file, 0, NULL, FILE_END));
  WIN_CALL(SetEndOfFile(file));
}
void rsl::vfs::trunc_file(win::FileHandle file)
{
  WIN_CALL(SetFilePointer(file, 0, NULL, FILE_BEGIN));
  WIN_CALL(SetEndOfFile(file));
}

void rsl::vfs::copy_file(const Path& src, const Path& dst, FailIfExists fail_if_exists)
{
  internal::copy_file(src.data(), dst.data(), fail_if_exists);
}

bool rsl::vfs::does_exist(const Path& path)
{
  return internal::does_exist(path.data());
}
bool rsl::vfs::does_exist(const StringView path)
{
  return internal::does_exist(path.data());
}
bool rsl::vfs::is_directory(const Path& path)
{
  return internal::is_directory(path.data());
}
bool rsl::vfs::is_directory(const StringView path)
{
  return internal::is_directory(path.data());
}
bool rsl::vfs::is_file(const Path& path)
{
  return internal::is_file(path.data());
}
bool rsl::vfs::is_file(const StringView path)
{
  return internal::is_file(path.data());
}
bool rsl::vfs::is_readonly(const Path& path)
{
  return internal::is_readonly(path.data());
}
bool rsl::vfs::is_readonly(const StringView path)
{
  return internal::is_readonly(path.data());
}
bool rsl::vfs::is_valid_handle(win::FileHandle handle)
{
  return handle != INVALID_HANDLE_VALUE;
}

card32 rsl::vfs::file_size(win::FileHandle file)
{
  LARGE_INTEGER size {};
  WIN_CALL(GetFileSizeEx(file, &size));
  uint64 unsigned_file_size = 0;
  memcpy(&unsigned_file_size, &size, sizeof(unsigned_file_size));

  REX_ASSERT_X(unsigned_file_size < rsl::NumericLimits<card32>::max(), "file size larget than card32 max, this is unsupported");

  return static_cast<card32>(unsigned_file_size);
}

card64 rsl::vfs::creation_time(win::FileHandle file)
{
  FILETIME file_time;
  WIN_CALL(GetFileTime((HANDLE)file, &file_time, NULL, NULL));
  return win::to_integer(file_time);
}
card64 rsl::vfs::creation_time(const Path& path)
{
  win::FileHandle file_handle = open_existing_file(path, OpenFlags::Read);
  card64 time                 = creation_time(file_handle);
  close_file(file_handle);
  return time;
}
card64 rsl::vfs::modification_time(win::FileHandle file)
{
  FILETIME file_time;
  WIN_CALL(GetFileTime((HANDLE)file, NULL, NULL, &file_time));
  return win::to_integer(file_time);
}
card64 rsl::vfs::modification_time(const Path& path)
{
  win::FileHandle file_handle = open_existing_file(path, OpenFlags::Read);
  card64 time                 = modification_time(file_handle);
  close_file(file_handle);
  return time;
}
card64 rsl::vfs::access_time(win::FileHandle file)
{
  FILETIME file_time;
  WIN_CALL(GetFileTime((HANDLE)file, NULL, &file_time, NULL));
  return win::to_integer(file_time);
}
card64 rsl::vfs::access_time(const Path& path)
{
  win::FileHandle file_handle = open_existing_file(path, OpenFlags::Read);
  card64 time                 = access_time(file_handle);
  close_file(file_handle);
  return time;
}

rsl::TimePoint rsl::vfs::creation_timepoint(win::FileHandle file)
{
  FILETIME file_time;
  GetFileTime((HANDLE)file, &file_time, NULL, NULL);
  SYSTEMTIME sys_time = win::to_local_sys_time(file_time);
  return win::timepoint(sys_time);
}
rsl::TimePoint rsl::vfs::creation_timepoint(const Path& path)
{
  win::FileHandle file_handle = open_existing_file(path, OpenFlags::Read);
  TimePoint time              = creation_timepoint(file_handle);
  close_file(file_handle);
  return time;
}
rsl::TimePoint rsl::vfs::modification_timepoint(win::FileHandle file)
{
  FILETIME file_time;
  GetFileTime((HANDLE)file, NULL, NULL, &file_time);
  SYSTEMTIME sys_time = win::to_local_sys_time(file_time);
  return win::timepoint(sys_time);
}
rsl::TimePoint rsl::vfs::modification_timepoint(const Path& path)
{
  win::FileHandle file_handle = open_existing_file(path, OpenFlags::Read);
  TimePoint time              = modification_timepoint(file_handle);
  close_file(file_handle);
  return time;
}
rsl::TimePoint rsl::vfs::access_timepoint(win::FileHandle file)
{
  FILETIME file_time;
  GetFileTime((HANDLE)file, NULL, &file_time, NULL);
  SYSTEMTIME sys_time = win::to_local_sys_time(file_time);
  return win::timepoint(sys_time);
}
rsl::TimePoint rsl::vfs::access_timepoint(const Path& path)
{
  win::FileHandle file_handle = open_existing_file(path, OpenFlags::Read);
  TimePoint time              = access_timepoint(file_handle);
  close_file(file_handle);
  return time;
}

void rsl::vfs::add_readonly_attribute(const Path& path)
{
  internal::add_readonly_attribute(path.data());
}
void rsl::vfs::add_readonly_attribute(const StringView path)
{
  internal::add_readonly_attribute(path.data());
}

void rsl::vfs::remove_readonly_attribute(const Path& path)
{
  internal::remove_readonly_attribute(path.data());
}
void rsl::vfs::remove_readonly_attribute(const StringView path)
{
  internal::remove_readonly_attribute(path.data());
}