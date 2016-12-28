/**
 * @file layout.hpp
 * @brief header of Layout class
 */

#pragma once

#include "forward_declarations.hpp"
#include "util/vector/point.hpp"

namespace qc {
template <int dim, class Real = int>
class Layout {
 public:
  using Point = util::vector::Point<dim, Real>;

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
  auto find_min_corner() const -> Point;
  auto find_max_corner() const -> Point;
  auto find_bit_no(Point const& point) const -> std::tuple<bool, BitNo>;
  auto print(std::ostream& os = std::cout) const -> void;
  auto output(std::string const& filename) const -> void;
  auto input(std::string const& filename) -> bool;

 private:
  std::map<BitNo, Point> coords_;
};

template <int dim, class Real, class Enable = void>
struct LayoutPrinter {
  static auto print(Layout<dim, Real> const& layout,
                    std::ostream& os = std::cout) -> void;
};

template <class T>
struct LayoutPrinter<1, T, std::enable_if_t<std::is_integral<T>::value>> {
  static auto print(Layout<1, T> const& layout,
                    std::ostream& os = std::cout) -> void;
};

template <class T>
struct LayoutPrinter<2, T, std::enable_if_t<std::is_integral<T>::value>> {
  static auto print(Layout<2, T> const& layout,
                    std::ostream& os = std::cout) -> void;
};

using Layout1d = Layout<1>;
using Layout2d = Layout<2>;

template <int dim, class Real = int>
auto make_regular_lattice_layout(int side_bit_count) -> Layout<dim, Real>;

template <class Real = int>
auto make_line_layout(int bit_count) -> Layout<1, Real>;

template <class Real = int>
auto make_square_layout(int side_bit_count) -> Layout<2, Real>;
}

#include "layout/layout_impl.hpp"
