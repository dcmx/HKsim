/*
 * line.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef CIRCULAR_ARC_
#define CIRCULAR_ARC_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class CircularArc: public Drawable {
public:
	CircularArc(const vector& m, const vector& a, const vector& b, const bool ccw = false) :
			m(m), a(a), b(b), ccw(ccw) {
	}
	void draw();

private:
	const vector m, a, b;
	const bool ccw;
};

} /* namespace nx */
#endif /* CIRCULAR_ARC_H_ */
