/*
 * circle.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class Circle: public Drawable {
public:
	Circle(const vector& center, const double r) :
			center(center), r(r) {
	}

	void draw();
private:
	const vector center;
	const double r;
};

} /* namespace nx */
#endif /* CIRCLE_H_ */
