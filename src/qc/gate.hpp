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

#include "../util/container.hpp"
#include "../util/string.hpp"
#include "../util/matrix.hpp"

#include "bit.hpp"

namespace qc {
class Gate;

using BitList = std::unordered_set<Bitno>;
using CbitList = std::unordered_set<Cbit>;
using TbitList = std::unordered_set<Tbit>;
using GatePtr = std::unique_ptr<Gate>;

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
  Gate(const Gate& other);
  Gate(Gate&&) noexcept = default;

  auto _computeMatrix(const MatrixMap& matrix_map) const -> Matrix;
  auto _simulate(const Vector& input, const MatrixMap& matrix_map) const
    -> Vector;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  virtual ~Gate();
  auto operator=(const Gate& other) -> Gate&;
  auto operator=(Gate&& other) -> Gate&;
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
  auto isAllPositive() const -> bool;
  auto print(std::ostream& os = std::cout) const -> void;

 private:
  class MatrixMap {
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
};

/**
 * @brief I gate class
 */
class I : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  I(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief V gate class
 */
class V : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  V(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief V+ gate class
 */
class VPlus : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  VPlus(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Hadamard gate class
 */
class Hadamard : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Hadamard(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Not gate class
 */
class Not : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Not(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Z gate class
 */
class Z : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Z(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief Swap gate class
 */
class Swap : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  Swap(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
  auto computeMatrix(const std::set<Bitno>& bits) const -> Matrix;
  auto decompose() const -> std::list<GatePtr>;
};

/**
 * @brief T gate class
 */
class T : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  T(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief S gate class
 */
class S : public Gate {
 private:
  static auto _createTargetMatrixList() -> std::initializer_list<Complex>;

 public:
  static const std::string TYPE_NAME;
  static const Matrix TARGET_MATRIX;

  template <class... Args>
  S(Args&&... args);
  auto clone() const -> GatePtr;
  auto getTypeName() const -> const std::string&;
  auto getTargetMatrix() const -> const Matrix&;
};

/**
 * @brief GateBuilder class
 */
struct GateBuilder {
  template <class... Args>
  static auto create(const std::string& str, Args&&... args) -> GatePtr;
};
}

#include "gate_impl.hpp"
