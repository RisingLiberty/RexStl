// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: filepath_iterator.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/filesystem/filepath_iterator.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::PathIterator::PathIterator() = default;
rsl::PathIterator::PathIterator(const BaseIterator& pos, const Path* total_path)
    : m_position(pos)
    , m_sub_path()
    , m_total_path(total_path)
{
}
rsl::PathIterator::PathIterator(const BaseIterator& pos, Path::string_view_type sub_path_text, const Path* total_path)
    : m_position(pos)
    , m_sub_path(sub_path_text)
    , m_total_path(total_path)
{
}

rsl::PathIterator::reference rsl::PathIterator::operator*() const
{
  return m_sub_path;
}
rsl::PathIterator::pointer rsl::PathIterator::operator->() const
{
  return rsl::addressof(m_sub_path);
}

rsl::PathIterator& rsl::PathIterator::operator++()
{
  const auto& total_path_text = m_total_path->as_string();
  const auto sub_path_size    = m_sub_path.as_string().size();
  const auto begin            = total_path_text.data();
  const auto end              = begin + total_path_text.size();

  // test if the next m_sub_path will be root-directory
  if(points_to_begin())
  {
    m_position += static_cast<ptrdiff_t>(sub_path_size);
    const auto first              = total_path_text.data();
    const auto last               = first + total_path_text.size();
    const auto root_name_end      = find_root_name_end(first, last);
    const auto root_directory_end = rsl::find_if_not(root_name_end, last, is_slash);

    // current m_sub_path is root-name, root-directory exists, so next is root-directory
    if(first != root_name_end && root_name_end != root_directory_end)
    {
      m_sub_path.assign(root_name_end, root_directory_end);
      return *this;
    }

    // if we get here, either there is no root-name, and by !is_slash(*position), no root-directory,
    // or, current m_sub_path is root-name, and root-directory doesn't exist.
    // either way, the next m_sub_path is the first or relative path
  }

  // current m_sub_path is root-directory, or the "magic empty path"
  else if(is_slash(*m_position))
  {
    // current m_sub_path was "magic empty path", become end()
    if(sub_path_size == 0)
    {
      ++m_position;
      return *this;
    }

    // current m_sub_path was root-directory, advance to relative-path
    m_position += static_cast<ptrdiff_t>(sub_path_size);
  }

  if(m_position == total_path_text.cend())
  {
    m_sub_path.clear();
    return *this;
  }

  // at this points, the next m_sub_path is a standard filename from relative_path(), and m_position
  // points at the preferred-separator or fallback-separator after the previous m_sub_path

  // advance to the start of the following path m_sub_path
  while(is_slash(*m_position))
  {
    // "magic" empty m_sub_path selected
    ++m_position;

    if(m_position == total_path_text.cend())
    {
      --m_position;
      m_sub_path.clear();
      return *this;
    }
  }

  m_sub_path.assign(unwrapped(m_position), rsl::find_if(unwrapped(m_position), end, is_slash));
  return *this;
}

rsl::PathIterator rsl::PathIterator::operator++(int)
{
  PathIterator tmp = *this;
  operator++();
  return tmp;
}

rsl::PathIterator& rsl::PathIterator::operator--()
{
  const auto& total_path_text       = m_total_path->as_string();
  const auto first                  = total_path_text.data();
  const auto last                   = first + total_path_text.size();
  const auto root_name_end_ptr      = find_root_name_end(first, last);
  const auto root_directory_end_ptr = rsl::find_if_not(root_name_end_ptr, last, is_slash);

  // current m_sub_path is the first of relative-path, and the prev m_sub_path is root-directory
  if(root_name_end_ptr != root_directory_end_ptr && unwrapped(m_position) == root_directory_end_ptr)
  {
    seek_wrapped(m_position, root_name_end_ptr);
    m_sub_path.assign(root_name_end_ptr, static_cast<card32>(root_directory_end_ptr - root_name_end_ptr));
    return *this;
  }

  // current m_sub_path is root-directory or , if that doesn't exist, first
  // m_sub_path of relative-apth prev m_sub_path therefore is root-name
  if(first != root_name_end_ptr && unwrapped(m_position) == root_name_end_ptr)
  {
    seek_wrapped(m_position, first);
    m_sub_path.assign(first, static_cast<card32>(root_name_end_ptr - first));
    return *this;
  }

  // from here, the result will be somewhere in relative-path

  // target is "magic empty path"
  if(unwrapped(m_position) == last && is_slash(m_position[-1]))
  {
    --m_position;
    m_sub_path.clear();
    return *this;
  }

  while(root_directory_end_ptr != unwrapped(m_position) && is_slash(m_position[-1]))
  {
    --m_position;
  }

  const auto new_end = m_position;
  while(root_directory_end_ptr != unwrapped(m_position) && !is_slash(m_position[-1]))
  {
    --m_position;
  }

  m_sub_path.assign(m_position, new_end);
  return *this;
}

rsl::PathIterator rsl::PathIterator::operator--(int)
{
  PathIterator tmp = *this;
  operator--();
  return tmp;
}

bool rsl::PathIterator::operator==(const PathIterator& rhs) const
{
  return m_position == rhs.m_position;
}
bool rsl::PathIterator::operator!=(const PathIterator& rhs) const
{
  return m_position != rhs.m_position;
}

bool rsl::PathIterator::points_to_begin() const
{
  return m_total_path->as_string().data() == unwrapped(m_position);
}
const char8* rsl::PathIterator::unwrapped(BaseIterator position) const
{
  return iterator_to_pointer(position);
}
void rsl::PathIterator::seek_wrapped(BaseIterator it, const char* next)
{
  it += (card32)(next - unwrapped(it));
}