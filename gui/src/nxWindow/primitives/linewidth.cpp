/*
 * linewidth.cpp
 *
 *      Author: dkaaser
 */

#include "linewidth.h"
#include "../gl.h"

namespace nx {

void LineWidth::draw() {
	glLineWidth(width);
}

} /* namespace nx */
