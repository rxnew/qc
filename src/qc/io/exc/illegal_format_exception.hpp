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
  template <class T>
  explicit IllegalFormatException(T arg);
};

template <class T>
inline IllegalFormatException::IllegalFormatException(T arg) : Super(arg) {
}
}
}
}
