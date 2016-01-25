/**
 * @file gate.hpp
 * @brief header of quantum gate classes
 */

#pragma once

#include <set>
#include <unordered_set>
#include <memory>
#include <algorithm>

#include "bit.hpp"

namespace qc {
class Gate;

using GatePtr = std::shared_ptr<Gate>;
using BitList = std::unordered_set<Bitno>;
using CbitList = std::unordered_set<Cbit>;
using TbitList = std::unordered_set<Tbit>;

/**
 * @brief quantum gate class
 * @note this class is abstract
 */
class Gate {
 protected:
  CbitList cbits_;
  TbitList tbits_;

  Gate(const Tbit& tbit);
  Gate(const Tbit& tbit1, const Tbit& tbit2);
  Gate(const Cbit& cbit, const Tbit& tbit);
  Gate(const Cbit& cbit, const TbitList& tbits);
  Gate(const Cbit& cbit, const std::initializer_list<Tbit>& tbits);
  Gate(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  Gate(const CbitList& cbits, const Tbit& tbit);
  Gate(const std::initializer_list<Cbit>& cbits, const Tbit& tbit);
  Gate(const CbitList& cbits, const TbitList& tbits);
  Gate(const std::initializer_list<Cbit>& cbits, \
       const std::initializer_list<Tbit>& tbits);
  Gate(const Gate& other);

 public:
  virtual ~Gate();
  auto operator=(const Gate& other) -> Gate&;
  auto operator==(const Gate& other) const -> bool;
  auto operator!=(const Gate& other) const -> bool;
  virtual auto clone() const -> GatePtr = 0;
  virtual auto getGateType() const -> int = 0;
  auto getCbitList() const -> const CbitList&;
  auto getTbitList() const -> const TbitList&;
  auto setCbits(const CbitList& cbits) -> void;
  auto setTbits(const TbitList& tbits) -> void;
  //virtual Matrix getTargetUnitary() const = 0;
  auto getUsedBits() const -> BitList;
  auto isAllPositive() const -> bool;
  virtual auto print(std::ostream& os) const -> void;
};

inline auto Gate::getCbitList() const -> const CbitList& {
  return this->cbits_;
}

inline auto Gate::getTbitList() const -> const TbitList& {
  return this->tbits_;
}

inline auto Gate::setCbits(const CbitList& cbits) -> void {
  this->cbits_ = cbits;
}

inline auto Gate::setTbits(const TbitList& tbits) -> void {
  this->tbits_ = tbits;
}

/**
 * @brief V gate class
 * @note gate type is 16
 */
class V : public Gate {
public:
  V(const Tbit& tbit);
  V(const Cbit& cbit, const Tbit& tbit);
  V(const Cbit& cbit, const TbitList& tbits);
  V(const Cbit& cbit, const std::initializer_list<Tbit>& tbits);
  V(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  V(const CbitList& cbits, const Tbit& tbit);
  V(const std::initializer_list<Cbit>& cbits, const Tbit& tbit);
  V(const CbitList& cbits, const TbitList& tbits);
  V(const std::initializer_list<Cbit>& cbits, \
    const std::initializer_list<Tbit>& tbits);
  auto clone() const -> GatePtr;
  auto getGateType() const -> int;
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix(Matrix::TYPE_V);
  }
  */
  void print(std::ostream& os) const;
};

inline auto V::clone() const -> GatePtr {
  return std::move(std::make_shared<V>(*this));
}

inline auto V::getGateType() const -> int {
  return 16;
}

/**
 * @brief V+ gate class
 * @note gate type is 15
 */
class VPlus : public Gate {
public:
  VPlus(const Tbit& tbit);
  VPlus(const Cbit& cbit, const Tbit& tbit);
  VPlus(const Cbit& cbit, const TbitList& tbits);
  VPlus(const Cbit& cbit, const std::initializer_list<Tbit>& tbits);
  VPlus(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  VPlus(const CbitList& cbits, const Tbit& tbit);
  VPlus(const std::initializer_list<Cbit>& cbits, const Tbit& tbit);
  VPlus(const CbitList& cbits, const TbitList& tbits);
  VPlus(const std::initializer_list<Cbit>& cbits, \
        const std::initializer_list<Tbit>& tbits);
  auto clone() const -> GatePtr;
  auto getGateType() const -> int;
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix(Matrix::TYPE_VI);
  }
  */
  void print(std::ostream& os) const;
};

inline auto VPlus::clone() const -> GatePtr {
  return std::move(std::make_shared<VPlus>(*this));
}

inline auto VPlus::getGateType() const -> int {
  return 15;
}

/**
 * @brief Hadamard gate class
 * @note gate type is 1
 */
class H : public Gate {
public:
  H(const Tbit& tbit);
  H(const CbitList& cbits, const TbitList& tbits);
  auto clone() const -> GatePtr;
  auto getGateType() const -> int;
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix();
  }
  */
  void print(std::ostream& os) const;
};

inline auto H::clone() const -> GatePtr {
  return std::move(std::make_shared<H>(*this));
}

inline auto H::getGateType() const -> int {
  return 1;
}

/**
 * @brief NOT gate class
 * @note gate type is 2
 */
class Not : public Gate {
public:
  Not(const Tbit& tbit);
  Not(const Cbit& cbit, const Tbit& tbit);
  Not(const Cbit& cbit, const TbitList& tbits);
  Not(const Cbit& cbit, const std::initializer_list<Tbit>& tbits);
  Not(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  Not(const CbitList& cbits, const Tbit& tbit);
  Not(const std::initializer_list<Cbit>& cbits, const Tbit& tbit);
  Not(const CbitList& cbits, const TbitList& tbits);
  Not(const std::initializer_list<Cbit>& cbits, \
      const std::initializer_list<Tbit>& tbits);
  auto clone() const -> GatePtr;
  auto getGateType() const -> int;
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix(Matrix::TYPE_N);
  }
  */
  void print(std::ostream& os) const;
};

inline auto Not::clone() const -> GatePtr {
  return std::move(std::make_shared<Not>(*this));
}

inline auto Not::getGateType() const -> int {
  return 2;
}

/**
 * @brief Z gate class
 * @note gate type is 6
 */
class Z : public Gate {
public:
  Z(const Tbit& tbit);
  Z(const Cbit& cbit, const Tbit& tbit);
  Z(const Cbit& cbit, const TbitList& tbits);
  Z(const Cbit& cbit, const std::initializer_list<Tbit>& tbits);
  Z(const Cbit& cbit1, const Cbit& cbit2, const Tbit& tbit);
  Z(const CbitList& cbits, const Tbit& tbit);
  Z(const std::initializer_list<Cbit>& cbits, const Tbit& tbit);
  Z(const CbitList& cbits, const TbitList& tbits);
  Z(const std::initializer_list<Cbit>& cbits, \
    const std::initializer_list<Tbit>& tbits);
  auto clone() const -> GatePtr;
  auto getGateType() const -> int;
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix();
  }
  */
  void print(std::ostream& os) const;
};

inline auto Z::clone() const -> GatePtr {
  return std::move(std::make_shared<Z>(*this));
}

inline auto Z::getGateType() const -> int {
  return 6;
}

/**
 * @brief Swap gate class
 * @note gate type is 12
 */
class Swap : public Gate {
public:
  Swap(const Tbit& tbit1, const Tbit& tbit2);
  Swap(const Cbit& cbit, const TbitList& tbits);
  Swap(const Cbit& cbit, const std::initializer_list<Tbit>& tbits);
  Swap(const CbitList& cbits, const TbitList& tbits);
  Swap(const std::initializer_list<Cbit>& cbits, \
       const std::initializer_list<Tbit>& tbits);
  auto clone() const -> GatePtr;
  auto getGateType() const -> int;
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix();
  }
  */
  void print(std::ostream& os) const;
};

inline auto Swap::clone() const -> GatePtr {
  return std::move(std::make_shared<Swap>(*this));
}

inline auto Swap::getGateType() const -> int {
  return 12;
}
}

namespace std {
template <class T>
struct hash<unordered_set<T>> {
  auto operator()(const unordered_set<T>& obj) const -> size_t {
    size_t hash_value;
    for(const auto& elem : obj)
      hash_value ^= hash<T>()(elem) + 0x9e3779b9 + (hash_value << 6);
    return hash_value;
  }
};

template <>
struct hash<qc::Gate> {
  auto operator()(const qc::Gate& obj) const -> size_t {
    auto cbit_hash = hash<unordered_set<qc::Cbit>>()(obj.getCbitList());
    auto tbit_hash = hash<unordered_set<qc::Tbit>>()(obj.getTbitList());
    return cbit_hash ^ tbit_hash;
  }
};
}
