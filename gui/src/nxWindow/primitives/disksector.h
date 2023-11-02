/*
 * line.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef DISKSECTOR_H_
#define DISKSECTOR_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class DiskSector: public Drawable {
public:
	DiskSector(const vector& m, const vector& a, const vector& b, const bool ccw = true) :
			m(m), a(a), b(b), ccw(ccw) {
	}
	void draw();
private:
	const vector m, a, b;
	const bool ccw;

};

} /* namespace nx */
#endif /* LINE_H_ */
