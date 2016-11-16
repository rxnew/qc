#pragma once

namespace qc {
namespace util {
namespace string {
template <class... Args>
istring::istring(Args&&... args) : Super(std::forward<Args>(args)...) {}

template <class... Args>
auto istring::operator=(Args&&... args) -> istring& {
  Super::operator=(std::forward<Args>(args)...);
  return *this;
}

inline auto istring::operator==(const istring& other) const -> bool {
  return equal_case_insensitive(*this, other);
}

inline auto istring::operator!=(const istring& other) const -> bool {
  return !(*this == other);
}

inline auto istring::operator<(const istring& other) const -> bool {
  return case_insensitive() < other.case_insensitive();
}

inline auto istring::operator>(const istring& other) const -> bool {
  return !(*this < other);
}

inline auto istring::to_string() const -> Super {
  return Super(c_str());
}

inline auto istring::case_insensitive() const -> Super {
  auto str = this->to_string();
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}
}
}
}
