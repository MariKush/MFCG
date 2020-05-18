#ifndef SHORTESTPATH2D_HASH_H
#define SHORTESTPATH2D_HASH_H

#include <functional>
#include "Point.h"

namespace std {
	template<>
	class hash<shortestPath2D::Point> {
	public:
		size_t operator()(const shortestPath2D::Point& point) const {
			size_t seed = 0;
			seed ^= hash<shortestPath2D::real>()(point.x()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash<shortestPath2D::real>()(point.y()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};
}

#endif
