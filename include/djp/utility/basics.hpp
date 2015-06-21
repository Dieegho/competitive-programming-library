//          Copyright Diego Ramírez June 2015
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
/// \file
/// \brief Defines basic utility functions.

#ifndef DJP_UTILITY_BASICS_HPP
#define DJP_UTILITY_BASICS_HPP

#include <cstddef> // for std::size_t

namespace djp {

/// \brief Invokes a given function a fixed number of times.
///
/// \param n The number of times to invoke \p f.
/// \param f The function to be invoked on each repetition.
///
template <typename Function>
inline void repeat(std::size_t n, Function f) {
  while (n--)
    f();
}

} // end namespace djp

#endif // Header guard
