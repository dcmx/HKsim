/*
 * dashedline.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef DASHEDLINE_H_
#define DASHEDLINE_H_

#include "line.h"
#include "../drawable.h"
#include "../vector.h"

namespace nx {

class DashedLine: public Line {
public:
	DashedLine(const vector& a, const vector& b, const double length = 0.0) :
			Line(a, b), length(length) {
	}
	void draw();
private:
	const double length;
};

} /* namespace nx */
#endif /* DASHEDLINE_H_ */
