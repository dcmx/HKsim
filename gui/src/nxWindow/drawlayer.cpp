/*
 * nxdrawlayer.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "drawlayer.h"
#include "gl.h"

namespace nx {

void DrawLayer::draw() {
	if (lineWidth > 0.0)
		glLineWidth(lineWidth);

	if (enabled && primitives.size() > 0) {
		color.set();
		for (std::list<Drawable*>::iterator it = primitives.begin(); it != primitives.end(); ++it)
			(*it)->draw();
	}
	Layer::draw();
	if (lineWidth > 0.0)
		glLineWidth(DEFAULT_LINE_WIDTH);
}

}
