#pragma once

namespace qc {
namespace util {
namespace string {
template <class CharT>
constexpr auto CaseInsensitiveCharCompare<CharT>::operator()(CharT lhs,
                                                             CharT rhs) const
  -> bool {
  return (lhs < 'a' ? lhs + 0x20 : lhs) == (rhs < 'a' ? rhs + 0x20 : rhs);
}

template <class CharT, class Compare>
constexpr BasicString<CharT, Compare>::BasicString(CharT const* const str)
  : str_(str) {}

template <class CharT, class Compare>
constexpr BasicString<CharT, Compare>::BasicString(std::string const& str)
  : str_(str.c_str()) {}

template <class CharT, class Compare>
constexpr BasicString<CharT, Compare>::BasicString(BasicString const& other)
  : str_(other.str_) {}

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
constexpr auto BasicString<CharT, Compare>::operator!=(BasicString const& other)
  const -> bool {
  return !(*this == other);
}

template <class CharT, class Compare>
constexpr BasicString<CharT, Compare>::operator char const* const() const {
  return str_;
}
}
}
}
