#ifndef NX_VECTOR_H
#define NX_VECTOR_H

#include <math.h>
#include <utility>

namespace nx {

/**
 * Basic class for vectors
 */
class vector {
public:
	/**
	 *  Anything that has an x and y field is a vector
	 */
	template<typename T> vector(const T& p) :
			x(p.x), y(p.y) {
	}

	vector() :
			x(0.0), y(0.0) {
	}
	vector(double x, double y) :
			x(x), y(y) {
	}
	vector(const vector& v) :
			x(v.x), y(v.y) {
	}
	vector(const std::pair<double, double>& pair) :
			x(pair.first), y(pair.second) {
	}

	inline bool operator==(const vector& v) const {
		return x == v.x && y == v.y;
	}

	inline bool operator!=(const vector& v) const {
		return x != v.x || y != v.y;
	}

	inline void operator+=(const vector& v) {
		x += v.x;
		y += v.y;
	}

	inline void operator*=(const double& s) {
		x *= s;
		y *= s;
	}

	inline vector operator+(const vector& v) const {
		return vector(x + v.x, y + v.y);
	}

	inline vector operator-(const vector& v) const {
		return vector(x - v.x, y - v.y);
	}

	inline vector operator-() const {
		return vector(-x, -y);
	}

	inline vector operator*(const double& s) const {
		return vector(x * s, y * s);
	}

	inline vector operator/(const double& s) const {
		return vector(x / s, y / s);
	}

	inline void normalize() {
		const double l = length();
		x /= l;
		y /= l;
	}

	inline double length() const {
		return sqrt(x * x + y * y);
	}

	inline double length2() const {
		return (x * x + y * y);
	}

	inline double distance(const vector&v) const {
		return sqrt((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
	}

	inline double distance2(const vector&v) const {
		return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y);
	}

	inline double operator*(const vector& v) const {
		return (x * v.x) + (y * v.y);
	}

	double dotProduct(const vector& v) const {
		return (x * v.x) + (y * v.y);
	}

	double crossProduct(const vector& v) const {
		return (x * v.y) - (y * v.x);
	}

	double cos(const vector& v) const {
		return (dotProduct(v) / (length() * v.length()));
	}

	double angle(const vector& v) const {
		return acos(cos(v));
	}

	inline vector rotate(const vector& v) const {
		return vector(v.x * x + v.y * y, -v.y * x + v.x * y);
	}

	inline vector rotateBack(const vector& v) const {
		return vector(v.x * x - v.y * y, v.y * x + v.x * y);
	}

	inline vector norm() const {
		const double l = length();
		return vector(x / l, y / l);
	}

	double x;
	double y;

};

inline vector operator*(const double& s, const vector&v) {
	return vector(v.x * s, v.y * s);
}

}
#endif
