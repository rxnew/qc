#pragma once

#include <cmath>

namespace qc {
namespace util {
namespace vector {
// prototype declarations
template <class Real>
auto _cross(Point<2, Real> const& a, Point<2, Real> const& b) -> Real;
template <class Real>
auto _ccw(Point<2, Real> const& a,
          Point<2, Real> const& b,
          Point<2, Real> const& c) -> int;

// implementations
template <int dim, class Real>
template <class T, class... Args, class>
inline Point<dim, Real>::Point(T&& t, Args&&... args)
  : p_{{std::forward<T>(t), std::forward<Args>(args)...}} {
}

template <int dim, class Real>
inline auto Point<dim, Real>::operator==(Point const& other) const -> bool {
  return p_ == other.p_;
}

template <int dim, class Real>
inline auto Point<dim, Real>::operator!=(Point const& other) const -> bool {
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
  auto point = Point<dim, Real>();
  for(auto i = 0; i < dim; ++i) {
    point[i] = (*this)[i] + other[i];
  }
  return point;
}

template <int dim, class Real>
auto Point<dim, Real>::operator-(Point<dim, Real> const& other) const
  -> Point {
  auto point = Point<dim, Real>();
  for(auto i = 0; i < dim; ++i) {
    point[i] = (*this)[i] - other[i];
  }
  return point;
}

template <int dim, class Real>
inline auto Point<dim, Real>::dimension() const -> int {
  return dim;
}

template <int dim, class Real>
template <class>
auto Point<dim, Real>::norm(int n) const -> Real {
  auto inner = Real(0);
  for(auto const& e : p_) {
    inner += std::pow(e, n);
  }
  return std::pow(inner, Real(1) / n);
}

template <int dim, class Real>
template <class>
auto Point<dim, Real>::norm(int n) const -> long double {
  auto inner = 0;
  for(auto const& e : p_) {
    inner += std::pow(e, n);
  }
  return std::pow(static_cast<long double>(inner), 1.0l / n);
}

template <int dim, class Real>
inline Point<dim, Real>::Point(std::array<Real, dim> const& p) : p_(p) {
}

template <int dim, class Real>
inline Point<dim, Real>::Point(std::array<Real, dim>&& p) : p_(std::move(p)) {
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

template <int dim, class Real>
auto inner_product(Point<dim, Real> const& a, Point<dim, Real> const& b)
  -> Real {
  auto result = Real(0);
  for(auto i = 0; i < dim; ++i) {
    result += a[i] * b[i];
  }
  return result;
}

template <class Real>
auto is_intersected(Point<1, Real> const& a1,
                    Point<1, Real> const& a2,
                    Point<1, Real> const& b1,
                    Point<1, Real> const& b2) -> bool {
  Point<1, Real> const& a_max = std::max(a1, a2); 
  Point<1, Real> const& a_min = std::min(a1, a2);
  Point<1, Real> const& b_max = std::max(b1, b2);
  Point<1, Real> const& b_min = std::min(b1, b2);
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
auto _cross(Point<2, Real> const& a, Point<2, Real> const& b) -> Real {
  return a[0] * b[1] - a[1] * b[0];
}

template <class Real>
auto _ccw(Point<2, Real> const& a,
          Point<2, Real> const& b,
          Point<2, Real> const& c) -> int {
  auto ba = b - a;
  auto ca = c - a;
  if(_cross(ba, ca) > 0)        return +1; // counter clockwise
  if(_cross(ba, ca) < 0)        return -1; // clockwise
  if(inner_product(ba, ca) < 0) return +2; // c--a--b on line
  if(ba.norm() < ca.norm())     return -2; // a--b--c on line
  return 0;
}
}
}
}
