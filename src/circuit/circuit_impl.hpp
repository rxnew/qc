/**
 * @file circuit_impl.hpp
 * @brief implementation header of Circuit class
 */

#pragma once

namespace qc {
inline Circuit::Circuit(std::string const& description)
  : description_(description) {}

inline Circuit::Circuit(std::string&& description)
  : description_(std::move(description)) {}

template <class GatesT, class StringT>
inline Circuit::Circuit(GatesT&& gates, StringT&& description)
  : GatesWrapper(std::forward<GatesT>(gates)),
    description_(std::forward<StringT>(description)) {}

inline auto Circuit::operator==(Circuit const& other) const -> bool {
  return gates_ == other.gates_;
}

inline auto Circuit::operator!=(Circuit const& other) const -> bool {
  return !(*this == other);
}

inline auto Circuit::get_description() const -> std::string const& {
  return description_;
}

template <class StringT>
inline auto Circuit::set_description(StringT&& description) -> void {
  description_ = std::forward<StringT>(description);
}
}
