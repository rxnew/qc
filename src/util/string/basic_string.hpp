#pragma once

#include "../string.hpp"

namespace qc {
namespace util {
namespace string {
template <class CharT, class Compare = std::equal_to<CharT>>
class BasicString {
 public:
  constexpr BasicString(CharT const* const str);
  constexpr BasicString(std::string const& str);
  constexpr BasicString(BasicString const& other);

  constexpr auto operator==(BasicString const& other) const -> bool;
  constexpr auto operator!=(BasicString const& other) const -> bool;

  constexpr operator char const* const() const;

 private:
  CharT const* const str_;
};

using String = BasicString<char>;
using CaseInsensitiveString =
  BasicString<char, CaseInsensitiveCharCompare<char>>;
}
}
}

#include "basic_string/basic_string_impl.hpp"