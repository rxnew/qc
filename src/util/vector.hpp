#pragma once

#include <array>
#include <sstream>

namespace qc {
namespace util {
namespace vector {
template <int dim, class Real = float>
class Vector {
public:
  Vector() = default;
  template <class T, class... Args,
            class = std::enable_if_t<!std::is_convertible<T, Vector>::value>>
  Vector(T&& t, Args&&... args);
  Vector(Vector const&) = default;
  Vector(Vector&&) noexcept = default;
  ~Vector() = default;

  auto operator=(Vector const&) -> Vector& = default;
  auto operator=(Vector&&) -> Vector& = default;
  auto operator==(Vector const& other) const -> bool;
  auto operator!=(Vector const& other) const -> bool;
  auto operator<(Vector const& other) const -> bool;
  auto operator>(Vector const& other) const -> bool;
  auto operator+(Vector const& other) const -> Vector;
  auto operator-(Vector const& other) const -> Vector;
  auto operator[](size_t n) -> Real&;
  auto operator[](size_t n) const -> Real const&;

  auto dimension() const -> int;
  template <class = std::enable_if_t<std::is_floating_point<Real>::value>>
  auto norm(int n = 2) const -> Real;
  template <class = std::enable_if_t<!std::is_floating_point<Real>::value>>
  auto norm(int n = 2) const -> long double;

 private:
  Vector(std::array<Real, dim> const& p);
  Vector(std::array<Real, dim>&& p);

  std::array<Real, dim> p_;
};

using Vector1d = Vector<1>;
using Vector2d = Vector<2>;

template <int dim, class Real>
auto operator<<(std::ostream& os, Vector<dim, Real> const& vector)
  -> std::ostream&;
template <int dim, class Real>
auto inner_product(Vector<dim, Real> const& a, Vector<dim, Real> const& b)
  -> Real;
template <class Real>
auto is_intersected(Vector<1, Real> const& a1,
                    Vector<1, Real> const& a2,
                    Vector<1, Real> const& b1,
                    Vector<1, Real> const& b2) -> bool;
template <class Real>
auto is_intersected(Vector<2, Real> const& a1,
                    Vector<2, Real> const& a2,
                    Vector<2, Real> const& b1,
                    Vector<2, Real> const& b2) -> bool;
}
}
}

#include "vector/vector_impl.hpp"
