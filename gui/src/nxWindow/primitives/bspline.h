/*
 * bspline.h
 *
 *  Created on: Mar 22, 2012
 *      Author: dkaaser
 */

#ifndef BSPLINE_H_
#define BSPLINE_H_
#include <list>

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class BSpline: public Drawable {
public:
	BSpline(const std::list<vector>& controlPoints);
	~BSpline();
	void draw();
private:
	float* controlPoints;
	float* knots;
	int numPoints;

};

} /* namespace nx */
#endif /* BSPLINE_H_ */
