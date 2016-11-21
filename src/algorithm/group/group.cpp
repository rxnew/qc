#include "../group.hpp"

#include "../../gate/group.hpp"
#include "../../gate/gates_wrapper/gates_wrapper_shell.hpp"

namespace qc {
auto is_group(Gate const& gate) -> bool {
  return gate.get_type_name() == Group::TYPE_NAME;
}

auto has_group(GatesWrapperShell const& target) -> bool {
  for(auto const& gate : target.get_gates()) {
    if(is_group(gate)) return true;
  }
  return false;
}

auto remove_empty_groups(GatesWrapperShell& target) -> void {
  auto it = target.begin_gates();
  while(it != target.end_gates()) {
    if(is_group(*it)) {
      remove_empty_groups(*it);
      if(it->empty()) {
        it = target.erase_gate(it);
        continue;
      }
    }
    ++it;
  }
}

auto expand_groups(GatesWrapperShell& target) -> void {
  auto it = target.begin_gates();
  while(it != target.end_gates()) {
    if(is_group(*it)) {
      expand_groups(*it);
      auto jt = it->begin_gates();
      while(jt != it->end_gates()) {
        assert(!is_group(*jt));
        auto pos = target.insert_gate(it, Gate::make_dummy(false));
        jt = it->erase_gate(jt, *pos);
      }
      it = target.erase_gate(it);
      continue;
    }
    ++it;
  }
}
}
