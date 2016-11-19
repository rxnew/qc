#include "../gate_wrapper.hpp"

namespace qc {
  template <class... Args>
  GatesWrapper::GatesWrapper(Args&&... args)
    : GatesWrapperCore(std::forward<Args>(args)...) {}
}
