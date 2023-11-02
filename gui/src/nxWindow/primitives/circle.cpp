/*
 * circle.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */
#include <math.h>
#include "circle.h"
#include "../gl.h"

namespace nx {

void Circle::draw() {
	const double step = M_PI / 180.0;
	glBegin(GL_LINE_LOOP);
	for (double deg = 0.0; deg < 2.0 * M_PI; deg += step)
		glVertex2d(center.x + sin(deg) * r, center.y + cos(deg) * r);
	glEnd();
}

} /* namespace nx */
