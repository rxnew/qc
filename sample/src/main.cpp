#include "qc/circuit.hpp"
#include "qc/algorithm.hpp"
#include "qc/io.hpp"

auto main(int argc, char* argv[]) -> int {
  auto input = argc >= 2 ? argv[1] : "circuit_data/alu4.esop";
  auto circuit = qc::io::open(input);
  circuit.print();
  std::cout << std::endl;
  auto cost = qc::calculate_mct_circuit_cost(circuit);
  std::cout << "Circuit cost is " << cost << '.' << std::endl;
  return 0;
}
