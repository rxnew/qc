/**
 * @file circuit.hpp
 * @brief header of Circuit class
 */

#pragma once

#include <list>

#include "gate.hpp"

namespace qc {
class Circuit;

/**
 * @brief quantum circuit class
 */
class Circuit {
 private:
  GateList gates_;
  std::string description_;

 public:
  Circuit() = default;
  explicit Circuit(const std::string& description);
  explicit Circuit(std::string&& description);
  template <class stringT = std::string>
  Circuit(GateList&& gates, stringT&& description = "");
  template <class GateListT, class stringT = std::string>
  Circuit(const GateListT& gates, stringT&& description = "");
  Circuit(const Circuit& other);
  Circuit(Circuit&&) noexcept = default;
  ~Circuit() = default;

  auto operator=(const Circuit& other) -> Circuit&;
  auto operator=(Circuit&&) -> Circuit& = default;
  auto operator==(const Circuit& other) const -> bool;
  auto operator!=(const Circuit& other) const -> bool;

  auto getDescription() const -> const std::string&;
  template <class stringT>
  auto setDescription(stringT&& description) -> void;
  auto getGateList() -> GateList&;
  auto getGateList() const -> const GateList&;
  auto getGateListBegin() -> IterGateList;
  auto getGateListEnd() -> IterGateList;
  auto addGate(GatePtr&& gate) -> void;
  auto addGate(GatePtr& gate) -> void;
  auto addGate(Gate*&& gate) -> void;
  auto addGate(GateList&& gates) -> void;
  template <class GateListT>
  auto addGate(const GateListT& gates) -> void;
  auto insertGate(CIterGateList pos, GatePtr&& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, GatePtr& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, Gate*&& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, GateList&& gates) -> IterGateList;
  template <class GateListT>
  auto insertGate(CIterGateList pos, const GateListT& gates) -> IterGateList;
  auto eraseGate(CIterGateList pos) -> IterGateList;
  auto eraseGate(IterGateList pos, GatePtr& gate) -> IterGateList;
  auto eraseGate(CIterGateList first, CIterGateList last) -> IterGateList;
  auto swapGate(IterGateList pos1, IterGateList pos2) -> void;
  auto append(const Circuit& circuit) -> void;
  auto append(Circuit&& circuit) -> void;
  auto clear() -> void;
  auto getGateCount() const -> size_t;
  auto collectUsedBits() const -> BitList;
  auto computeMatrix() const -> Matrix;
  auto computeZeroVectorMap() const -> std::map<Bitno, Vector>;
  auto simulate() const -> Vector;
  auto simulate(const Vector& input) const -> Vector;
  auto simulate(const Vector& input, const Matrix& matrix) const -> Vector;
  auto simulate(std::vector<Complex>&& input) const -> Vector;
  auto simulate(const std::map<Bitno, Vector>& input) const -> Vector;
  auto print(std::ostream& os = std::cout) const -> void;
};
}

#include "circuit/circuit_impl.hpp"
