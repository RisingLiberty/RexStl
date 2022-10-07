// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_file.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/filesystem/win/win_file.h"

#include "rex_std/string_view.h"
#include "rex_std_extra/diagnostics/logging.h"
#include "rex_std_extra/filesystem/win/win_virtual_file_system.h"
#include "rex_std_extra/memory/memory_size.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

#define NOMINMAX
#include <Windows.h>

REX_RSL_BEGIN_NAMESPACE

constexpr MemorySize MaxFileSizeToReadOnConstruction = 1_gib;

String data_to_string(const char8* src, card32 size)
{
  return String(src, size);
}

template <typename StringType>
UniqueArray<StringType> data_to_lines(const rsl::byte* data, card32 size)
{
  const char8* data_as_char = reinterpret_cast<const char8*>(data);

  card32 num_new_line_chars = (card32)rsl::count_if(data_as_char, data_as_char + size, [](char8 c) { return c == '\n'; });

  vector<StringType> lines;
  lines.reserve(num_new_line_chars);

  StringType line;
  card32 length = 0;
  card32 start  = 0;

  for(card32 i = 0; i < size; ++i)
  {
    char8 c = data_as_char[i];

    if(length == 0)
    {
      if(c == '\0' || c == '\t' || c == '\n' || c == '\r')
      {
        ++start;
        continue;
      }
    }

    if(c == '\n' || c == '\r')
    {
      line = StringView(&data_as_char[start], length);
      lines.push_back(line);
      start += length + 1;
      length = 0;
    }
    else
    {
      ++length;
    }
  }

  if(length > 0)
  {
    line = StringView(&data_as_char[start], length);
    lines.push_back(line);
  }

  UniqueArray<StringType> result = make_unique<StringType[]>(lines.size());
  rsl::copy(lines.cbegin(), lines.cend(), result.get());
  return result;
}
UniqueArray<rsl::byte> read_from_disk(win::FileHandle file_handle)
{
  card32 file_size = vfs::file_size(file_handle);
  return vfs::read_file(file_size, file_handle);
}
void check_for_big_file_size(win::FileHandle file_handle)
{
  if(vfs::file_size(file_handle) > MaxFileSizeToReadOnConstruction)
  {
    REX_WARN("Reading in big file, is this needed?");
  }
}
String read_string_from_buff(StreamBuff& stream_buff)
{
  card32 start_pos = stream_buff.read_cursor_pos();
  card32 length    = 0;
  char8 c          = stream_buff.getc();
  while(c && c != stream_buff.eof())
  {
    ++length;
    c = stream_buff.getc();
  }

  stream_buff.set_read_cursor_pos(start_pos);
  String result;
  result.resize(length);
  stream_buff.getn(result.data(), length);
  stream_buff.set_read_cursor_pos(stream_buff.read_cursor_pos() + 1); // skip the null termination char
  return result;
}
void write_string_to_buff(StringView str, StreamBuff& stream_buff)
{
  stream_buff.putn(str.data(), str.length() + 1);
}

REX_RSL_END_NAMESPACE

rsl::File::File()
    : m_file_handle(INVALID_HANDLE_VALUE)
    , m_path()
    , m_is_open(false)
    , m_is_read_only_at_startup(false)
    , m_open_flags()
{
}
rsl::File::File(const Path& path, OpenFlags open_flags)
    : File(StringView(path), open_flags)
{
}
rsl::File::File(const StringView path, OpenFlags open_flags)
    : m_file_handle(vfs::open_or_create_file(path, OpenFlags::ReadWrite | open_flags))
    , m_path(path)
    , m_is_open(vfs::is_valid_handle(m_file_handle))
    , m_is_read_only_at_startup(vfs::is_readonly(path))
    , m_open_flags(open_flags)
{
  init_file_data();
}
rsl::File::File(const char8* path, OpenFlags open_flags)
    : File(StringView(path), open_flags)
{
  REX_ASSERT_X(path, "nullptr provided to path, this is not allowed");
}
rsl::File::File(File&& other) noexcept
    : IOStream(rsl::move(other))
    , m_file_handle(rsl::move(other.m_file_handle))
    , m_path(rsl::move(other.m_path))
    , m_is_open(rsl::move(other.m_is_open))
    , m_is_read_only_at_startup(rsl::move(other.m_is_read_only_at_startup))
    , m_open_flags(rsl::move(other.m_open_flags))
{
  other.m_file_handle             = INVALID_HANDLE_VALUE;
  other.m_path                    = "";
  other.m_is_open                 = false;
  other.m_is_read_only_at_startup = false;
}
rsl::File::~File()
{
  close();
}
rsl::File& rsl::File::operator=(File&& other) noexcept
{
  swap_adl(stream_buff(), other.stream_buff());
  swap_adl(m_file_handle, other.m_file_handle);
  swap_adl(m_path, other.m_path);
  swap_adl(m_is_open, other.m_is_open);
  swap_adl(m_is_read_only_at_startup, other.m_is_read_only_at_startup);
  swap_adl(m_open_flags, other.m_open_flags);

  return *this;
}

void rsl::File::flush()
{
  // Nothing to implement
}
const rsl::Path& rsl::File::path() const
{
  return m_path;
}
const rsl::byte* rsl::File::data() const
{
  return reinterpret_cast<const rsl::byte*>(stream_buff().stream_data());
}
const rsl::byte* rsl::File::read_cursor_pos_data() const
{
  return reinterpret_cast<const rsl::byte*>(stream_buff().read_cursor_pos_pointer());
}
rsl::String rsl::File::data_as_string() const
{
  return data_to_string(stream_buff().stream_data(), stream_buff().write_cursor_pos());
}
rsl::UniqueArray<rsl::String> rsl::File::lines() const
{
  return data_to_lines<String>(data(), stream_size());
}
rsl::UniqueArray<rsl::StringView> rsl::File::line_views() const
{
  return data_to_lines<StringView>(data(), stream_size());
}
bool rsl::File::open(const StringView path, OpenFlags open_flags)
{
  *this = File(path, open_flags);
  return is_open();
}
bool rsl::File::open(const Path& path, OpenFlags open_flags)
{
  return open(StringView(path), open_flags);
}
bool rsl::File::open(const char8* path, OpenFlags open_flags)
{
  return open(StringView(path), open_flags);
}
bool rsl::File::is_open() const
{
  return m_is_open;
}
void rsl::File::append()
{
  append_file_ptr();
}
void rsl::File::trunc()
{
  reset_file_ptr();
  stream_buff().flush();
}
void rsl::File::close()
{
  if(!m_is_read_only_at_startup && is_open())
  {
    if(m_open_flags & OpenFlags::Write)
    {
      if(m_open_flags & OpenFlags::Read)
      {
        reset_file_ptr();
      }
      save_to_disk();
    }
  }
}
void rsl::File::skip(card32 bytes)
{
  set_read_cursor_pos(bytes);
}
bool rsl::File::eof() const
{
  return read_cursor_pos() > file_size();
}
card32 rsl::File::file_size() const
{
  return write_cursor_pos();
}
void rsl::File::read(void* address, card32 size)
{
  REX_ASSERT_X(read_cursor_pos() + size <= file_size(), "Trying to read passed file's size");
  stream_buff().getn((char8*)address, size);
}
void rsl::File::write_string(StringView str)
{
  write_string_to_buff(str, stream_buff());
}
rsl::String rsl::File::read_string()
{
  return read_string_from_buff(stream_buff());
}
bool rsl::File::is_readonly() const
{
  return vfs::is_readonly(m_path);
}
void rsl::File::add_readonly_attribute()
{
  vfs::add_readonly_attribute(m_path);
}
void rsl::File::remove_readonly_attribute()
{
  vfs::remove_readonly_attribute(m_path);
}
void rsl::File::write(const void* data, size_t size)
{
  stream_buff().putn((const char8*)data, (card32)size);
}
void rsl::File::save_to_disk()
{
  vfs::write_file(reinterpret_cast<const rsl::byte*>(stream_buff().stream_data()), (card32)stream_buff().write_cursor_pos(), m_file_handle);
}
void rsl::File::reset_file_ptr()
{
  vfs::trunc_file(m_file_handle);
}
void rsl::File::append_file_ptr()
{
  vfs::append_file(m_file_handle);
}
void rsl::File::init_file_data()
{
  if(m_open_flags & OpenFlags::Trunc)
  {
    trunc(); // truncate all file content
  }
  else if(m_open_flags & OpenFlags::Read)
  {
    read_file_data();
  }
  else if(m_open_flags & OpenFlags::App)
  {
    read_file_data();
    append(); // put file pointer at the end
  }
  // the reason app is default without opening flags is
  // because we don't want to accidentally remove file data when
  // we open a file without specifying if we should trunc or append to it
  else
  {
    REX_WARN("No opening flags specified, will append");
    append();
  }
}
void rsl::File::read_file_data()
{
  if(!is_open())
    return;

#ifdef REX_ENABLE_BIG_FILE_SIZE_CHECK
  check_for_big_file_size(m_file_handle);
#endif

  UniqueArray<rsl::byte> data = read_from_disk(m_file_handle);
  card32 data_size            = data.count();
  UniqueArray<char8> char_data(reinterpret_cast<char8*>(data.release()), data_size);
  init(rsl::move(char_data));
}

//
// IFile
//

rsl::IFile::IFile()
    : m_file_handle(INVALID_HANDLE_VALUE)
    , m_path()
    , m_is_open(false)
    , m_is_read_only_at_startup(false)
{
}
rsl::IFile::IFile(const Path& path)
    : IFile(StringView(path))
{
}
rsl::IFile::IFile(const StringView path)
    : m_file_handle(vfs::open_existing_file(path, OpenFlags::Read))
    , m_path(path)
    , m_is_open(vfs::is_valid_handle(m_file_handle))
    , m_is_read_only_at_startup(vfs::is_readonly(path))
{
  read_file_data();
}
rsl::IFile::IFile(const char8* path)
    : IFile(StringView(path))
{
  REX_ASSERT_X(path, "nullptr provided to path, this is not allowed");
}
rsl::IFile::IFile(IFile&& other) noexcept
    : IStream(rsl::move(other))
    , m_file_handle(other.m_file_handle)
    , m_path(other.m_path)
    , m_is_open(other.m_is_open)
    , m_is_read_only_at_startup(other.m_is_read_only_at_startup)
{
  other.m_file_handle             = INVALID_HANDLE_VALUE;
  other.m_path                    = "";
  other.m_is_open                 = false;
  other.m_is_read_only_at_startup = false;
}
rsl::IFile::~IFile()
{
  close();
}
rsl::IFile& rsl::IFile::operator=(IFile&& other) noexcept
{
  swap_adl(stream_buff(), other.stream_buff());
  swap_adl(m_file_handle, other.m_file_handle);
  swap_adl(m_path, other.m_path);
  swap_adl(m_is_open, other.m_is_open);
  swap_adl(m_is_read_only_at_startup, other.m_is_read_only_at_startup);

  return *this;
}
const rsl::Path& rsl::IFile::path() const
{
  return m_path;
}
const rsl::byte* rsl::IFile::data() const
{
  return reinterpret_cast<const rsl::byte*>(stream_buff().stream_data());
}
const rsl::byte* rsl::IFile::read_cursor_pos_data() const
{
  return reinterpret_cast<const rsl::byte*>(stream_buff().read_cursor_pos_pointer());
}
rsl::String rsl::IFile::data_as_string() const
{
  return data_to_string(stream_buff().stream_data(), stream_buff().write_cursor_pos());
}
rsl::UniqueArray<rsl::String> rsl::IFile::lines() const
{
  return data_to_lines<String>(data(), stream_buff().stream_size());
}
rsl::UniqueArray<rsl::StringView> rsl::IFile::line_views() const
{
  return data_to_lines<StringView>(data(), stream_buff().stream_size());
}
bool rsl::IFile::is_open() const
{
  return m_is_open;
}
bool rsl::IFile::open(const StringView path)
{
  *this = IFile(path);
  return is_open();
}
bool rsl::IFile::open(const Path& path)
{
  return open(StringView(path));
}
bool rsl::IFile::open(const char8* path)
{
  return open(StringView(path));
}
void rsl::IFile::close()
{
  if(is_open())
  {
    vfs::close_file(m_file_handle);
  }

  m_is_open = false;
  flush();
}
void rsl::IFile::skip(card32 bytes)
{
  set_read_cursor_pos(bytes);
}
card32 rsl::IFile::file_size() const
{
  return stream_size();
}
bool rsl::IFile::eof() const
{
  return read_cursor_pos() >= file_size();
}
void rsl::IFile::read(void* address, card32 size)
{
  stream_buff().getn((char8*)address, size);
}
rsl::String rsl::IFile::read_string()
{
  return read_string_from_buff(stream_buff());
}
bool rsl::IFile::is_readonly() const
{
  return vfs::is_readonly(m_path);
}
void rsl::IFile::add_readonly_attribute()
{
  vfs::add_readonly_attribute(m_path);
}
void rsl::IFile::remove_readonly_attribute()
{
  vfs::remove_readonly_attribute(m_path);
}
void rsl::IFile::read_file_data()
{
  if(!is_open())
    return;

#ifdef REX_ENABLE_BIG_FILE_SIZE_CHECK
  check_for_big_file_size(m_file_handle);
#endif

  UniqueArray<rsl::byte> data = read_from_disk(m_file_handle);
  card32 data_size            = data.count();
  UniqueArray<char8> char_data(reinterpret_cast<char8*>(data.release()), data_size);
  init(rsl::move(char_data));
}

//
// OFile
//

rsl::OFile::OFile()
    : m_file_handle(INVALID_HANDLE_VALUE)
    , m_path()
    , m_is_open(false)
    , m_open_flags()
{
}
rsl::OFile::OFile(const Path& path, OpenFlags open_flags)
    : OFile(StringView(path), open_flags)
{
}
rsl::OFile::OFile(const StringView path, OpenFlags open_flags)
    : m_file_handle(vfs::open_or_create_file(path, open_flags | OpenFlags::Write))
    , m_path(path)
    , m_is_open(vfs::is_valid_handle(m_file_handle))
    , m_open_flags(open_flags)
{
  init_file_data();
}
rsl::OFile::OFile(const char8* path, OpenFlags open_flags)
    : OFile(StringView(path), open_flags)
{
  REX_ASSERT_X(path, "nullptr provided to path, this is not allowed");
}
rsl::OFile::OFile(OFile&& other) noexcept
    : OStream(rsl::move(other))
    , m_file_handle(other.m_file_handle)
    , m_path(other.m_path)
    , m_is_open(other.m_is_open)
    , m_open_flags(other.m_open_flags)
{
  other.m_file_handle = INVALID_HANDLE_VALUE;
  other.m_path        = "";
  other.m_is_open     = false;
}
rsl::OFile::~OFile()
{
  close();
}
rsl::OFile& rsl::OFile::operator=(OFile&& other) noexcept
{
  swap_adl(stream_buff(), other.stream_buff());
  swap_adl(m_file_handle, other.m_file_handle);
  swap_adl(m_path, other.m_path);
  swap_adl(m_is_open, other.m_is_open);
  swap_adl(m_open_flags, other.m_open_flags);

  return *this;
}
void rsl::OFile::flush()
{
  // Nothing to implement
}
const rsl::Path& rsl::OFile::path() const
{
  return m_path;
}
const rsl::byte* rsl::OFile::data() const
{
  return reinterpret_cast<const rsl::byte*>(stream_buff().stream_data());
}
bool rsl::OFile::is_open() const
{
  return m_is_open;
}
void rsl::OFile::append()
{
  append_file_ptr();
}
void rsl::OFile::trunc()
{
  vfs::trunc_file(m_file_handle);
  stream_buff().flush();
}
bool rsl::OFile::open(const StringView path, OpenFlags open_flags)
{
  *this = OFile(path, open_flags);
  return is_open();
}
bool rsl::OFile::open(const Path& path, OpenFlags open_flags)
{
  return open(StringView(path), open_flags);
}
bool rsl::OFile::open(const char8* path, OpenFlags open_flags)
{
  return open(StringView(path), open_flags);
}
void rsl::OFile::close()
{
  if(!is_open())
    return;

  save_to_disk();

  vfs::close_file(m_file_handle);

  m_is_open = false;
}
bool rsl::OFile::is_readonly() const
{
  return vfs::is_readonly(m_path);
}
card32 rsl::OFile::file_size() const
{
  // OFile never reads the existing file content
  // so the stream size will never have the disk data, even with append flag
  return stream_size() + vfs::file_size(m_file_handle);
}
void rsl::OFile::add_readonly_attribute()
{
  vfs::add_readonly_attribute(m_path);
}
void rsl::OFile::remove_readonly_attribute()
{
  vfs::remove_readonly_attribute(m_path);
}
void rsl::OFile::write(const void* data, size_t size)
{
  stream_buff().putn((const char8*)data, (card32)size);
}
void rsl::OFile::write_string(const StringView str)
{
  write_string_to_buff(str, stream_buff());
}
void rsl::OFile::save_to_disk()
{
  vfs::write_file(data(), (card32)stream_buff().write_cursor_pos(), m_file_handle);
}
void rsl::OFile::reset_file_ptr()
{
  vfs::trunc_file(m_file_handle);
}
void rsl::OFile::append_file_ptr()
{
  vfs::append_file(m_file_handle);
}
void rsl::OFile::init_file_data()
{
  if(!is_open())
    return;

  if(m_open_flags & OpenFlags::Trunc)
  {
    trunc(); // truncate all file content
  }
  else if(m_open_flags & OpenFlags::App)
  {
    append(); // put file pointer at the end
  }
  // the reason app is default without opening flags is
  // because we don't want to accidentally remove file data when
  // we open a file without specifying if we should trunc or append to it
  else
  {
    REX_WARN("no opening flags specfied, will append");
    append();
  }
}