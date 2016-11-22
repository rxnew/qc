/**
 * @file circuit.hpp
 * @brief header of Circuit class
 */

#pragma once

#include "forward_declarations.hpp"
#include "gate/gates_wrapper.hpp"
#include "util/tmpl.hpp"

namespace qc {
/**
 * @brief quantum circuit class
 */
class Circuit : public GatesWrapper {
 public:
  Circuit() = default;
  explicit Circuit(std::string const& description);
  explicit Circuit(std::string&& description);
  template <class GatesT, class StringT = char const* const>
  explicit Circuit(GatesT&& gates, StringT&& description = "");
  Circuit(Circuit const& other) = default;
  Circuit(Circuit&&) noexcept = default;

  ~Circuit() noexcept = default;

  auto operator=(Circuit const& other) -> Circuit& = default;
  auto operator=(Circuit&&) noexcept -> Circuit& = default;
  auto operator==(Circuit const& other) const -> bool;
  auto operator!=(Circuit const& other) const -> bool;

  auto get_description() const -> std::string const&;
  template <class StringT>
  auto set_description(StringT&& description) -> void;

 private:
  std::string description_;
};
}

#include "circuit/circuit_impl.hpp"
