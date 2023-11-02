/*
 * line.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "rect.h"
#include "../gl.h"

namespace nx {

void Rect::draw() {

	glBegin(GL_LINE_LOOP);
	glVertex2d(a.x, a.y);
	glVertex2d(a.x, b.y);
	glVertex2d(b.x, b.y);
	glVertex2d(b.x, a.y);
	glEnd();
}

} /* namespace nx */
