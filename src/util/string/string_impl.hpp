#pragma once

namespace qc {
namespace util {
namespace string {
inline auto getExtension(const std::string& filename) -> std::string {
  return std::move(std::get<1>(string::splitext(filename)));
}

inline auto addExtension(const std::string& filename,
                         const std::string& extension) -> std::string {
  if(extension == string::getExtension(filename)) return filename;
  return std::move(filename + "." + extension);
}

inline auto excludeExtension(const std::string& filename) -> std::string {
  return std::move(std::get<0>(string::splitext(filename)));
}
}
}
}
