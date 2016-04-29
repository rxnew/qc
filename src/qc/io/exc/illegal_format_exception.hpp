/**
 * @file illegal_format_exception.hpp
 * @brief header of IllegalFormatException class
 */

#pragma once

#include <stdexcept>

namespace qc {
namespace io {
namespace exc {
class IllegalFormatException : public std::runtime_error {
 private:
  using Super = std::runtime_error;

 public:
  template <class... Args>
  explicit IllegalFormatException(Args... args);
};
}
}
}

#include "illegal_format_exception_impl.hpp"
