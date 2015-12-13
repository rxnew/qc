/**
 * @file circuit.hpp
 * @brief header of the quantum circuit class
 */

#pragma once

#include <fstream>

#include "step.hpp"

namespace qc {
class Circuit;

using CircuitPtr = std::shared_ptr<Circuit>;
using StepList = std::list<StepPtr>;
using IterStepList = StepList::iterator;
using CIterStepList = StepList::const_iterator;

/**
 * @brief quantum circuit class
 */
class Circuit {
 private:
  StepList steps_;
  DDMFMgr ddmf_mgr_;
  std::map<Bitno, DDMF> initial_ddmf_;

 public:
  Circuit();
  Circuit(const Circuit& other);
  virtual ~Circuit();
  Circuit& operator=(const Circuit& other);
  bool operator==(const Circuit& other) const;
  bool operator!=(const Circuit& other) const;
  inline const StepList& getStepList() const {return this->steps_;}
  inline void addStep(const StepPtr& step) {
    assert(step.get() != nullptr);
    this->steps_.push_back(step);
  }
  inline void addStep(Step*&& step) {
    assert(step != nullptr);
    this->steps_.emplace_back(step);
  }
  inline void addGate(const GatePtr& gate) {
    assert(gate.get() != nullptr);
    this->addStep(new Step(gate));
  }
  inline void addGate(Gate*&& gate) {
    assert(gate != nullptr);
    this->addStep(new Step(std::move(gate)));
  }
  inline CIterStepList insertStep(CIterStepList pos, const StepPtr& step) {
    assert(pos != this->steps_.cend());
    assert(step.get() != nullptr);
    return this->steps_.insert(pos, step);
  }
  inline CIterStepList insertStep(CIterStepList pos, Step*&& step) {
    assert(pos != this->steps_.cend());
    assert(step != nullptr);
    return this->steps_.emplace(pos, step);
  }
  inline void insertStep(const StepPtr& pos, const StepPtr& step) {
    insertStep(this->findStep(pos), step);
  }
  inline void insertStep(const StepPtr& pos, Step*&& step) {
    insertStep(this->findStep(pos), std::move(step));
  }
  inline void eraseStep(const StepPtr& step) {
    this->steps_.remove(step);
  }
  inline CIterStepList eraseStep(CIterStepList pos) {
    return this->steps_.erase(pos);
  }
  inline void eraseEmptySteps() {
    for(auto it = this->steps_.begin(); it != this->steps_.end(); it++)
      if((*it)->isEmpty()) it = this->steps_.erase(it);
  }
  inline void append(const Circuit& circ) {
    for(const auto& step : circ.steps_)
      this->addStep(new Step(*step));
  }
  inline StepPtr getFirstStep() const {
    return this->steps_.front();
  }
  inline StepPtr getLastStep() const {
    return this->steps_.back();
  }
  StepPtr getAnyStep(int n) const;
  int getStepIndex(const StepPtr& step) const;
  int countGates() const;
  BitList getUsedBits() const;
  void doFlat();
  bool isFlat() const;
  inline CIterStepList findStep(const StepPtr& step) const {
    return std::find(this->steps_.cbegin(), this->steps_.cend(), step);
  }
  inline bool isExistStep(const StepPtr& step) const {
    return this->steps_.cend() != this->findStep(step);
  }
  bool isExistGate(const GatePtr& gate) const;
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
    for(const auto& step : this->steps_)
      step->print(os);
  }
  void open(const std::string& filename);
  void open(const char* filename);
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
