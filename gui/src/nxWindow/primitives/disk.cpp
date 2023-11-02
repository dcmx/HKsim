/*
 * disk.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "disk.h"
#include "../gl.h"

namespace nx {

void Disk::draw() {
	const double step = M_PI / 180.0;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(center.x, center.y);
	for (double deg = 0.0; deg < 2.0 * M_PI; deg += step)
		glVertex2d(center.x + sin(deg) * r, center.y + cos(deg) * r);
	glEnd();
}

} /* namespace nx */
