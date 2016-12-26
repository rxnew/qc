#pragma once

namespace qc {
inline namespace algorithm {
inline namespace tqc {
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
  return coords_[bit];
}

template <int dim, class Real>
inline auto Layout<dim, Real>::get_coords() const
  -> std::map<BitNo, Point> const& {
  return coords_;
}
}
}
}
