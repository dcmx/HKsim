/*
 * color.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "color.h"
#include "gl.h"

namespace nx {
namespace colors {

const Color red(1.0, 0.0, 0.0);
const Color green(0.0, 0.8, 0.0);
const Color blue(0.0, 0.0, 1.0);
const Color yellow(1.0, 1.0, 0.0);
const Color white(1.0, 1.0, 1.0, 1.0);
const Color lightgrey(0.75, 0.75, 0.75);
const Color grey(0.5, 0.5, 0.5);
const Color darkgrey(0.25, 0.25, 0.25);
const Color black(0.0, 0.0, 0.0, 1.0);
const Color magenta(1.0, 0.0, 1.0);
const Color cyan(0.0, 1.0, 1.0);

void Color::set() const {
	glColor4d(r, g, b, a);
}

void Color::setAsBackground() const {
	glClearColor(r, g, b, a);
	glBlendColor(r, g, b, a);
}

}
}
