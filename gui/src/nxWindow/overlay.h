/*
 * nxdrawlayer.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef NXOVERLAY_H_
#define NXOVERLAY_H_

#include "layer.h"
#include "drawlayer.h"
#include "gl.h"

namespace nx {
class Overlay: public DrawLayer {
public:
	Overlay(const colors::Color& color, unsigned int mode = 0) :
			DrawLayer(color), mode(mode) {
	}

	void draw() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if(mode & 0x1) {
			const vector& mousePosition = Window::get()->getMousePosition();
			glTranslated(mousePosition.x, mousePosition.y, 0.0);
		}
		if(mode & 0x2) {
			const double scale = Window::get()->getPixelLength();
			glScaled(scale, scale, scale);
		}

		DrawLayer::draw();
		glLoadIdentity();
	}
private:
	unsigned int mode;
};
}
#endif /* NXOVERLAY_H_ */
