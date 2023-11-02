/*
 * line.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "ring.h"
#include "../gl.h"

namespace nx {

void Ring::draw() {

	const double step = M_PI / 180.0;

	glBegin(GL_TRIANGLE_STRIP);
	for (double deg = 0.0; deg < 2.0 * M_PI; deg += 2.0 * step) {
		glVertex2d(center.x + sin(deg) * r, center.y + cos(deg) * r);
		glVertex2d(center.x + sin(deg) * R, center.y + cos(deg) * R);

	}
	glEnd();

}

} /* namespace nx */
