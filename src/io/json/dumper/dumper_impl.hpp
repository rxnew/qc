/**
 * @file dumper_impl.hpp
 * @brief implementation header of Json::Dumper class
 */

#pragma once

namespace qc {
namespace io {
inline Json::Dumper::Dumper(Circuit const& circuit, std::ostream& os)
  : circuit_(circuit), os_(os) {}
}
}
