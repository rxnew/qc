/**
 * @file tqc.hpp
 * @brief header of tqc algorithm
 */

#pragma once

#include "../forward_declarations.hpp"
#include "tqc/parallel.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <class Engine = CsvdEv1>
auto parallelize(Circuit& circuit) -> void;
}
}
}

#include "tqc/tqc_impl.hpp"
