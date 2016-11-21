/**
 * @file io.hpp
 * @brief header of qc::io methods
 */

#pragma once

#include "io/qo.hpp"
#include "io/blif.hpp"
#include "io/esop.hpp"

namespace qc {
namespace io {
auto input(Circuit& circuit, std::string const& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void;
auto output(Circuit const& circuit, std::string const& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void;
auto open(std::string const& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> Circuit;
auto convert(std::string const& input_filename,
             std::string const& output_filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void;
}
}

#include "io/io_impl.hpp"
