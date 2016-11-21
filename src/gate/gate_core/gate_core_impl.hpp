#pragma once

namespace qc {
inline GateCore::GateCore(TBit const& tbit) : tbits_{tbit} {}

inline GateCore::GateCore(CBit const& cbit, TBit const& tbit)
  : cbits_{cbit}, tbits_{tbit} {
}

inline GateCore::GateCore(CBit const& cbit, const TBits& tbits)
  : cbits_{cbit}, tbits_(tbits) {
}

inline GateCore::GateCore(CBit const& cbit, TBits&& tbits)
  : cbits_{cbit}, tbits_(std::move(tbits)) {
}

inline GateCore::GateCore(const CBits& cbits, TBit const& tbit) :
  cbits_(cbits), tbits_{tbit} {
}

inline GateCore::GateCore(CBits&& cbits, TBit const& tbit) :
  cbits_(std::move(cbits)), tbits_{tbit} {
}

inline GateCore::GateCore(const CBits& cbits, const TBits& tbits) :
  cbits_(cbits), tbits_(tbits) {
}

inline GateCore::GateCore(CBits&& cbits, TBits&& tbits) :
  cbits_(std::move(cbits)), tbits_(std::move(tbits)) {
}

inline auto GateCore::operator==(GateCore const& other) const -> bool {
  return
    get_type_name() == other.get_type_name() &&
    cbits_ == other.cbits_ && tbits_ == other.tbits_;
}

inline auto GateCore::operator!=(GateCore const& other) const -> bool {
  return !(*this == other);
}

inline auto GateCore::get_cbits() -> CBits& {
  return cbits_;
}

inline auto GateCore::get_cbits() const -> CBits const& {
  return cbits_;
}

inline auto GateCore::get_tbits() -> TBits& {
  return tbits_;
}

inline auto GateCore::get_tbits() const -> TBits const& {
  return tbits_;
}
}
