#pragma once

#include <iomanip>
#include <limits>

namespace qc {
template <int dim, class Real>
inline Layout<dim, Real>::
Layout(std::map<BitNo, Point> const& coords) : coords_(coords) {
}

template <int dim, class Real>
inline Layout<dim, Real>::Layout(std::map<BitNo, Point>&& coords)
  : coords_(std::move(coords)) {
}

template <int dim, class Real>
inline auto Layout<dim, Real>::operator==(Layout const& other) const -> bool {
  return coords_ == other.coords_;
}

template <int dim, class Real>
inline auto Layout<dim, Real>::operator!=(Layout const& other) const -> bool {
  return coords_ != other.coords_;
}

template <int dim, class Real>
inline auto Layout<dim, Real>::operator[](BitNo bit) -> Point& {
  return coords_[bit];
}

template <int dim, class Real>
inline auto Layout<dim, Real>::operator[](BitNo bit) const -> Point const& {
  return coords_.at(bit);
}

template <int dim, class Real>
inline auto Layout<dim, Real>::get_coords() const
  -> std::map<BitNo, Point> const& {
  return coords_;
}

template <int dim, class Real>
auto Layout<dim, Real>::find_min_corner() const -> Point {
  auto corner_point = Point();
  for(auto i = 0; i < dim; ++i) {
    corner_point[i] = std::numeric_limits<Real>::max();
  }
  for(auto const& e : coords_) {
    auto const& point = e.second;
    for(auto i = 0; i < dim; ++i) {
      corner_point[i] = std::min(corner_point[i], point[i]);
    }
  }
  return corner_point;
}

template <int dim, class Real>
auto Layout<dim, Real>::find_max_corner() const -> Point {
  auto corner_point = Point();
  for(auto i = 0; i < dim; ++i) {
    corner_point[i] = std::numeric_limits<Real>::lowest();
  }
  for(auto const& e : coords_) {
    auto const& point = e.second;
    for(auto i = 0; i < dim; ++i) {
      corner_point[i] = std::max(corner_point[i], point[i]);
    }
  }
  return corner_point;
}

template <int dim, class Real>
auto Layout<dim, Real>::find_bit_no(Point const& point) const
  -> std::tuple<bool, BitNo> {
  for(auto const& e : coords_) {
    if(e.second == point) return std::make_tuple(true, e.first);
  }
  return std::make_tuple(false, BitNo());
}

template <int dim, class Real>
auto Layout<dim, Real>::print(std::ostream& os) const -> void {
  LayoutPrinter<dim, Real>::print(*this, os);
}

template <int dim, class Real, class Enable>
auto LayoutPrinter<dim, Real, Enable>::
print(Layout<dim, Real> const& layout, std::ostream& os) -> void {
  for(auto const& e : layout.get_coords()) {
    os << "bit";
    os << std::setw(4) << e.first;
    os << ": " << e.second << std::endl;
  }
}

template <class T>
auto LayoutPrinter<1, T, std::enable_if_t<std::is_integral<T>::value>>::
print(Layout<1, T> const& layout, std::ostream& os) -> void {
  auto min_corner_point = layout.find_min_corner();
  auto max_corner_point = layout.find_max_corner();
  auto current_point = min_corner_point;
  while(current_point[0] <= max_corner_point[0]) {
    auto found = layout.find_bit_no(current_point);
    if(std::get<0>(found)) {
      os << std::setw(4) << std::right << std::get<1>(found);
    }
    else {
      os << std::string(4, ' ');
    }
    ++current_point[0];
  }
  os << std::endl;
}

template <class T>
auto LayoutPrinter<2, T, std::enable_if_t<std::is_integral<T>::value>>::
print(Layout<2, T> const& layout, std::ostream& os) -> void {
  auto min_corner_point = layout.find_min_corner();
  auto max_corner_point = layout.find_max_corner();
  auto current_point = min_corner_point;
  while(current_point[0] <= max_corner_point[0]) {
    current_point[1] = min_corner_point[1];
    while(current_point[1] <= max_corner_point[1]) {
      auto found = layout.find_bit_no(current_point);
      if(std::get<0>(found)) {
        os << std::setw(4) << std::right << std::get<1>(found);
      }
      else {
        os << std::string(4, ' ');
      }
      ++current_point[1];
    }
    os << std::endl;
    ++current_point[0];
  }
}

template <int dim, class Real = int>
auto make_regular_lattice_layout(int side_bit_count) -> Layout<dim, Real> {
  auto layout = Layout<dim, Real>();
  auto point = typename Layout<dim, Real>::Point();
  auto bit_count = 0_bit;

  std::function<void(int)> f = [&](auto d) {
    if(d == dim) {
      layout[bit_count++] = point;
      return;
    }
    for(auto i = 0; i < side_bit_count; ++i) {
      point[d] = i;
      f(d + 1);
    }
  };

  f(0);

  return layout;
}

template <class Real = int>
auto make_line_layout(int bit_count) -> Layout<1, Real> {
  return make_regular_lattice_layout<1, Real>(bit_count);
}

template <class Real = int>
auto make_square_layout(int side_bit_count) -> Layout<2, Real> {
  return make_regular_lattice_layout<2, Real>(side_bit_count);
}
}
