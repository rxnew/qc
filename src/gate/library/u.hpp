/**
 * @file u.hpp
 * @brief header of U class
 */

#pragma once

#include "../gate_type.hpp"
#include "../unit.hpp"
#include "../gate_kernel/unit_kernel.hpp"
#include "../../util/string/aliases.hpp"

namespace qc {
class UKernel : public UnitKernel {
 public:
  static constexpr GateType const TYPE = GateType::U;
  static constexpr char const* const TYPE_NAME = "U";
  static constexpr util::string::Aliases<1> const ALIASES = {
    "u"
  };

  UKernel() = default;
  template <class T, class... Args, class =
            std::enable_if_t<!std::is_convertible<T, std::string>::value>>
  UKernel(T&& arg, Args&&... args);
  template <class... Args>
  UKernel(char const* const type_name, Args&&... args);
  template <class... Args>
  UKernel(std::string const& type_name, Args&&... args);
  UKernel(UKernel const& other);
  UKernel(UKernel&& other) noexcept;

  virtual ~UKernel() noexcept = default;

  auto operator=(UKernel const& other) -> UKernel&;
  auto operator=(UKernel&& other) noexcept -> UKernel&;
  auto operator==(UKernel const& other) const -> bool;
  auto operator!=(UKernel const& other) const -> bool;
  virtual auto operator==(GateKernel const& other) const -> bool;
  virtual auto operator!=(GateKernel const& other) const -> bool;

  virtual auto clone() const -> std::unique_ptr<GateKernel>;
  virtual auto get_type() const -> GateType;
  virtual auto get_type_name() const -> std::string;

 private:
  std::string type_name_;
};

inline namespace library_gates {
using U = Unit<UKernel>;
}
}

#include "u/u_impl.hpp"
