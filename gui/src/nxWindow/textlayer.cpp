/*
 * nxlayer.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#include "textlayer.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "gl.h"
#include "window.h"
#include "vector.h"

namespace nx {
using std::string;

void TextLayer::draw() {
	if (!enabled)
		return;
	Layer::draw();
	color.set();
	for (std::list<std::pair<vector, std::string> >::iterator it = messages.begin(); it != messages.end(); ++it) {
		glRasterPos2d((*it).first.x, (*it).first.y);
		for (unsigned int i = 0; i < (*it).second.length(); ++i)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (*it).second[i]);
	}

}
void TextLayer::write(const vector position, const char* fmt, ...) {
	char text[1024];
	memset(text, 0, sizeof(char) * 1023);

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(text, 1023, fmt, ap);
	va_end(ap);
	write(position, string(text));
}
void TextLayer::write(const vector position, const string text) {
	messages.push_back(std::pair<vector, string>(position, text));
}

}
