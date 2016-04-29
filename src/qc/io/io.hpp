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
auto open(const std::string& filename)
  throw(exc::IllegalFormatException, std::ios_base::failure) -> Circuit;
auto getExtension(const std::string& filename) -> std::string;
}
}

#include "io_impl.hpp"
