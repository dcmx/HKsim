/*
 * line.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef RING_H_
#define RING_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class Ring: public Drawable {
public:
	Ring(const vector& center, const double R, const double r) :
			center(center), R(R), r(r) {
	}
	void draw();
private:
	const vector center;
	const double R;
	const double r;
};

} /* namespace nx */
#endif /* RING_H_ */
