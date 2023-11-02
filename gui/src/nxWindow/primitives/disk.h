/*
 * disk.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef DISK_H_
#define DISK_H_

#include "../drawable.h"
#include "../vector.h"

namespace nx {

class Disk: public Drawable {
public:
	Disk(const vector& center, const double r) :
			center(center), r(r) {
	}
	void draw();
private:
	const vector center;
	const double r;
};

} /* namespace nx */
#endif /* LINE_H_ */
