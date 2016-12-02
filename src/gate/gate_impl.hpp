/**
 * @file gate_impl.hpp
 * @brief implementation header of quantum gate classes
 */

#pragma once

#include <cassert>

#include "gate_kernel.hpp"
#include "../util/tmpl.hpp"

namespace qc {
inline Gate::Gate(Gate const& other) : kernel_(other.kernel_->clone()) {}

template <class Type, class... Args>
inline auto Gate::make(Args&&... args) -> Gate {
  using GateKernelT = util::tmpl::template_parameter_t<Type>;
  return Gate(new GateKernelT(std::forward<Args>(args)...));
}

inline auto Gate::make_dummy(bool assert_flag) -> Gate {
  assert(!assert_flag);
  return Gate(nullptr);
}

inline auto Gate::operator=(Gate const& other) -> Gate& {
  kernel_ = other.kernel_->clone();
  return *this;
}

inline auto Gate::operator==(const Gate& other) const -> bool {
  return *kernel_ == *other.kernel_;
}

inline auto Gate::operator!=(const Gate& other) const -> bool {
  return !(*this == other);
}

inline auto Gate::get_type_name() const -> util::string::String const& {
  return kernel_->get_type_name();
}

inline auto Gate::is_group() const -> bool {
  return kernel_->is_group();
}

inline auto Gate::get_cbits() const -> CBits const& {
  return kernel_->get_cbits();
}

inline auto Gate::get_tbits() const -> TBits const& {
  return kernel_->get_tbits();
}

inline auto Gate::get_gates() const -> Gates const& {
  return kernel_->get_gates();
}

inline auto Gate::print(std::ostream& os) const -> void {
  kernel_->print(os);
}

inline auto Gate::collect_bits() const -> BitNos {
  return is_group() ?
    GatesWrapperShell::collect_bits() : BitsWrapperShell::collect_bits();
}

inline auto Gate::_get_cbits() -> CBits& {
  return kernel_->get_cbits();
}

inline auto Gate::_get_tbits() -> TBits& {
  return kernel_->get_tbits();
}

inline auto Gate::_get_gates() -> Gates& {
  return kernel_->get_gates();
}

inline Gate::Gate(std::unique_ptr<GateKernel>&& kernel)
  : kernel_(std::move(kernel)) {}

inline Gate::Gate(GateKernel*&& kernel) : kernel_(std::move(kernel)) {}
}
