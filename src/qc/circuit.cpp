/**
 * @file circuit.cpp
 * @brief implementation of the quantum circuit class
 */

#include "circuit.hpp"

namespace qc {
/**
 * @fn Circuit()
 * @brief constructor
 * @detail empty Circuit class constructor
 */
Circuit::Circuit() : ddmf_mgr_(10000, 1000, DDMFMgr::GC_TYPE_LIST_SIZE, 10) {
}

/**
 * @fn Circuit(const Circuit& other)
 * @brief copy constructor
 * @param [in] other another Circuit class object
 */
Circuit::Circuit(const Circuit& other) :
  ddmf_mgr_(10000, 1000, DDMFMgr::GC_TYPE_LIST_SIZE, 10) {
  for(const auto& gate : other.gates_)
    this->addGate(new Gate(*gate));
}

/**
 * @fn ~Circuit()
 * @brief destructor
 */
Circuit::~Circuit() {
  this->gates_.clear();
}

/**
 * @fn Circuit& operator=(const Circuit& other)
 * @brief assignment operator
 * @param [in] other another Circuit class object
 * @return reference to this object
 */
Circuit& Circuit::operator=(const Circuit& other) {
  for(const auto& gate : other.gates_)
    this->addGate(new Gate(*gate));
  return *this;
}

/**
 * @fn bool operator==(const Circuit& other) const
 * @brief equality operator
 * @param [in] other another Circuit class object
 * @return true or false
 */
bool Circuit::operator==(const Circuit& other) const {
  if(this->gates_.size() != other.gates_.size()) return false;

  auto it = this->gates_.cbegin();
  auto jt = other.gates_.cbegin();
  while(it != this->gates_.cend() || jt != other.gates_.cend()) {
    if(**it != **jt) return false;
    it++, jt++;
  }

  return true;
}

/**
 * @fn bool operator!=(const Circuit& other) const
 * @brief nonequivalence operator
 * @param [in] other another Circuit class object
 * @return true or false
 */
bool Circuit::operator!=(const Circuit& other) const {
  return !(*this == other);
}

GatePtr Circuit::getAnyGate(int n) const {
  int cnt = 0;
  for(const auto& gate_i : this->gates_)
    if(cnt++ == n) return gate_i;
  return GatePtr(nullptr);
}

int Circuit::getGateIndex(const GatePtr& gate) const {
  int cnt = 0;
  for(const auto& gate_i : this->gates_) {
    if(gate_i == gate) return cnt;
    cnt++;
  }
  return -1;
}

/**
 * @fn int countGates() const
 * @brief take the number of included quantum gates
 * @return the number of included quantum gates
 */
int Circuit::countGates() const {
  int cnt = 0;
  for(const auto& gate : this->gates_)
    cnt += static_cast<int>(gate->getGateList().size());
  return cnt;
}

/**
 * @fn BitList getUsedBits() const
 * @brief take used bits of all included parallel quanutm gates
 * @return used bits
 */
BitList Circuit::getUsedBits() const {
  BitList used_bits;
  for(const auto& gate : this->gates_) {
    auto gate_used_bits = gate->getUsedBits();
    used_bits.insert(gate_used_bits.cbegin(), gate_used_bits.cend());
  }
  return std::move(used_bits);
}

/**
 * @fn void calcDDMF()
 * @brief calculate DDMF
 */
void Circuit::calcDDMF() {
  if(this->steps_.empty()) return;

  auto used_bits = util::ContainerConverter::to_set(this->getUsedBits());
  for(const auto& bit : used_bits)
    this->initial_ddmf_.insert(std::make_pair(bit, this->ddmf_mgr_.ddmfVar()));

  StepPtr step, prev_step;
  for(auto it = this->steps_.begin(); it != this->steps_.end(); it++) {
    step = *it;
    if(it == this->steps_.begin())
      step->ddmf_ = this->initial_ddmf_;
    else
      step->ddmf_ = prev_step->ddmf_;
    step->calcDDMF(this->ddmf_mgr_);
    prev_step = step;
  }
}

/**
 * @fn DDMF getDDMF(Bitbo bitno, const StepPtr& step) const
 * @brief take the DDMF of appointed bit and parallel quantum gate
 * @param [in] bitno arbitrary bit number
 * @param [in] pqgate arbitrary parallel quantum gate
 * @return DDMF object
 * @note please call this method after calcDDMF()
 */
DDMF Circuit::getDDMF(Bitno bitno, const StepPtr& step) const {
  assert(this->isExistStep(step));
  auto pos1 = this->initial_ddmf_.find(bitno);
  auto pos2 = step->ddmf_.find(bitno);
  assert(pos1 != this->initial_ddmf_.end());
  assert(pos2 != step->ddmf_.end());
  return pos1->second ^ pos2->second;
}

/**
 * @fn std::map<Bitno, DDMF> getDDMF(const StepPtr& step) const
 * @brief take DDMFs of all bits of appointed parallel quantum gate
 * @param [in] pqgate arbitrary parallel quantum gate
 * @return map object
 *         key: BitNo, value: DDMF
 * @note please call this method after calcDDMF()
 */
std::map<Bitno, DDMF> Circuit::getDDMF(const StepPtr& step) const {
  assert(this->isExistStep(step));
  auto ddmf = this->initial_ddmf_;
  for(auto it = ddmf.begin(); it != ddmf.end(); it++) {
    auto pos = step->ddmf_.find(it->first);
    assert(pos != step->ddmf_.end());
    it->second = it->second ^ pos->second;
  }
  return ddmf;
}

void Circuit::open(const std::string& filename) {
  OpenFile()(CircuitPtr(this), filename);
}

void Circuit::open(const char* filename) {
  this->open(std::string(filename));
}

/**
 * @fn void add(const std::string& type, const CbitList& cbits,
 *              const TbitList& tbits);
 * @brief add the quantum gate to the circuit
 * @param [in] type gate type
 * @param [in] cbits control bits
 * @param [in] tbits target bits
 */
void OpenFile::add(const std::string& type, const CbitList& cbits,
                   const TbitList& tbits) {
  if(type == "Not" || type == "NOT")
    this->circ_->addGate(new Not(cbits, tbits));
  else if(type == "V")
    this->circ_->addGate(new V(cbits, tbits));
  else if(type == "VPlus")
    this->circ_->addGate(new VPlus(cbits, tbits));
  else if(type == "Z")
    this->circ_->addGate(new Z(cbits, tbits));
  else if(type == "H" || type == "Hadamard")
    this->circ_->addGate(new H(cbits, tbits));
}

/**
 * @fn void add(const std::string& type, const CbitList& cbits,
 *              const TbitList& tbits, const StepPtr& step);
 * @brief add the quantum gate to the parallel quantum gate
 * @param [in] type gate type
 * @param [in] cbits control bits
 * @param [in] tbits target bits
 * @param [in, out] step arbitrary parallel quantum gate
 */
void OpenFile::add(const std::string& type, const CbitList& cbits,
                   const TbitList& tbits, const StepPtr& step) {
  if(type == "Not" || type == "NOT")
    step->addGate(new Not(cbits, tbits));
  else if(type == "V")
    step->addGate(new V(cbits, tbits));
  else if(type == "VPlus")
    step->addGate(new VPlus(cbits, tbits));
  else if(type == "Z")
    step->addGate(new Z(cbits, tbits));
  else if(type == "H" || type == "Hadamard")
    step->addGate(new H(cbits, tbits));
}

/**
 * @fn bool checkLine(std::string& line, int& pstate, int& judge) const
 * @param [in, out] line string
 * @return true or false
 */
bool OpenFile::checkLine(std::string& line, int& pstate, int& judge) const {
  if(line.at(0) == '#') {
    std::string parallel = this->getBitUntilSpace(line);
    if(parallel == "#begin") {
      if(pstate == 1) {
        std::cout << "ERROR:"
                  << "#begin parallel follows #begin parallel"
                  << std::endl;
        exit(1);
      }
      pstate = 1;
      judge = 1;
    }
    else if(parallel == "#end") {
      if(pstate == 0) {
        std::cout << "ERROR:"
                  << "#end parallel follows #end parallel "
                  << std::endl;
        exit(1);
      }
      pstate = 0;
      judge = -1;
    }
    return false;
  }
  return true;
}

/**
 * @fn std::string getWord(std::string& line) const
 * @brief retrieves the word from the specified string until \\
 * @param [in, out] line string
 * @return extracted word
 * @datail from line starting from the head until \\ the word is returned
 *         spaces in the string to be returned are ignored
 *         e.g.) line = " Not \ 1 2 3 T3 \ \
 *               "Not" is returned, line = " 1 2 3 T3 \ \
 */
std::string OpenFile::getWord(std::string& line) const {
  std::string::size_type position = line.find_first_not_of(" \t");
  line.erase(0, position);
  position = line.find_first_of("\\");
  std::string word = line.substr(0, position);
  line.erase(0, position + 1);
  position = word.find_last_not_of(" \t");
  word.erase(position + 1, word.length() - position - 1);
  return word;
}

/**
 * @fn std::string getBitUntilSpace(std::string& line) const
 * @brief take the word between the start of the string until the next space
 * @param [in, out] line string
 * @return extracted word
 * @datail e.g.) line = "a b c f"
 *               "a" is returned, line = "b c d"
 */
std::string OpenFile::getBitUntilSpace(std::string& line) const {
  if(line.empty()) return "";
  std::string::size_type position = line.find_first_not_of(" \t");
  position = std::min(position, line.size());
  line.erase(0, position);
  position = line.find_first_of(" \t");
  position = std::min(position, line.size());
  std::string word = line.substr(0, position);
  line.erase(0, position + 1);
  return word;
}

/**
 * @fn string getExtension(const std::string& filename) const
 * @brief take the file extension
 * @return file extension
 */
std::string OpenFile::getExtension(const std::string& filename) const {
  if(filename.empty()) return "";
  std::string::size_type position = filename.find_last_of(".");
  if((int)position == -1) {
    std::cout << "ERROR::" << filename << " is illegal file." << std::endl;
    exit(1);
  }
  std::string word = filename.substr(position, filename.size());
  return word;
}

/**
 * @fn void processOneLine(std::string line, const StepPtr& step,
 *                         int& pstate, int& judge);
 * @brief process one line of the file
 * @param [in] line file to read
 */
void OpenFile::processOneLine(std::string line, const StepPtr& step,
                              int& pstate, int& judge) {
  std::string::size_type position;
  position = line.find_first_not_of(" \t");
  if(line.length() < position || position < 0) return;
  line.erase(0, position);
  if(!this->checkLine(line, pstate, judge)) return;
  judge = 0;
  std::string gate_type = this->getWord(line);
  std::string gate_nums = this->getWord(line);
  std::string bit;
  CbitList cbits;
  TbitList tbits;
  Cbit cbit;
  Tbit tbit;

  while((bit = this->getBitUntilSpace(gate_nums)) != "") {
    cbit.polarity_ = true;
    if(bit.at(0) == '!') {
      bit.erase(0, 1);
      cbit.polarity_ = false;
    }
    if(bit.at(0) == 'T') {
      bit.erase(0, 1);
      tbit.bitno_ = std::atoi(bit.c_str());
      tbits.insert(tbit);
    }
    else {
      cbit.bitno_ = std::atoi(bit.c_str());
      cbits.insert(cbit);
    }
  }

  if(pstate == 1)
    this->add(gate_type, cbits, tbits, step);
  else
    this->add(gate_type, cbits, tbits);
}

/**
 * @fn void openQuantumObjectFile(const std::string& filename)
 * @brief open the .qo file
 * @param [in] filename filename
 */
void OpenFile::openQuantumObjectFile(const std::string& filename) {
  std::ifstream circ_file;
  circ_file.open(filename.c_str(), std::ios::in);
  if(!circ_file) {
    std::cout << "ERROR::cannot open " << filename << std::endl;
    exit(1);
  }
  std::string buf;
  StepPtr step(nullptr);
  int judge = 0, pstate = 0;
  while(std::getline(circ_file, buf)) {
    this->processOneLine(buf, step, pstate, judge);
    if(judge == 1)
      step = std::make_shared<Step>();
    if(judge == -1)
      this->circ_->addStep(step);
  }
}

/**
 * @fn void operator()(const CircuitPtr& circ, const std::string& filename)
 * @brief function object
 *        open the file and set to the circuit
 * @param [in, out] circ pointer to circuit class object
 * @param [in] filename filename
 */
void OpenFile::operator()(const CircuitPtr& circ, const std::string& filename) {
  this->circ_ = circ;
  std::string extension = this->getExtension(filename);
  if(extension == ".qo")
    this->openQuantumObjectFile(filename);
  else
    std::cout << "ERROR::"<< filename << " is illegal filetype." << std::endl;
}
}
