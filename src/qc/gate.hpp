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
  Gate& operator=(const Gate& other);
  bool operator==(const Gate& other) const;
  bool operator!=(const Gate& other) const;
  virtual GatePtr clone() const = 0;
  virtual int getGateType() const = 0;
  inline const CbitList& getCbitList() const {
    return this->cbits_;
  }
  inline const TbitList& getTbitList() const {
    return this->tbits_;
  }
  inline void setCbits(const CbitList& cbits) {
    this->cbits_ = cbits;
  }
  inline void setTbits(const TbitList& tbits) {
    this->tbits_ = tbits;
  }
  //virtual Matrix getTargetUnitary() const = 0;
  BitList getUsedBits() const;
  bool isAllPositive() const;
  virtual void print(std::ostream& os) const;
};

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

  inline GatePtr clone() const {
    return std::move(std::make_shared<V>(*this));
  }
  inline int getGateType() const {
    return 16;
  }
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix(Matrix::TYPE_V);
  }
  */
  void print(std::ostream& os) const;
};

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

  inline GatePtr clone() const {
    return std::move(std::make_shared<VPlus>(*this));
  }
  inline int getGateType() const {
    return 15;
  }
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix(Matrix::TYPE_VI);
  }
  */
  void print(std::ostream& os) const;
};

/**
 * @brief Hadamard gate class
 * @note gate type is 1
 */
class H : public Gate {
public:
  H(const Tbit& tbit);
  H(const CbitList& cbits, const TbitList& tbits);

  inline GatePtr clone() const {
    return std::move(std::make_shared<H>(*this));
  }
  inline int getGateType() const {
    return 1;
  }
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix();
  }
  */
  void print(std::ostream& os) const;
};

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

  inline GatePtr clone() const {
    return std::move(std::make_shared<Not>(*this));
  }
  inline int getGateType() const {
    return 2;
  }
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix(Matrix::TYPE_N);
  }
  */
  void print(std::ostream& os) const;
};

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

  inline GatePtr clone() const {
    return std::move(std::make_shared<Z>(*this));
  }
  inline int getGateType() const {
    return 6;
  }
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix();
  }
  */
  void print(std::ostream& os) const;
};

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

  inline GatePtr clone() const {
    return std::move(std::make_shared<Swap>(*this));
  }
  inline int getGateType() const {
    return 12;
  }
  /*
  inline Matrix getTargetUnitary() const {
    return Matrix();
  }
  */
  void print(std::ostream& os) const;
};
}

namespace std {
template <class T>
struct hash<unordered_set<T>> {
  size_t operator()(const unordered_set<T>& obj) const {
    size_t hash_value;
    for(const auto& elem : obj)
      hash_value ^= hash<T>()(elem) + 0x9e3779b9 + (hash_value << 6);
    return hash_value;
  }
};

template <>
struct hash<qc::Gate> {
  size_t operator()(const qc::Gate& obj) const {
    auto cbit_hash = hash<unordered_set<qc::Cbit>>()(obj.getCbitList());
    auto tbit_hash = hash<unordered_set<qc::Tbit>>()(obj.getTbitList());
    return cbit_hash ^ tbit_hash;
  }
};
}
