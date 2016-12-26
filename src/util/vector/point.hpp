#pragma once

#include <sstream>
#include <array>

namespace qc {
namespace util {
namespace vector {
template <int dim, class Real = float>
class Point {
public:
  Point() = default;
  template <class... Args>
  Point(Args... args);
  Point(Point const&) = default;
  Point(Point&&) noexcept = default;
  ~Point() = default;

  auto operator=(Point const&) -> Point const& = default;
  auto operator=(Point&&) -> Point const& = default;
  auto operator==(Point const& other) const -> bool;
  auto operator!=(Point const& other) const -> bool;
  auto operator<(Point const& other) const -> bool;
  auto operator>(Point const& other) const -> bool;
  auto operator+(Point const& other) const -> Point;
  auto operator-(Point const& other) const -> Point;
  auto operator[](size_t n) -> Real&;
  auto operator[](size_t n) const -> Real const&;

  auto dimension() const -> int;
  auto inner_product() const -> Real;
  auto norm() const -> Real;

 private:
  Point(std::array<Real, dim>&& p);

  std::array<Real, dim> p_;
};

using Point1d = Point<1>;
using Point2d = Point<2>;

template <int dim, class Real>
auto operator<<(std::ostream& os, Point<dim, Real> const& point)
  -> std::ostream&;
template <class Real>
auto is_intersected(Point<1, Real> const& a1,
                    Point<1, Real> const& a2,
                    Point<1, Real> const& b1,
                    Point<1, Real> const& b2) -> bool;
template <class Real>
auto is_intersected(Point<2, Real> const& a1,
                    Point<2, Real> const& a2,
                    Point<2, Real> const& b1,
                    Point<2, Real> const& b2) -> bool;
}
}
}

#include "point/point_impl.hpp"
