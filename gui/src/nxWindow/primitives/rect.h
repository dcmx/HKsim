/*
 * line.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef RECT_H_
#define RECT_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class Rect: public Drawable {
public:
	Rect(const vector& a, const vector& b) :
			a(a), b(b) {
	}
	void draw();
private:
	const vector a, b;
};

} /* namespace nx */
#endif /* LINE_H_ */
