#pragma once

#include "gates_wrapper/gates_wrapper_kernel.hpp"
#include "gates_wrapper/gates_wrapper_shell.hpp"

namespace qc {
class GatesWrapper : public GatesWrapperKernel, public GatesWrapperShell {
 public:
  GatesWrapper() = default;
  template <class... Args>
  GatesWrapper(Args&&... args);

  virtual ~GatesWrapper() noexcept = default;

  virtual auto get_gates() const -> Gates const& final;

 private:
  virtual auto _get_gates() -> Gates& final;
};
}

#include "gates_wrapper/gates_wrapper_impl.hpp"
