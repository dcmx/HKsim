/*
 * line.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "disksector.h"
#include "../gl.h"

namespace nx {

void DiskSector::draw() {

	const vector ma = ccw ? a - m : b - m;
	const vector mb = ccw ? b - m : a - m;
	const double phie = atan2(mb.y, mb.x);
	const double phis = atan2(ma.y, ma.x);

	double phi = phie - phis;
	if (phi < 0.0)
		phi += 2.0 * M_PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(m.x, m.y);
	ccw ? glVertex2d(a.x, a.y) : glVertex2d(b.x, b.y);
	const int n = ceil(phi / 0.01);
	for (int i = 1; i < n - 1; i++) {
		const double c = cos(0.01 * (double) i);
		const double s = sin(0.01 * (double) i);
		const vector mid = m + vector(ma.x * c - ma.y * s, ma.x * s + ma.y * c);
		glVertex2d(mid.x, mid.y);
	}
	ccw ? glVertex2d(b.x, b.y) : glVertex2d(a.x, a.y);

	glEnd();

}

} /* namespace nx */
