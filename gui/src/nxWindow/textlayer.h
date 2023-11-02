/*
 * nxlayer.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef NXTEXTLAYER_H_
#define NXTEXTLAYER_H_
#include <string>
#include <list>
#include "vector.h"
#include "color.h"
#include "drawable.h"
#include "layer.h"
#include "vector.h"
namespace nx {
class TextLayer: public Layer {
public:
	TextLayer(const colors::Color color) :
			color(color) {
	}
	virtual ~TextLayer() {
	}
	virtual void draw();
	void write(const vector position, const char* fmt, ...);
	void write(const vector position, const std::string);

protected:
	colors::Color color;
	std::list<std::pair<vector, std::string> > messages;
};
}
#endif /* NXLAYER_H_ */

