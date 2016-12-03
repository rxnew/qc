#pragma once

#include "../../forward_declarations.hpp"
#include "../../bit.hpp"
#include "../../bit/hash.hpp"

namespace qc {
class BitsWrapperKernel {
 public:
  BitsWrapperKernel() = default;
  explicit BitsWrapperKernel(TBit const& tbit);
  BitsWrapperKernel(CBit const& cbit, TBit const& tbit);
  BitsWrapperKernel(CBit const& cbit, TBits const& tbits);
  BitsWrapperKernel(CBit const& cbit, TBits&& tbits);
  BitsWrapperKernel(CBits const& cbits, TBit const& tbit);
  BitsWrapperKernel(CBits&& cbits, TBit const& tbit);
  BitsWrapperKernel(CBits const& cbits, TBits const& tbits);
  BitsWrapperKernel(CBits&& cbits, TBits&& tbits);
  BitsWrapperKernel(std::initializer_list<CBit> cbits,
                    std::initializer_list<TBit> tbits);
  //template <class... Args>
  //explict BitsWrapperKernel(Args&&... args);
  BitsWrapperKernel(BitsWrapperKernel const&) = default;
  BitsWrapperKernel(BitsWrapperKernel&&) noexcept = default;

  virtual ~BitsWrapperKernel() noexcept = default;

  auto operator=(BitsWrapperKernel const& other)
    -> BitsWrapperKernel& = default;
  auto operator=(BitsWrapperKernel&&) noexcept
    -> BitsWrapperKernel& = default;
  auto operator==(BitsWrapperKernel const& other) const -> bool;
  auto operator!=(BitsWrapperKernel const& other) const -> bool;

 protected:
  CBits cbits_;
  TBits tbits_;
};
}

#include "bits_wrapper_kernel/bits_wrapper_kernel_impl.hpp"
