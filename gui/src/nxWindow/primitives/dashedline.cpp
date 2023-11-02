#include "dashedline.h"
#include "../gl.h"
#include "../window.h"

namespace nx {

void DashedLine::draw() {
	const double length = this->length > 0 ? this->length : DEFAULT_DASH_SIZE * Window::get()->getPixelLength();
	int numSegments = ((int) ((b - a).length() / length)) | 1;
	vector offset = (b - a) / ((double) numSegments);
	glBegin(GL_LINES);
	glVertex2d(a.x, a.y);
	for (int i = 1; i < numSegments; ++i) {
		const vector pos = a + i * offset;
		glVertex2d(pos.x, pos.y);
	}
	glVertex2d(b.x, b.y);
	glEnd();

}

} /* namespace nx */
