/**
 * @file io.hpp
 * @brief header of qc::io methods
 */

#pragma once

#include "io/qo.hpp"
#include "io/esop.hpp"

namespace qc {
namespace io {
auto input(Circuit& circuit, const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void;
auto output(const Circuit& circuit, const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void;
auto open(const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> Circuit;
auto convert(const std::string& input_filename,
             const std::string& output_filename)
  throw(exc::IllegalFormatException, std::ios_base::failure)-> void;
}
}

#include "io/io_impl.hpp"
