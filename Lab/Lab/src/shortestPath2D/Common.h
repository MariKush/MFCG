#ifndef SHORTESTPATH2D_COMMON_H
#define SHORTESTPATH2D_COMMON_H

#include <cmath>

namespace shortestPath2D {
	typedef double real;

	const real EPS = 1e-9;
	const real INF = 1e9;
	const real PI = 2 * std::acos(0);

	static inline bool approx(real a, real b) {
		real diff = a > b ? a - b : b - a;
		return diff < EPS;
	}
}

#endif
