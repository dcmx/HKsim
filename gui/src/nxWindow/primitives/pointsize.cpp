/*
 * pointsize.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "pointsize.h"
#include "../gl.h"

namespace nx {

void PointSize::draw() {
	glPointSize(size);
}

} /* namespace nx */
