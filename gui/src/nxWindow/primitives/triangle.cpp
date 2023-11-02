/*
 * arrow.cpp
 *
 *      Author: dkaaser
 */

#include "triangle.h"
#include "../gl.h"

namespace nx {

void Triangle::draw() {
	glBegin(GL_TRIANGLES);
	glVertex2d(a.x, a.y);
	glVertex2d(b.x, b.y);
	glVertex2d(c.x, c.y);
	glEnd();
}

} /* namespace nx */
