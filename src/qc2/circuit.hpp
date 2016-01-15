/**
 * @file circuit.hpp
 * @brief header of the quantum circuit class
 */

#pragma once

#include <fstream>

#include "gate.hpp"

namespace qc {
class Circuit;

using CircuitPtr = std::shared_ptr<Circuit>;

using GateList = std::list<GatePtr>;
using IterGateList = GateList::iterator;
using CIterGateList = GateList::const_iterator;

using Step = std::unordered_set<GatePtr>;
using StepList = std::list<Step>;
using IterStepList = StepList::iterator;
using CIterStepList = StepList::const_iterator;

/**
 * @brief quantum circuit class
 */
class Circuit {
 protected:
  GateList gates_;
  DDMFMgr ddmf_mgr_;
  std::map<Bitno, DDMF> initial_ddmf_;

 public:
  Circuit();
  Circuit(const Circuit& other);
  virtual ~Circuit();
  Circuit& operator=(const Circuit& other);
  bool operator==(const Circuit& other) const;
  bool operator!=(const Circuit& other) const;
  inline const GateList& getGateList() const {
    return this->gates_;
  }
  inline void addGate(const GatePtr& gate) {
    assert(gate.get() != nullptr);
    this->gates_.push_back(gate);
  }
  inline void addGate(Gate*&& gate) {
    assert(gate != nullptr);
    this->gates_.emplace_back(gate);
  }
  inline CIterGateList insertGate(CIterGateList pos, const GatePtr& gate) {
    assert(pos != this->gates_.cend());
    assert(gate.get() != nullptr);
    return this->gates_.insert(pos, gate);
  }
  inline CIterGateList insertGate(CIterGateList pos, Gate*&& gate) {
    assert(pos != this->gates_.cend());
    assert(gate != nullptr);
    return this->gates_.emplace(pos, gate);
  }
  inline void insertGate(const GatePtr& pos, const GatePtr& gate) {
    insertGate(this->findGate(pos), gate);
  }
  inline void insertGate(const GatePtr& pos, Gate*&& gate) {
    insertGate(this->findGate(pos), std::move(gate));
  }
  inline void eraseGate(const GatePtr& gate) {
    this->gates_.remove(gate);
  }
  inline CIterGateList eraseGate(CIterGateList pos) {
    return this->gates_.erase(pos);
  }
  inline void append(const Circuit& circ) {
    for(const auto& gate : circ.gates_)
      this->addGate(new Gate(*gate));
  }
  inline GatePtr getFirstGate() const {
    return this->gates_.front();
  }
  inline GatePtr getLastGate() const {
    return this->gates_.back();
  }
  GatePtr getAnyGate(int n) const;
  int getGateIndex(const GatePtr& gate) const;
  int countGates() const;
  BitList getUsedBits() const;
  inline CIterGateList findGate(const GatePtr& gate) const {
    return std::find(this->gates_.cbegin(), this->gates_.cend(), gate);
  }
  inline bool isExistGate(const GatePtr& gate) const {
    return this->gates_.cend() != this->findGate(gate);
  }
  void calcDDMF();
  DDMF getDDMF(Bitno bitno, const StepPtr& step) const;
  inline DDMF getDDMF(Bitno bitno) const {
    return this->getDDMF(bitno, this->getLastStep());
  }
  std::map<Bitno, DDMF> getDDMF(const StepPtr& step) const;
  inline std::map<Bitno, DDMF> getDDMF() const {
    return this->getDDMF(this->getLastStep());
  }
  inline void print(std::ostream& os) const {
    for(const auto& gate : this->gates_)
      gate->print(os);
  }
  void open(const std::string& filename);
  void open(const char* filename);
};

class CircuitParallelizer {
 protected:
  // 双方向連結リスト型Stepクラスの先頭だけ持つ方がいいか？
  StepList steps_;
 public:
  CircuitParallelizer();
  CircuitParallelizer(const Circuit& circ);
  virtual ~CircuitParallelizer();
  inline const StepList& getStepList() const {
    return this->steps_;
  }
  inline std::size_t getNumberOfSteps const {
    return this->steps_.size();
  }

  // 未実装
  Circuit makeCircuit();
  void doFlat();
  bool isFlat() const;
};

/**
 * @brief management quantum circuit file class
 */
class OpenFile {
 private:
  CircuitPtr circ_;
  void add(const std::string& type, const CbitList& cbits,
           const TbitList& tbits);
  void add(const std::string& type, const CbitList& cbits,
           const TbitList& tbits, const StepPtr& step);
  bool checkLine(std::string& line, int& pstate, int& judge) const;
  std::string getWord(std::string& line) const;
  std::string getBitUntilSpace(std::string& line) const;
  std::string getExtension(const std::string& filename) const;
  void processOneLine(std::string line, const StepPtr& step,
                      int& pstate, int& judge);
  void openQuantumObjectFile(const std::string& filename);

 public:
  void operator()(const CircuitPtr& circ, const std::string& filename);
};
}
