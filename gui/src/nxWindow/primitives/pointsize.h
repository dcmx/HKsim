/*
 * pointsize.h
 *
 *  Created on: Oct 28, 2014
 *      Author: dkaaser
 */

#ifndef POINTSIZE_H_
#define POINTSIZE_H_

#include "../drawable.h"

namespace nx {
class PointSize: public Drawable {
public:
	PointSize(const double size) :
			size(size) {
	}
	void draw();
private:
	const double size;
};
}

#endif /* POINTSIZE_H_ */
