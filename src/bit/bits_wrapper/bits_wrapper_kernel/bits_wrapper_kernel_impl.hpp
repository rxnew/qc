#pragma once

namespace qc {
inline BitsWrapperKernel::BitsWrapperKernel(TBit const& tbit) : tbits_{tbit} {}

inline BitsWrapperKernel::BitsWrapperKernel(CBit const& cbit, TBit const& tbit)
  : cbits_{cbit}, tbits_{tbit} {}

inline BitsWrapperKernel::BitsWrapperKernel(CBit const& cbit, const TBits& tbits)
  : cbits_{cbit}, tbits_(tbits) {}

inline BitsWrapperKernel::BitsWrapperKernel(CBit const& cbit, TBits&& tbits)
  : cbits_{cbit}, tbits_(std::move(tbits)) {}

inline BitsWrapperKernel::BitsWrapperKernel(const CBits& cbits, TBit const& tbit)
  : cbits_(cbits), tbits_{tbit} {}

inline BitsWrapperKernel::BitsWrapperKernel(CBits&& cbits, TBit const& tbit)
  : cbits_(std::move(cbits)), tbits_{tbit} {}

inline BitsWrapperKernel::BitsWrapperKernel(const CBits& cbits, const TBits& tbits)
  : cbits_(cbits), tbits_(tbits) {}

inline BitsWrapperKernel::BitsWrapperKernel(CBits&& cbits, TBits&& tbits)
  : cbits_(std::move(cbits)), tbits_(std::move(tbits)) {}

inline auto BitsWrapperKernel::operator==(BitsWrapperKernel const& other) const
  -> bool {
  return cbits_ == other.cbits_ && tbits_ == other.tbits_;
}

inline auto BitsWrapperKernel::operator!=(BitsWrapperKernel const& other) const
  -> bool {
  return !(*this == other);
}
}
