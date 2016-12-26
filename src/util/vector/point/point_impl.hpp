#pragma once

#include <cmath>

namespace qc {
namespace util {
namespace vector {
// prototype declarations
template <class Real>
auto _dot(Point<2, Real> const& a, Point<2, Real> const& b) -> Real;
template <class Real>
auto _cross(Point<2, Real> const& a, Point<2, Real> const& b) -> Real;
template <class Real>
auto _ccw(Point<2, Real> const& a,
          Point<2, Real> const& b,
          Point<2, Real> const& c) -> int;

// implementations
template <int dim, class Real>
template <class... Args>
Point<dim, Real>::Point(Args... args) {

}

template <int dim, class Real>
auto Point<dim, Real>::operator==(Point const& other) const -> bool {
  return p_ == other.p_;
}

template <int dim, class Real>
auto Point<dim, Real>::operator!=(Point const& other) const -> bool {
  return p_ != other.p_;
}

template <int dim, class Real>
auto Point<dim, Real>::operator<(Point<dim, Real> const& other) const -> bool {
  for(auto i = dim - 1; i >= 0; --i) {
    if((*this)[i] < other[i]) return true;
    if((*this)[i] > other[i]) return false;
  }
  return p_[0] != other.p_[0];
}

template <int dim, class Real>
auto Point<dim, Real>::operator>(Point<dim, Real> const& other) const -> bool {
  for(auto i = dim - 1; i >= 0; --i) {
    if((*this)[i] > other[i]) return true;
    if((*this)[i] < other[i]) return false;
  }
  return p_[0] != other.p_[0];
}

template <int dim, class Real>
inline auto Point<dim, Real>::operator[](size_t n) -> Real& {
  return p_[n];
}

template <int dim, class Real>
inline auto Point<dim, Real>::operator[](size_t n) const -> Real const& {
  return p_[n];
}

template <int dim, class Real>
auto Point<dim, Real>::operator+(Point<dim, Real> const& other) const
  -> Point {
  std::array<Real, dim> p;
  for(auto i = 0; i < dim; ++i) {
    p[i] = (*this)[i] + other[i];
  }
  return Point(std::move(other));
}

template <int dim, class Real>
auto Point<dim, Real>::operator-(Point<dim, Real> const& other) const
  -> Point {
  std::array<Real, dim> p;
  for(auto i = 0; i < dim; ++i) {
    p[i] = (*this)[i] - other[i];
  }
  return Point(std::move(other));
}

template <int dim, class Real>
inline auto Point<dim, Real>::dimension() const -> int {
  return dim;
}

template <int dim, class Real>
auto Point<dim, Real>::inner_product() const -> Real {
  auto result = Real(0);
  for(auto const& e : p_) {
    result += e * e;
  }
  return result;
}

template <int dim, class Real>
auto Point<dim, Real>::norm() const -> Real {
  return std::sqrt(inner_product());
}

template <int dim, class Real>
auto operator<<(std::ostream& os, Point<dim, Real> const& point)
  -> std::ostream& {
  os << "(";
  for(auto i = 0; i < dim; ++i) {
    if(i != 0) os << ", ";
    os << point[i];
  }
  return os << ")";
}

template <class Real>
auto is_intersected(Point<1, Real> const& a1,
                    Point<1, Real> const& a2,
                    Point<1, Real> const& b1,
                    Point<1, Real> const& b2) -> bool {
  Point<1, Real> a_max = std::max(a1, a2); 
  Point<1, Real> a_min = std::min(a1, a2);
  Point<1, Real> b_max = std::max(b1, b2);
  Point<1, Real> b_min = std::min(b1, b2);
  return !(a_min > b_max || a_max < b_min);
}

template <class Real>
auto is_intersected(Point<2, Real> const& a1,
                    Point<2, Real> const& a2,
                    Point<2, Real> const& b1,
                    Point<2, Real> const& b2) -> bool {
  return
    _ccw(a1, a2, b1) * _ccw(a1, a2, b2) <= 0 &&
    _ccw(b1, b2, a1) * _ccw(b1, b2, a2) <= 0;
}

template <class Real>
auto _dot(Point<2, Real> const& a, Point<2, Real> const& b) -> Real {
  return a[0] * b[0] + a[1] * b[1];
}

template <class Real>
auto _cross(Point<2, Real> const& a, Point<2, Real> const& b) -> Real {
  return a[0] * b[1] - a[1] * b[0];
}

template <class Real>
auto _ccw(Point<2, Real> const& a,
          Point<2, Real> const& b,
          Point<2, Real> const& c) -> int {
  b = b - a;
  c = c - a;
  if(_cross(b, c) > 0)    return +1;       // counter clockwise
  if(_cross(b, c) < 0)    return -1;       // clockwise
  if(_dot(b, c) < 0)      return +2;       // c--a--b on line
  if(b.norm() < c.norm()) return -2;       // a--b--c on line
  return 0;
}
}
}
}
