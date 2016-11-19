#pragma once

#include "gates_wrapper/gates_wrapper_core.hpp"
#include "gates_wrapper/gates_wrapper_shell.hpp"

namespace qc {
class GatesWrapper : public GatesWrapperCore, public GatesWrapperShell {
 public:
  template <class... Args>
  GatesWrapper(Args&&... args);

  virtual ~GatesWrapper() noexcept = default;

  virtual auto get_gates() const -> Gates const& final;

 protected:
  virtual auto get_gates() -> Gates& final;
};

#include "gates_wrapper/gates_wrapper_impl.hpp"
