#pragma once

namespace qc {
template <class... Args>
XCore::XCore(Args&&... args) : GateCore(std::forward<Args>(args)...) {}

inline auto XCore::clone() const -> std::unique_ptr<GateCore> {
  return std::make_unique<XCore>(*this);
}

inline auto XCore::get_type_name() const -> char const* const& {
  return TYPE_NAME;
}
}
