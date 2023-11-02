/*
 * arrow.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef ARROW_H_
#define ARROW_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class Arrow: public Drawable {
public:
	Arrow(const vector& a, const vector& b) :
			a(a), b(b) {
	}
	void draw();
private:
	const vector a, b;
};

} /* namespace nx */
#endif
