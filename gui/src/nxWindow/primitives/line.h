/*
 * line.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef LINE_H_
#define LINE_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class Line: public Drawable {
public:
	Line(const vector& a, const vector& b) :
			a(a), b(b) {
	}
	virtual void draw();
protected:
	const vector a, b;
};

} /* namespace nx */
#endif /* LINE_H_ */
