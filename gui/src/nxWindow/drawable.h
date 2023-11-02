/*
 * nxDrawable.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef NXDRAWABLE_H_
#define NXDRAWABLE_H_

namespace nx {

class Drawable {
public:
	Drawable() {
	}
	virtual ~Drawable() {
	}
	virtual void draw() = 0;
};

} /* namespace nx */
#endif /* NXDRAWABLE_H_ */
