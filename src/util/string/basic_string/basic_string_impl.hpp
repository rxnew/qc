#pragma once

namespace qc {
namespace util {
namespace string {
template <class CharT>
constexpr auto to_lower(CharT c) -> CharT;
template <class CharT>
constexpr auto to_upper(CharT c) -> CharT;

template <class CharT, class Compare>
constexpr BasicString<CharT, Compare>::BasicString(CharT const* const str)
  : str_(str), size_(0) {
  _set_size();
}

template <class CharT, class Compare>
constexpr
BasicString<CharT, Compare>::BasicString(std::basic_string<CharT> const& str)
  : str_(str.c_str()), size_(str.size()) {}

template <class CharT, class Compare>
constexpr BasicString<CharT, Compare>::BasicString(BasicString const& other)
  : str_(other.str_), size_(other.size_) {}

template <class CharT, class Compare>
template <class CharU, class CompareU>
constexpr BasicString<CharT, Compare>::BasicString
(BasicString<CharU, CompareU> const& other)
  : str_(other.str_), size_(other.size()) {}

template <class CharT, class Compare>
constexpr auto BasicString<CharT, Compare>::operator==(BasicString const& other)
  const -> bool {
  char const* p = str_;
  char const* q = other.str_;
  while(*p != '\0' && *q != '\0') {
    if(!Compare()(*p++, *q++)) return false;
  }
  return *p == *q;
}

template <class CharT, class Compare>
constexpr auto BasicString<CharT, Compare>::operator==(CharT const* const& other)
  const -> bool {
  char const* p = str_;
  char const* q = other;
  while(*p != '\0' && *q != '\0') {
    if(!Compare()(*p++, *q++)) return false;
  }
  return *p == *q;
}

template <class CharT, class Compare>
constexpr
auto BasicString<CharT, Compare>::operator==(std::basic_string<CharT>& other)
  const -> bool {
  if(size() != other.size()) return false;
  for(auto i = 0u; i < size(); ++i) {
    if(!Compare()(*this[i], other[i])) return false;
  }
  return true;
}

template <class CharT, class Compare>
constexpr auto BasicString<CharT, Compare>::operator!=(BasicString const& other)
  const -> bool {
  return !(*this == other);
}

template <class CharT, class Compare>
constexpr auto BasicString<CharT, Compare>::operator!=(CharT const* const& other)
  const -> bool {
  return !(*this == other);
}

template <class CharT, class Compare>
constexpr
auto BasicString<CharT, Compare>::operator!=(std::basic_string<CharT>& other)
  const -> bool {
  return !(*this == other);
}

template <class CharT, class Compare>
constexpr auto BasicString<CharT, Compare>::operator[](size_type pos) const
  -> CharT const* const {
  assert(pos < size());
  return str_ + pos;
}

//template <class CharT, class Compare>
//constexpr BasicString<CharT, Compare>::operator char const* const() const {
//  return str_;
//}

template <class CharT, class Compare>
BasicString<CharT, Compare>::operator std::basic_string<CharT>() const {
  return std::basic_string<CharT>(str_);
}

template <class CharT, class Compare>
inline constexpr auto BasicString<CharT, Compare>::size() const -> size_type {
  return size_;
}

template <class CharT, class Compare>
constexpr auto BasicString<CharT, Compare>::_set_size() -> void {
  while(*(str_ + size_) != '\0') ++size_;
}

template <class CharT>
auto operator<<(std::ostream& os, BasicString<CharT> const& obj)
  -> std::ostream& {
  return os << obj.str_;
}

template <class CharT>
constexpr auto CaseInsensitiveCharCompare<CharT>::operator()
  (CharT lhs, CharT rhs) const -> bool {
  return to_lower(lhs) == to_lower(rhs);
}
}
}
}
