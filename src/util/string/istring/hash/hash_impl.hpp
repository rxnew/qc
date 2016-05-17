#pragma once

namespace std {
inline auto hash<qc::util::string::istring>::operator()(
    const istring& obj) const -> size_t {
  auto result = hash<string>()(obj.case_insensitive());
  return result;
}
}
