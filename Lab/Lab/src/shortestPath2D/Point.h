#ifndef SHORTESTPATH2D_POINT_H
#define SHORTESTPATH2D_POINT_H

#include <complex>
#include "Common.h"

namespace shortestPath2D {
	class PolarPoint;

	class Point : public std::complex<real> {
	public:
		Point() {}
        Point(shortestPath2D::real x, shortestPath2D::real y) : std::complex<shortestPath2D::real>(x, y) {}
        Point(const std::complex<shortestPath2D::real> &c) : Point(c.real(), c.imag()) {}

        inline shortestPath2D::real x() const {
			return this->real();
		}

        inline shortestPath2D::real y() const {
			return this->imag();
		}

		inline PolarPoint toPolarPoint() const;

		inline bool operator< (const Point &b) const {
			if (this->x() != b.x())
				return this->x() < b.x();
			return this->y() < b.y();
		}
	};

	static inline real crossProduct(const Point &a, const Point &b) {
		return a.x() * b.y() - a.y() * b.x();
	}

	static inline real dotProduct(const Point &a, const Point &b) {
		return a.x() * b.x() + a.y() * b.y();
	}

	class PolarPoint : public std::complex<real> {
	public:
		PolarPoint() {}
        PolarPoint(shortestPath2D::real angle, shortestPath2D::real radius) : std::complex<shortestPath2D::real>(angle, radius) {}

        inline shortestPath2D::real angle() const {
			return this->real();
		}

        inline shortestPath2D::real radius() const {
			return this->imag();
		}

		inline Point toPoint() const {
			return Point(std::cos(angle()) * radius(), std::sin(angle()) * radius());
		}
	};

	PolarPoint Point::toPolarPoint() const {
        shortestPath2D::real angle = std::atan2(this->y(), this->x());
		return PolarPoint(angle < 0.0 ? angle + 2 * PI : angle, std::hypot(this->x(), this->y()));
	}
}

#endif
