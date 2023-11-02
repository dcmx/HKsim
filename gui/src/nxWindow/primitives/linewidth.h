/*
 * linewidth.h
 *
 *  Created on: Apr 20, 2012
 *      Author: dkaaser
 */

#ifndef LINEWIDTH_H_
#define LINEWIDTH_H_
#include "../drawable.h"

namespace nx {
class LineWidth: public Drawable {
public:
	LineWidth(const double width) :
			width(width) {
	}
	void draw();
private:
	const double width;
};
}

#endif /* LINEWIDTH_H_ */
