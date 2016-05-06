/**
 * @file circuit.hpp
 * @brief header of Circuit class
 */

#pragma once

#include <list>

#include "gate.hpp"

namespace qc {
class Circuit;

using GateList = std::list<GatePtr>;
using IterGateList = GateList::iterator;
using CIterGateList = GateList::const_iterator;

/**
 * @brief quantum circuit class
 */
class Circuit {
 private:
  GateList gates_;

 public:
  Circuit();
  Circuit(const Circuit& other);
  Circuit(Circuit&& other) noexcept;
  ~Circuit();
  auto operator=(const Circuit& other) -> Circuit&;
  auto operator=(Circuit&& other) -> Circuit&;
  auto operator==(const Circuit& other) const -> bool;
  auto operator!=(const Circuit& other) const -> bool;
  auto getGateList() const -> const GateList&;
  auto getGateListBegin() -> IterGateList;
  auto getGateListEnd() -> IterGateList;
  auto addGate(GatePtr&& gate) -> void;
  auto addGate(GatePtr& gate) -> void;
  auto addGate(Gate*&& gate) -> void;
  auto insertGate(CIterGateList pos, GatePtr&& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, GatePtr& gate) -> IterGateList;
  auto insertGate(CIterGateList pos, Gate*&& gate) -> IterGateList;
  auto eraseGate(CIterGateList pos) -> IterGateList;
  auto eraseGate(IterGateList pos, GatePtr& gate) -> IterGateList;
  auto eraseGate(CIterGateList first, CIterGateList last) -> IterGateList;
  auto swapGate(IterGateList pos1, IterGateList pos2) -> void;
  auto append(const Circuit& circ) -> void;
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
