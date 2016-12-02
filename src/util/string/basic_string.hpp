#pragma once

#include <string>

namespace qc {
namespace util {
namespace string {
template <class CharT, class Compare = std::equal_to<CharT>>
class BasicString {
 public:
  using size_type = std::size_t;

  constexpr BasicString(CharT const* const str);
  constexpr BasicString(std::basic_string<CharT> const& str);
  constexpr BasicString(BasicString const& other);
  template <class CharU, class CompareU>
  constexpr BasicString(BasicString<CharU, CompareU> const& other);

  constexpr auto operator==(BasicString const& other) const -> bool;
  constexpr auto operator==(CharT const* const& other) const -> bool;
  constexpr auto operator==(std::basic_string<CharT>& other) const -> bool;
  constexpr auto operator!=(BasicString const& other) const -> bool;
  constexpr auto operator!=(CharT const* const& other) const -> bool;
  constexpr auto operator!=(std::basic_string<CharT>& other) const -> bool;
  constexpr auto operator[](size_type pos) const -> CharT const* const;

  //constexpr operator char const* const() const;
  operator std::basic_string<CharT>() const;

  constexpr auto size() const -> size_type;

 private:
  constexpr auto _set_size() -> void;

  CharT const* const str_;
  size_type size_;

  template <class CharU>
  friend auto operator<<(std::ostream& os, BasicString<CharU> const& obj)
    -> std::ostream&;

  template <class CharU, class CompareU>
  friend class BasicString;
};

template <class CharT>
auto operator<<(std::ostream& os, BasicString<CharT> const& obj)
  -> std::ostream&;

template <class CharT>
struct CaseInsensitiveCharCompare {
  constexpr auto operator()(CharT lhs, CharT rhs) const -> bool;
};

using String = BasicString<char>;
using CaseInsensitiveString =
  BasicString<char, CaseInsensitiveCharCompare<char>>;
}
}
}

#include "basic_string/basic_string_impl.hpp"
