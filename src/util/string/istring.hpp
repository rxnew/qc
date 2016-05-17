#pragma once

#include "../string.hpp"

namespace qc {
namespace util {
namespace string {
class istring : public std::string {
 private:
  using Super = std::string;

 public:
  template <class... Args>
  istring(Args&&... args);

  template <class... Args>
  auto operator=(Args&&... args) -> istring&;
  auto operator==(const istring& other) const -> bool;
  auto operator!=(const istring& other) const -> bool;
  auto operator<(const istring& other) const -> bool;
  auto operator>(const istring& other) const -> bool;

  auto to_string() const -> Super;
  auto case_insensitive() const -> Super;
};
}
}
}

#include "istring/istring_impl.hpp"
