/**
 * @file io.hpp
 * @brief header of qc::io methods
 */

#pragma once

#include "qo.hpp"
#include "esop.hpp"

namespace qc {
namespace io {
auto input(Circuit& circuit, const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void;
auto output(Circuit& circuit, const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> void;
auto open(const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> Circuit;
}
}

#include "io_impl.hpp"
