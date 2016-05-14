/**
 * @file gate.hpp
 * @brief header of Gate class
 */

#pragma once

#include <set>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>

#include "bit/hash.hpp"
#include "util/container.hpp"
#include "util/string.hpp"
#include "util/matrix.hpp"

namespace qc {
class Gate;

using BitList = std::unordered_set<Bitno>;
using CbitList = std::unordered_set<Cbit>;
using TbitList = std::unordered_set<Tbit>;
using GatePtr = std::unique_ptr<Gate>;
using GateList = std::list<GatePtr>;
using IterGateList = GateList::iterator;
using CIterGateList = GateList::const_iterator;

using util::matrix::Complex;
using util::matrix::Matrix;
using util::matrix::Vector;
using util::matrix::operator"" _i;

/**
 * @brief quantum gate class
 * @note this class is abstract
 */
class Gate {
 private:
  class MatrixMap;

  using ui = unsigned int;

  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 protected:
  CbitList cbits_;
  TbitList tbits_;

  explicit Gate(const Tbit& tbit);
  Gate(const Tbit& tbit1, const Tbit& tbit2);
  Gate(const Cbit& cbit, const Tbit& tbit);
  Gate(const Cbit& cbit, const TbitList& tbits);
  Gate(const Cbit& cbit, TbitList&& tbits);
  Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  Gate(const CbitList& cbits, const Tbit& tbit);
  Gate(CbitList&& cbits, const Tbit& tbit);
  Gate(const CbitList& cbits, const TbitList& tbits);
  Gate(CbitList&& cbits, TbitList&& tbits);
  Gate(const Gate&) = default;
  Gate(Gate&&) noexcept = default;

  auto _computeMatrix(const MatrixMap& matrix_map) const -> Matrix;
  auto _simulate(const Vector& input, const MatrixMap& matrix_map) const
    -> Vector;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  virtual ~Gate() = default;

  auto operator=(const Gate&) -> Gate& = default;
  auto operator=(Gate&&) -> Gate& = default;
  auto operator==(const Gate& other) const -> bool;
  auto operator!=(const Gate& other) const -> bool;

  virtual auto clone() const -> GatePtr = 0;
  virtual auto getTypeName() const -> const std::string& = 0;
  auto getCbitList() const -> const CbitList&;
  auto getTbitList() const -> const TbitList&;
  auto setCbits(const CbitList& cbits) -> void;
  auto setCbits(CbitList&& cbits) -> void;
  auto setTbits(const TbitList& tbits) -> void;
  auto setTbits(TbitList&& tbits) -> void;
  auto isIncluded(Bitno bit) const -> bool;
  auto isIncludedInCbitList(Bitno bit) const -> bool;
  auto isIncludedInTbitList(Bitno bit) const -> bool;
  auto collectUsedBits() const -> BitList;
  virtual auto getTargetMatrix() const -> const Matrix& = 0;
  virtual auto computeMatrix(const std::set<Bitno>& bits) const -> Matrix;
  auto computeMatrix(const BitList& bits) const -> Matrix;
  auto computeMatrix() const -> Matrix;
  auto simulate(const Vector& input, const std::set<Bitno>& bits) const
    -> Vector;
  auto simulate(const Vector& input, const BitList& bits) const -> Vector;
  auto simulate(const Vector& input) const -> Vector;
  auto isControlled() const -> bool;
  auto isSingleControlled() const -> bool;
  auto isMultiControlled() const -> bool;
  auto isSingleTarget() const -> bool;
  auto isMultiTarget() const -> bool;
  auto isSingleQubitRotation() const -> bool;
  auto isAllPositive() const -> bool;
  auto print(std::ostream& os = std::cout) const -> void;
};

class Gate::MatrixMap {
 private:
  const Gate& gate_;
  ui active_polarity_pattern_;
  ui polarity_pattern_mask_;

  auto _init() -> void;
  auto _setActivePolarityPattern() -> void;
  auto _updateActive(bool is_cbit, Bitno bit) -> void;
  auto _updateInactive(bool is_cbit) -> void;
  auto _mask(ui polarity_pattern) const -> bool;
  auto _isActive() const -> bool;

 public:
  // matrix of active input pattern of each target
  std::unordered_map<Bitno, Matrix> active_;
  // matrix of inactive each input pattern
  std::unordered_map<ui, Matrix> inactive_;

  MatrixMap(const Gate& gate, const std::set<Bitno>& bits);
};
}

#include "gate/gate_impl.hpp"
