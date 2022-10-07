// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: filepath.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/algorithm.h"
#include "rex_std_extra/bonus/string/string_utils.h"
#include "rex_std_extra/filesystem.h"
#include "rex_std_extra/iterator.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

#include <list>

REX_RSL_BEGIN_NAMESPACE

// this is for the windows version
// an absolute filepath on windows with a root name is structured like this
// C:/my/path/file.txt
// C: is the root name
// / is the root directory
// C:/ is the root path
bool has_drive_prefix(const char8* path)
{
  unsigned short value = 0;
  memcpy(&value, path, sizeof(value));
  value &= 0xFFFF'FFDFu; // transform lowercase drive letters into uppercase ones
  value -= (static_cast<unsigned short>(':') << (sizeof(char) * CHAR_BIT)) | 'A';
  return value < 26;
}

// FUNCTION TEMPLATE unaligned_load
// load a T from ptr
template <typename T>
REX_NO_DISCARD T unaligned_load(const void* ptr)
{
  static_assert(rsl::is_trivial_v<T>, "Unaligned loads require trivial types");
  T tmp;
  memcpy(&tmp, ptr, sizeof(tmp));
  return tmp;
}

REX_NO_DISCARD inline bool is_drive_prefix(const char* const first)
{
  // test if first points to a prefix of the form X:
  // pre: first points to at least 2 char instances
  // pre: Little endian
  auto value = unaligned_load<unsigned short>(first);
  value &= 0xFFFF'FFDFu; // transform lowercase drive letters into uppercase ones
  value -= (static_cast<unsigned short>(':') << (sizeof(char) * CHAR_BIT)) | 'A';
  return value < 26;
}

REX_NO_DISCARD bool has_drive_letter_prefix(const char8* first, const char8* last)
{
  return last - first >= 2 && is_drive_prefix(first);
}

bool is_slash(const char ch)
{
  return ch == '\\' || ch == '/';
}

const char* find_root_name_end(const char8* first, const char8* last)
{
  // attempt to parse [first, last) as a path and return the end of root-name if it exists; otherwise, first

  // This is the place in the generic grammar where library implementations have the most freedom.
  // Below are example Windows paths, and what we've decided to do with them:
  // * X:DriveRelative, X:\DosAbsolute
  //   We parse X: as root-name, if and only if \ is present we consider that root-directory
  // * \RootRelative
  //   We parse no root-name, and \ as root-directory
  // * \\server\share
  //   We parse \\server as root-name, \ as root-directory, and share as the first element in relative-path.
  //   Technically, Windows considers all of \\server\share the logical "root", but for purposes
  //   of decomposition we want those split, so that path(R"(\\server\share)").replace_filename("other_share")
  //   is \\server\other_share
  // * \\?\device
  // * \??\device
  // * \\.\device
  //   CreateFile appears to treat these as the same thing; we will set the first three characters as root-name
  //   and the first \ as root-directory. Support for these prefixes varies by particular Windows version, but
  //   for the purposes of path decomposition we don't need to worry about that.
  // * \\?\UNC\server\share
  //   MSDN explicitly documents the \\?\UNC syntax as a special case. What actually happens is that the device
  //   Mup, or "Multiple UNC provider", owns the path \\?\UNC in the NT namespace, and is responsible for the
  //   network file access. When the user says \\server\share, CreateFile translates that into
  //   \\?\UNC\server\share to get the remote server access behavior. Because NT treats this like any other
  //   device, we have chosen to treat this as the \\?\ case above.
  if(last - first < 2)
  {
    return first;
  }

  if(has_drive_letter_prefix(first, last))
  { // check for X: first because it's the most common root-name
    return first + 2;
  }

  if(!rsl::is_slash(first[0]))
  { // all the other root-names start with a slash; check that first because
    // we expect paths without a leading slash to be very common
    return first;
  }

  // $ means anything other than a slash, including potentially the end of the input
  if(last - first >= 4 && rsl::is_slash(first[3]) && (last - first == 4 || !rsl::is_slash(first[4])) // \xx\$
     && ((rsl::is_slash(first[1]) && (first[2] == '?' || first[2] == '.'))                           // \\?\$ or \\.\$
         || (first[1] == '?' && first[2] == '?')))
  { // \??\$
    return first + 3;
  }

  if(last - first >= 3 && rsl::is_slash(first[1]) && !rsl::is_slash(first[2]))
  { // \\server
    return rsl::find_if(first + 3, last, rsl::is_slash);
  }

  // no match
  return first;
}

REX_RSL_END_NAMESPACE

rsl::Path::Path() = default;
rsl::Path::Path(const string_view_type view)
    : m_text(view)
{
}
rsl::Path::Path(const String& str)
    : m_text(str)
{
}

rsl::Path& rsl::Path::operator=(const Path& path)
{
  m_text = path.m_text;
  return *this;
}
rsl::Path& rsl::Path::operator=(const string_view_type view)
{
  m_text = view;
  return *this;
}
rsl::Path& rsl::Path::operator=(const String& str)
{
  m_text = str;
  return *this;
}

void rsl::Path::assign(const char8* first, const char8* last)
{
  m_text.assign(first, last);
}
void rsl::Path::assign(const char8* first, card32 count)
{
  m_text.assign(first, count);
}

rsl::Path rsl::Path::operator/(string_view_type rhs) const
{
  rsl::Path tmp(m_text.to_view());
  tmp /= rhs;
  return tmp;
}
rsl::Path& rsl::Path::operator/=(string_view_type rhs)
{
  Path other(rhs);

  if(other.is_absolute())
  {
    return operator=(other);
  }

  const char8* my_first            = m_text.data();
  const char8* my_last             = my_first + m_text.size();
  const char8* other_first         = other.m_text.data();
  const char8* other_last          = other_first + other.m_text.size();
  const char8* my_root_name_end    = find_root_name_end(my_first, my_last);
  const char8* other_root_name_end = find_root_name_end(other_first, other_last);

  if(other_first != other_root_name_end && internal::are_ranges_equal(my_first, other_first, other_root_name_end, rsl::equal_to<>()))
  {
    return operator=(other);
  }

  if(other.has_root_directory())
  {
    m_text.erase(static_cast<card32>(my_root_name_end - my_first));
  }
  else
  {
    if(my_root_name_end == my_last)
    {
      if(my_root_name_end - my_first >= 3)
      {
        m_text.push_back(s_PreferredSeperator);
      }
    }
    else
    {
      if(!is_slash(my_last[-1]))
      {
        m_text.push_back(s_PreferredSeperator);
      }
    }
  }

  m_text.append(other_root_name_end, static_cast<card32>(other_last - other_root_name_end));
  return *this;
}

rsl::Path rsl::Path::operator+(const string_view_type view) const
{
  Path tmp = *this;
  tmp.m_text + view;
  return tmp;
}
rsl::Path rsl::Path::operator+(const value_type c) const
{
  Path tmp = *this;
  tmp.m_text.push_back(c);
  return tmp;
}

rsl::Path& rsl::Path::operator+=(const string_view_type view)
{
  m_text += view;
  return *this;
}
rsl::Path& rsl::Path::operator+=(const value_type c)
{
  m_text += c;
  return *this;
}

rsl::Path::operator rsl::Path::string_type() const
{
  return m_text;
}
rsl::Path::operator rsl::Path::string_view_type() const
{
  return m_text.to_view();
}

void rsl::Path::clear()
{
  m_text.clear();
}
const rsl::Path::value_type* rsl::Path::data() const
{
  return m_text.data();
}

int32 rsl::Path::compare(const string_type& other) const
{
  return compare(other.to_view());
}
int32 rsl::Path::compare(const Path& other) const
{
  return compare(string_view_type(other));
}
int32 rsl::Path::compare(string_view_type other) const
{
  return rsl::string_equals_case_insensitive(m_text.data(), m_text.size(), other.data(), other.length());
}
int32 rsl::Path::compare(const value_type* other) const
{
  return compare(string_view_type(other));
}

rsl::Path rsl::Path::root_name() const
{
  if(has_drive_prefix(m_text.data()))
  {
    return Path(m_text.substr(0, 2)); // only get first 2 chars
  }
  return "";
}
rsl::Path rsl::Path::root_directory() const
{
  if(has_drive_prefix(m_text.data()))
  {
    return Path(m_text.substr(2, 1)); // get the first char after drive prefix
  }
  return "";
}
rsl::Path rsl::Path::root_path() const
{
  if(has_drive_prefix(m_text.data()))
  {
    return Path(m_text.substr(0, 3)); // get both drive prefix and the char after
  }
  return "";
}
rsl::Path rsl::Path::relative_path() const
{
  if(has_drive_prefix(m_text.data()))
  {
    return Path(m_text.substr(3)); // get the path relative to the root path
  }
  return "";
}
rsl::Path rsl::Path::parent_path() const
{
  card32 pos = m_text.find_last_not_of('/');
  return Path(m_text.substr(0, pos));
}
rsl::Path rsl::Path::filename() const
{
  card32 pos = m_text.find_last_not_of('/');
  return Path(m_text.substr(pos));
}
rsl::Path rsl::Path::stem() const
{
  card32 filename_pos  = m_text.find_last_of('/');
  card32 extension_pos = m_text.find_last_of('.', filename_pos);
  return Path(m_text.substr(filename_pos, extension_pos - filename_pos));
}
rsl::Path rsl::Path::extension() const
{
  card32 extension_pos = m_text.find_last_of('.');
  return Path(m_text.substr(extension_pos));
}

bool rsl::Path::empty() const
{
  return m_text.empty();
}
bool rsl::Path::has_root_name() const
{
  return !root_name().empty();
}
bool rsl::Path::has_root_directory() const
{
  return !root_directory().empty();
}
bool rsl::Path::has_root_path() const
{
  return !root_path().empty();
}
bool rsl::Path::has_relative_path() const
{
  return !relative_path().empty();
}
bool rsl::Path::has_parent_path() const
{
  return !parent_path().empty();
}
bool rsl::Path::has_filename() const
{
  return !filename().empty();
}
bool rsl::Path::has_stem() const
{
  return !stem().empty();
}
bool rsl::Path::has_extension() const
{
  return !extension().empty();
}

bool rsl::Path::is_absolute() const
{
  return has_root_name() && has_relative_path();
}
bool rsl::Path::is_relative() const
{
  return !has_root_name() && has_relative_path();
}
rsl::Path rsl::Path::relative(const Path& base) const
{
  constexpr string_view_type dot     = ".";
  constexpr string_view_type dot_dot = "..";

  Path result;

  if(root_name() != base.root_name() || is_absolute() != base.is_absolute() || (!has_root_directory() && base.has_root_directory()))
  {
    return result;
  }

  const iterator this_end   = cend();
  const iterator base_begin = base.cbegin();
  const iterator base_end   = base.cend();

  auto mismatched  = rsl::mismatch(begin(), this_end, base_begin, base_end);
  iterator& iter_a = mismatched.first;
  iterator& iter_b = mismatched.second;

  if(iter_a == this_end && iter_b == base_end)
  {
    result = dot;
    return result;
  }

  { // skip root-name and root-directory elements
    ptrdiff_t dist_b = rsl::distance(base_begin, iter_b);

    const ptrdiff_t base_root_dist = static_cast<ptrdiff_t>(base.has_root_name()) + static_cast<ptrdiff_t>(base.has_root_directory());

    while(dist_b < base_root_dist)
    {
      ++iter_b;
      ++dist_b;
    }
  }

  ptrdiff_t num = 0;

  for(; iter_b != base_end; ++iter_b)
  {
    const Path& elem = *iter_b;

    // skip empty element
    if(elem.empty())
    {
      continue;
    }

    // skip filename elements that are dot
    else if(elem == dot)
    {
      continue;
    }
    else if(elem == dot_dot)
    {
      --num;
    }
    else
    {
      ++num;
    }
  }

  if(num < 0)
  {
    return result;
  }

  if(num == 0 && (iter_a == this_end || iter_a->empty()))
  {
    result = dot;
    return result;
  }

  for(; num > 0; --num)
  {
    result /= dot_dot;
  }

  for(; iter_a != this_end; ++iter_a)
  {
    result /= *iter_a;
  }

  return result;
}
rsl::Path rsl::Path::normalised() const
{
  // convert c:/some/./path/../path to c:/path
  constexpr string_view_type dot     = ".";
  constexpr string_view_type dot_dot = "..";

  // N4810 29.11.7.1 [fs.path.generic]/6:
  // Normalizatoin of a generic format pathname means:

  // 1. if the path is empty, stop.
  if(empty())
  {
    return Path();
  }

  string_type normalised = m_text;

  // 2. replace each slash character with a preferred-separator.
  rsl::replace(normalised.begin(), normalised.end(), '\\', '/');
  const auto first         = m_text.data();
  const auto last          = first + m_text.size();
  const auto root_name_end = find_root_name_end(iterator_to_pointer(normalised.begin()), iterator_to_pointer(normalised.end()));

  // 3. Replace each directory-separtor with a preferred-separator
  rsl::list<string_view_type> list;
  for(auto next = root_name_end; next != last;)
  {
    if(is_slash(*next))
    {
      if(list.empty() || !list.back().empty())
      {
        // collapse one or more slashes and preferred-separators to one empty string_view_type
        list.emplace_back();
      }

      ++next;
    }
    else
    {
      const auto filename_end = rsl::find_if(next + 1, last, is_slash);
      list.emplace_back(next, static_cast<card32>(filename_end - next));
      next = filename_end;
    }
  }

  // 4. Remove each dot filename and any immediately following directory-separator
  for(auto next = list.begin(); next != list.end();)
  {
    if(*next == dot)
    {
      next = list.erase(next); // erase dot filename
      if(next != list.end())
      {
        next = list.erase(next); // erase immediately following directory-separator
      }
    }
    else
    {
      ++next;
    }
  }

  // 5. As long as any appear, remove a non-dot-dot filename immediately followed by a
  // directory-separator and a dot-dot filename, along with any immediately following directory-separator
  for(auto next = list.begin(); next != list.end();)
  {
    auto prev = next;
    ++next; // if we aren't going to erase, keep advancing.
    // if we're going to erase, next now points past the dot-dot filename

    if(*prev == dot_dot && prev != list.begin() && --prev != list.begin() && *--prev != dot_dot)
    {
      if(next != list.end())
      {
        ++next;
      }

      list.erase(prev, next); // next remains valid
    }
  }

  // 6. if there is a root-directory, remove all dot-dot filenames
  // and any directory separators immediately following themn.

  // we have a root directory
  if(!list.empty() && list.front().empty())
  {
    for(auto next = list.begin(); next != list.end();)
    {
      if(*next == dot_dot)
      {
        next = list.erase(next); // erase dot-dot filename

        if(next != list.end())
        {
          next = list.erase(next); // erase immediately following directory-separator
        }
      }
      else
      {
        ++next;
      }
    }
  }

  // 7. if the last filename is dot-dot, remove any trailing directory-separator
  if(list.size() >= 2 && list.back().empty() && *(rsl::prev(list.end(), 2)) == dot_dot)
  {
    list.pop_back();
  }

  // Build up normalized by flattening list
  for(const auto& elem: list)
  {
    if(elem.empty())
    {
      normalised += s_PreferredSeperator;
    }
    else
    {
      normalised += elem;
    }
  }

  // 8. if the path is empty, add a dot
  if(normalised.empty())
  {
    normalised = dot;
  }

  Path result(rsl::move(normalised));
  return result;
}
void rsl::Path::normalise()
{
  *this = normalised();
}

rsl::Path::iterator rsl::Path::begin() const
{
  const auto first         = m_text.data();
  const auto last          = first + m_text.size();
  const auto root_name_end = find_root_name_end(first, last);
  const char8* first_end   = nullptr;

  // first element isn't root-name
  if(first == root_name_end)
  {
    auto root_directory_end = rsl::find_if_not(root_name_end, last, is_slash);

    // first element is first relative-path entry
    if(first == root_directory_end)
    {
      first_end = rsl::find_if(root_directory_end, last, is_slash);
    }

    // first element is root-directory
    else
    {
      first_end = root_directory_end;
    }
  }

  // first element is root-name
  else
  {
    first_end = root_name_end;
  }

  return iterator(m_text.cbegin(), StringView(first, static_cast<card32>(first_end - first)), this);
}
rsl::Path::const_iterator rsl::Path::cbegin() const
{
  return begin();
}

rsl::Path::iterator rsl::Path::end() const
{
  return iterator(m_text.cend(), this);
}
rsl::Path::const_iterator rsl::Path::cend() const
{
  return end();
}

bool rsl::Path::operator==(string_view_type rhs) const
{
  return compare(rhs) == 0;
}
bool rsl::Path::operator!=(string_view_type rhs) const
{
  return compare(rhs) != 0;
}

bool rsl::Path::operator<(const Path& rhs) const
{
  return compare(rhs) < 0;
}
bool rsl::Path::operator<=(const Path& rhs) const
{
  return compare(rhs) <= 0;
}
bool rsl::Path::operator>(const Path& rhs) const
{
  return compare(rhs) > 0;
}
bool rsl::Path::operator>=(const Path& rhs) const
{
  return compare(rhs) >= 0;
}

const rsl::Path::string_type& rsl::Path::as_string() const
{
  return m_text;
}

rsl::OStream& rsl::operator<<(OStream& os, const Path& path)
{
  os << path.as_string();
  return os;
}

card32 rsl::hash(const rsl::Path& path)
{
  return static_cast<card32>(rsl::hash<rsl::Path>()(path));
}