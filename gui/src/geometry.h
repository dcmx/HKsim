/*
 * geometry.h
 *
 */

#ifndef SRC_GEOMETRY_H_
#define SRC_GEOMETRY_H_

#include "nxWindow/vector.h"

using nx::vector;

namespace geometry {
short int sign(const double x) {
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}
inline double area(const vector p1, const vector p2, const vector p3) {
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}
inline double pointLineDistance(const vector p, const vector q1, const vector q2) {
	return 0.5 * std::fabs(area(p, q1, q2)) / (q2 - q1).length();
}
inline bool inBetween(const vector p, const vector q1, const vector q2) {
	vector v = q2 - q1;
	vector n(v.y, -v.x);
	vector r1 = q1 + n;
	vector r2 = q2 + n;
	double A1 = area(q1, r1, p);
	double A2 = area(q2, r2, p);
	return sign(A1) != sign(A2);
}
}



#endif /* SRC_GEOMETRY_H_ */
