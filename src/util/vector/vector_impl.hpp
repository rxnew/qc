#pragma once

#include <cmath>

namespace qc {
namespace util {
namespace vector {
// prototype declarations
template <class Real>
auto _ccw(Vector<2, Real> const& a,
          Vector<2, Real> const& b,
          Vector<2, Real> const& c) -> int;

// implementations
template <int dim, class Real>
template <class T, class... Args, class>
inline Vector<dim, Real>::Vector(T&& t, Args&&... args)
  : p_{{std::forward<T>(t), std::forward<Args>(args)...}} {
}

template <int dim, class Real>
inline auto Vector<dim, Real>::operator==(Vector const& other) const -> bool {
  return p_ == other.p_;
}

template <int dim, class Real>
inline auto Vector<dim, Real>::operator!=(Vector const& other) const -> bool {
  return p_ != other.p_;
}

template <int dim, class Real>
auto Vector<dim, Real>::operator<(Vector<dim, Real> const& other) const -> bool {
  for(auto i = dim - 1; i >= 0; --i) {
    if((*this)[i] < other[i]) return true;
    if((*this)[i] > other[i]) return false;
  }
  return p_[0] != other.p_[0];
}

template <int dim, class Real>
auto Vector<dim, Real>::operator>(Vector<dim, Real> const& other) const -> bool {
  for(auto i = dim - 1; i >= 0; --i) {
    if((*this)[i] > other[i]) return true;
    if((*this)[i] < other[i]) return false;
  }
  return p_[0] != other.p_[0];
}

template <int dim, class Real>
inline auto Vector<dim, Real>::operator[](size_t n) -> Real& {
  return p_[n];
}

template <int dim, class Real>
inline auto Vector<dim, Real>::operator[](size_t n) const -> Real const& {
  return p_[n];
}

template <int dim, class Real>
auto Vector<dim, Real>::operator+(Vector<dim, Real> const& other) const
  -> Vector {
  auto vector = Vector<dim, Real>();
  for(auto i = 0; i < dim; ++i) {
    vector[i] = (*this)[i] + other[i];
  }
  return vector;
}

template <int dim, class Real>
auto Vector<dim, Real>::operator-(Vector<dim, Real> const& other) const
  -> Vector {
  auto vector = Vector<dim, Real>();
  for(auto i = 0; i < dim; ++i) {
    vector[i] = (*this)[i] - other[i];
  }
  return vector;
}

template <int dim, class Real>
inline auto Vector<dim, Real>::dimension() const -> int {
  return dim;
}

template <int dim, class Real>
template <class>
auto Vector<dim, Real>::norm(int n) const -> Real {
  auto inner = Real(0);
  for(auto const& e : p_) {
    inner += std::pow(e, n);
  }
  return std::pow(inner, Real(1) / n);
}

template <int dim, class Real>
template <class>
auto Vector<dim, Real>::norm(int n) const -> long double {
  auto inner = 0;
  for(auto const& e : p_) {
    inner += std::pow(e, n);
  }
  return std::pow(static_cast<long double>(inner), 1.0l / n);
}

template <int dim, class Real>
inline Vector<dim, Real>::Vector(std::array<Real, dim> const& p) : p_(p) {
}

template <int dim, class Real>
inline Vector<dim, Real>::Vector(std::array<Real, dim>&& p) : p_(std::move(p)) {
}

template <int dim, class Real>
auto operator<<(std::ostream& os, Vector<dim, Real> const& vector)
  -> std::ostream& {
  os << "(";
  for(auto i = 0; i < dim; ++i) {
    if(i != 0) os << ", ";
    os << vector[i];
  }
  return os << ")";
}

template <int dim, class Real>
auto dot(Vector<dim, Real> const& a, Vector<dim, Real> const& b) -> Real {
  auto result = Real(0);
  for(auto i = 0; i < dim; ++i) {
    result += a[i] * b[i];
  }
  return result;
}

template <class Real>
auto cross(Vector<2, Real> const& a, Vector<2, Real> const& b) -> Real {
  return a[0] * b[1] - a[1] * b[0];
}

template <class Real>
auto cross(Vector<3, Real> const& a, Vector<3, Real> const& b)
  -> Vector<3, Real> {
  return Vector<3, Real>(a[1] * b[2] - a[2] * b[1],
                         a[2] * b[0] - a[0] * b[2],
                         a[0] * b[1] - a[1] * b[0]);
}

template <class Real>
auto is_intersected(Vector<1, Real> const& a1,
                    Vector<1, Real> const& a2,
                    Vector<1, Real> const& b1,
                    Vector<1, Real> const& b2) -> bool {
  Vector<1, Real> const& a_max = std::max(a1, a2); 
  Vector<1, Real> const& a_min = std::min(a1, a2);
  Vector<1, Real> const& b_max = std::max(b1, b2);
  Vector<1, Real> const& b_min = std::min(b1, b2);
  return !(a_min > b_max || a_max < b_min);
}

template <class Real>
auto is_intersected(Vector<2, Real> const& a1,
                    Vector<2, Real> const& a2,
                    Vector<2, Real> const& b1,
                    Vector<2, Real> const& b2) -> bool {
  return
    _ccw(a1, a2, b1) * _ccw(a1, a2, b2) <= 0 &&
    _ccw(b1, b2, a1) * _ccw(b1, b2, a2) <= 0;
}

template <class Real>
auto _ccw(Vector<2, Real> const& a,
          Vector<2, Real> const& b,
          Vector<2, Real> const& c) -> int {
  auto ba = b - a;
  auto ca = c - a;
  if(cross(ba, ca) > 0)     return +1; // counter clockwise
  if(cross(ba, ca) < 0)     return -1; // clockwise
  if(dot(ba, ca) < 0)       return +2; // c--a--b on line
  if(ba.norm() < ca.norm()) return -2; // a--b--c on line
  return 0;
}
}
}
}
