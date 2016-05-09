/**
 * @file swap.cpp
 * @brief implementation of Swap class
 */

#include "../swap.hpp"

#include "../x.hpp"

namespace qc {
const std::string Swap::TYPE_NAME = "Swap";
const Matrix Swap::TARGET_MATRIX =
  util::matrix::create(Swap::_createTargetMatrixList());

auto Swap::computeMatrix(const std::set<Bitno>& bits) const -> Matrix {
  auto gates = this->decompose();
  auto size = static_cast<size_t>(std::pow(2, bits.size()));
  auto result = util::matrix::identity(size);
  for(const auto& gate : gates) {
    result = gate->computeMatrix(bits) * result;
  }
  return std::move(result);
}

auto Swap::decompose() const -> GateList {
  assert(static_cast<int>(this->tbits_.size()) == 2);

  auto tbits = util::container::convert<std::vector>(this->tbits_);
  std::vector<CbitList> cbit_lists(2, this->cbits_);
  cbit_lists[0].insert(Cbit(tbits[0].bitno_));
  cbit_lists[1].insert(Cbit(tbits[1].bitno_));

  GateList gates;
  gates.emplace_back(new X(cbit_lists[0], tbits[1]));
  gates.emplace_back(new X(cbit_lists[1], tbits[0]));
  gates.emplace_back(new X(cbit_lists[0], tbits[1]));

  return std::move(gates);
}
}
