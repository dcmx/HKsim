/*
 * point.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "points.h"
#include "../gl.h"
#include "../window.h"

namespace nx {

void Point::draw() {
	glBegin(GL_POINTS);
	glVertex2d(p.x, p.y);
	glEnd();
}
void PointSquare::draw() {
	double d = 3.0 * Window::get()->getPixelLength();
	glBegin(GL_QUADS);
	glVertex2d(p.x - d, p.y - d);
	glVertex2d(p.x - d, p.y + d);
	glVertex2d(p.x + d, p.y + d);
	glVertex2d(p.x + d, p.y - d);
	glEnd();
}
void PointTriangle::draw() {
	double d1 = 4.0 * Window::get()->getPixelLength();
	double d2 = 0.577350269 * d1;
	glBegin(GL_TRIANGLES);
	glVertex2d(p.x - d1, p.y - d2);
	glVertex2d(p.x + d1, p.y - d2);
	glVertex2d(p.x, p.y + 2 * d2);
	glEnd();
	glBegin(GL_LINE);
	glVertex2d(p.x - d1, p.y - d2);
	glVertex2d(p.x + d1, p.y - d2);
	glVertex2d(p.x, p.y + 2 * d2);
	glVertex2d(p.x - d1, p.y - d2);
	glEnd();
}
void PointStar::draw() {
	double d1 = 5.0 * Window::get()->getPixelLength();
	double d2 = 0.577350269 * d1;
	glBegin(GL_TRIANGLES);
	glVertex2d(p.x - d1, p.y - d2);
	glVertex2d(p.x + d1, p.y - d2);
	glVertex2d(p.x, p.y + 2 * d2);
	glVertex2d(p.x - d1, p.y + d2);
	glVertex2d(p.x + d1, p.y + d2);
	glVertex2d(p.x, p.y - 2 * d2);
	glEnd();
	glBegin(GL_LINE);
	glVertex2d(p.x - d1, p.y - d2);
	glVertex2d(p.x + d1, p.y - d2);
	glVertex2d(p.x, p.y + 2 * d2);
	glVertex2d(p.x - d1, p.y - d2);
	glVertex2d(p.x - d1, p.y + d2);
	glVertex2d(p.x + d1, p.y + d2);
	glVertex2d(p.x, p.y - 2 * d2);
	glVertex2d(p.x - d1, p.y + d2);
	glEnd();
}
} /* namespace nx */
