/*
 * point.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef POINT_H_
#define POINT_H_

#include "../drawable.h"
#include "../vector.h"
namespace nx {

class Point: public Drawable {
public:
	Point(const vector& p) :
			p(p) {
	}
	void draw();
	virtual ~Point() {
	}
protected:
	const vector p;
};

class PointSquare: public Point {
public:
	PointSquare(const vector& p) :
			Point(p) {
	}
	void draw();
};

class PointTriangle: public Point {
public:
	PointTriangle(const vector& p) :
			Point(p) {
	}
	void draw();
};

class PointStar: public Point {
public:
	PointStar(const vector& p) :
			Point(p) {
	}
	void draw();
};

} /* namespace nx */
#endif /* POINT_H_ */
