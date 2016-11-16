#pragma once

namespace std {
inline auto hash<qc::util::string::istring>::operator()(istring const& obj)
  const -> size_t {
  return hash<string>()(obj.case_insensitive());
}
}
