/*
 * line.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "arrow.h"
#include "line.h"
#include "../vector.h"
#include "../window.h"
#include "../gl.h"

namespace nx {

void Arrow::draw() {
	const double size = (Window::get()->getPixelLength()) * 4.0;
	if ((a - b).length2() < size * size)
		return;
	const vector t = (b - a).norm() * size;
	const vector c = b - 2.0 * t;
	const vector l = c + vector(t.y, -t.x);
	const vector r = c + vector(-t.y, t.x);

	double currentColor[4];
	glGetDoublev(GL_CURRENT_COLOR, currentColor);

	colors::white.set();
	glBegin(GL_TRIANGLES);
	glVertex2d(b.x, b.y);
	glVertex2d(l.x, l.y);
	glVertex2d(r.x, r.y);
	glEnd();
	colors::Color(currentColor[0], currentColor[1], currentColor[2], currentColor[3]).set();
	Line(a, c).draw();
	Line(l, r).draw();
	Line(r, b).draw();
	Line(b, l).draw();
}

} /* namespace nx */
