//          Copyright Diego Ramirez 2015
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef CPL_NUMBER_THEORY_SHANKS_FACTORIZATION_HPP
#define CPL_NUMBER_THEORY_SHANKS_FACTORIZATION_HPP

#include <cpl/number_theory/euclid.hpp>      // gcd
#include <cpl/number_theory/square_root.hpp> // isqrt, is_square
#include <cstddef>                           // size_t
#include <limits>                            // numeric_limits
#include <stdexcept>                         // overflow_error
#include <type_traits>                       // is_signed

namespace cpl {

/// \brief Finds a non-trivial factor of a composite number.
///
/// Uses the Square Forms Factorization (SQUFOF) algorithm to find a non-trivial
/// factor of <tt>n</tt>. This algorithm will have success as long as the
/// working type \p T is big enough to maintain all required multiplications. If
/// \c T is <tt>int64_t</tt>, it is guaranteed that all numbers less than
/// <tt>2<sup>58</sup></tt> can be factored without problems.
///
/// \tparam T A signed integer type.
///
/// \param n The integer to be factored.
///
/// \returns A non-trivial factor of <tt>N</tt>.
///
/// \pre \p n must be a composite number, that is, a positive integer greater
/// than \c 1 that is not a prime number.
///
/// \throws std::overflow_error if the algorithm needs to do a multiplication
/// which does not fit in <tt>T</tt>.
///
/// \par Complexity
/// The time complexity is <tt>O(<sup>4</sup>&radic;N)</tt>.
///
template <typename T>
T shanks_factor(const T n) {
  static_assert(std::is_signed<T>::value, "Must be signed");
  auto find_factor = [n](const T k) -> T {
    const T sqrt_kn = isqrt(k * n);
    T p = sqrt_kn, old_p;
    T q = (k * n - p * p), old_q = 1;
    if (q == 0)
      return k == 1 ? sqrt_kn : 1;
    auto iterate = [&] {
      old_p = p;
      T b = (sqrt_kn + old_p) / q, tmp;
      p = b * q - old_p;
      tmp = q, q = old_q + b * (old_p - p), old_q = tmp;
    };
    for (size_t i = 1; i % 2 || !is_square(q); ++i)
      iterate();
    const T sqrt_q = isqrt(q);
    const T b = (sqrt_kn - p) / sqrt_q;
    p = b * sqrt_q + p;
    old_q = sqrt_q, q = (k * n - p * p) / old_q;
    do
      iterate();
    while (p != old_p);
    return gcd(n, p);
  };
  const T max_k = std::numeric_limits<T>::max() / n;
  for (T k = 1; k <= max_k; ++k) {
    const T f = find_factor(k);
    if (f != 1 && f != n)
      return f;
  }
  throw std::overflow_error("Can't use a larger multiplier.");
}

} // end namespace cpl

#endif // Header guard
