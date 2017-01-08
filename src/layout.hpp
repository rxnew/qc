/**
 * @file layout.hpp
 * @brief header of Layout class
 */

#pragma once

#include <iostream>
#include <map>

#include "mathutils/vector.hpp"

#include "circuit.hpp"

namespace qc {
template <int dim, class Real = int>
class Layout {
 public:
  using Vector = mathutils::Vector<dim, Real>;

  Layout() = default;
  Layout(std::map<BitNo, Vector> const& coords);
  Layout(std::map<BitNo, Vector>&& coords);
  Layout(Layout const&) = default;
  Layout(Layout&&) noexcept = default;
  ~Layout() = default;

  auto operator=(Layout const&) -> Layout& = default;
  auto operator=(Layout&&) noexcept -> Layout& = default;
  auto operator==(Layout const& other) const -> bool;
  auto operator!=(Layout const& other) const -> bool;
  auto operator[](BitNo bit) -> Vector&;
  auto operator[](BitNo bit) const -> Vector const&;

  auto get_coords() const -> std::map<BitNo, Vector> const&;
  auto find_min_bit() const -> BitNo;
  auto find_max_bit() const -> BitNo;
  auto find_min_corner() const -> Vector;
  auto find_max_corner() const -> Vector;
  auto find_bit_no(Vector const& vector) const -> std::tuple<bool, BitNo>;
  auto print(std::ostream& os = std::cout) const -> void;
  auto output(std::string const& filename) const -> void;
  auto input(std::string const& filename) -> bool;

 private:
  std::map<BitNo, Vector> coords_;
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

template <int dim, class Real = int,
          template <class...> class Container = std::vector>
auto make_regular_lattice_layout(Container<BitNo> const& bit_sequence)
  -> Layout<dim, Real>;
template <int dim, class Real = int>
auto make_regular_lattice_layout(int side_bit_count) -> Layout<dim, Real>;
template <int dim, class Real = int>
auto make_regular_lattice_layout(Circuit const& circuit) -> Layout<dim, Real>;
template <class Real = int, class... Args>
auto make_line_layout(Args&&... args) -> Layout<1, Real>;
template <class Real = int, class... Args>
auto make_square_layout(Args&&... args) -> Layout<2, Real>;
}

#include "layout/layout_impl.hpp"
