/**
 * @file io_impl.hpp
 * @brief implementation header of qc::io methods
 */

#pragma once

namespace qc {
namespace io {
inline auto convert(const std::string& input_filename,
                    const std::string& output_filename)
  throw(exc::IllegalFormatException, std::ios_base::failure)-> void {
  io::output(io::open(input_filename), output_filename);
}
}
}
