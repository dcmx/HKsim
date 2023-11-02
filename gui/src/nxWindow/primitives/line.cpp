/*
 * line.cpp
 *
 *      Author: dkaaser
 */

#include "line.h"
#include "../gl.h"

namespace nx {

void Line::draw() {
	glBegin(GL_LINES);
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);
	glEnd();
}

} /* namespace nx */
