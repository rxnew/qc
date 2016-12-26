/**
 * @file layout.hpp
 * @brief header of Layout class
 */

#pragma once

#include "forward_declarations.hpp"
#include "util/vector/point.hpp"

namespace qc {
inline namespace algorithm {
inline namespace tqc {
template <int dim, class Real = float>
class Layout {
 private:
  using Point = util::vector::Point<dim, Real>;

 public:
  Layout() = default;
  Layout(std::map<BitNo, Point> const& coords);
  Layout(std::map<BitNo, Point>&& coords);
  Layout(Layout const&) = default;
  Layout(Layout&&) noexcept = default;
  ~Layout() = default;

  auto operator=(Layout const&) -> Layout& = default;
  auto operator=(Layout&&) noexcept -> Layout& = default;
  auto operator==(Layout const& other) const -> bool;
  auto operator!=(Layout const& other) const -> bool;
  auto operator[](BitNo bit) -> Point&;
  auto operator[](BitNo bit) const -> Point const&;

  auto get_coords() const -> std::map<BitNo, Point> const&;
  auto print(std::ostream& os) const -> void;
  auto output(std::string const& filename) const -> void;
  auto input(std::string const& filename) -> bool;

 private:
  std::map<BitNo, Point> coords_;
};

using Layout1d = Layout<1>;
using Layout2d = Layout<2>;
}
}
}

#include "layout/layout_impl.hpp"
