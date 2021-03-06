//          Copyright Jorge Aguirre 2015
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef CPL_GEOMETRY_SHOELACE_HPP
#define CPL_GEOMETRY_SHOELACE_HPP

#include <cpl/geometry/point_2d.hpp> // point2d
#include <cassert>                   // assert
#include <cmath>                     // abs(Float)
#include <cstddef>                   // size_t
#include <cstdlib>                   // abs(Integer)
#include <vector>                    // vector

namespace cpl {

/// \brief Computes the area of a simple polygon.
///
/// Uses the Gauss's area formula to compute the area of the polygon `poly`.
///
/// \param poly The polygon to determine area.
///
/// \pre `poly.size() >= 3`
///
/// \returns **Twice** the area of the polygon `poly`.
///
/// \par Complexity
/// Linear in `poly.size()`.
///
template <typename T>
T shoelace_area(const std::vector<point2d<T>>& poly) {
  assert(poly.size() >= 3);
  using std::size_t;

  T sum = 0;
  const size_t n = poly.size();
  for (size_t i = 1; i + 1 < n; ++i)
    sum += poly[i].x * (poly[i + 1].y - poly[i - 1].y);
  sum += poly[0].x * (poly[1].y - poly[n - 1].y);
  sum += poly[n - 1].x * (poly[0].y - poly[n - 2].y);
  return std::abs(sum);
}

/// \brief Computes the area of a simple polygon.
///
/// \param poly The input polygon.
///
/// \pre `poly.size() >= 3`
///
/// \returns The computed area.
///
/// \par Complexity
/// Linear in `poly.size()`
///
/// \note If `T` is an integer type the result might not be representable on
/// this type.
///
template <typename T>
T compute_polygon_area(const std::vector<point2d<T>>& poly) {
  return shoelace_area(poly) / T{2};
}

} // end namespace cpl

#endif // Header guard
