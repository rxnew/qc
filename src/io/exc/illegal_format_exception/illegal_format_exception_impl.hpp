/**
 * @file illegal_format_exception_impl.hpp
 * @brief implementation header of IllegalFormatException class
 */

#pragma once

namespace qc {
namespace io {
namespace exc {
template <class... Args>
inline IllegalFormatException::IllegalFormatException(Args... args)
  : Super(std::forward<Args>(args)...) {
}
}
}
}
