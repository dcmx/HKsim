/*
 * line.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class Triangle: public Drawable {
public:
	Triangle(const vector& a, const vector& b, const vector& c) :
			a(a), b(b), c(c) {
	}
	void draw();
private:
	const vector a, b, c;
};

} /* namespace nx */
#endif /* LINE_H_ */
