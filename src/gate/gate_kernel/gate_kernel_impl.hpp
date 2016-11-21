#pragma once

namespace qc {
inline GateKernel::GateKernel(TBit const& tbit) : tbits_{tbit} {}

inline GateKernel::GateKernel(CBit const& cbit, TBit const& tbit)
  : cbits_{cbit}, tbits_{tbit} {
}

inline GateKernel::GateKernel(CBit const& cbit, const TBits& tbits)
  : cbits_{cbit}, tbits_(tbits) {
}

inline GateKernel::GateKernel(CBit const& cbit, TBits&& tbits)
  : cbits_{cbit}, tbits_(std::move(tbits)) {
}

inline GateKernel::GateKernel(const CBits& cbits, TBit const& tbit) :
  cbits_(cbits), tbits_{tbit} {
}

inline GateKernel::GateKernel(CBits&& cbits, TBit const& tbit) :
  cbits_(std::move(cbits)), tbits_{tbit} {
}

inline GateKernel::GateKernel(const CBits& cbits, const TBits& tbits) :
  cbits_(cbits), tbits_(tbits) {
}

inline GateKernel::GateKernel(CBits&& cbits, TBits&& tbits) :
  cbits_(std::move(cbits)), tbits_(std::move(tbits)) {
}

inline auto GateKernel::operator==(GateKernel const& other) const -> bool {
  return
    get_type_name() == other.get_type_name() &&
    cbits_ == other.cbits_ && tbits_ == other.tbits_;
}

inline auto GateKernel::operator!=(GateKernel const& other) const -> bool {
  return !(*this == other);
}

inline auto GateKernel::get_cbits() -> CBits& {
  return cbits_;
}

inline auto GateKernel::get_cbits() const -> CBits const& {
  return cbits_;
}

inline auto GateKernel::get_tbits() -> TBits& {
  return tbits_;
}

inline auto GateKernel::get_tbits() const -> TBits const& {
  return tbits_;
}
}
