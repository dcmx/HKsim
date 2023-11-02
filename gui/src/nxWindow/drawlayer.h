/*
 * nxdrawlayer.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef NXDRAWLAYER_H_
#define NXDRAWLAYER_H_

#include <list>

#include "layer.h"
namespace nx {
class DrawLayer: public Layer {
public:
	DrawLayer(const colors::Color& color) :
			Layer(), color(color), lineWidth(0.0) {
	}

	virtual ~DrawLayer() {
		for (std::list<Drawable*>::iterator it = primitives.begin(); it != primitives.end(); ++it)
			delete *it;
		primitives.clear();
	}
	virtual void draw();
	void addPrimitive(Drawable* primitive) {
		primitives.push_back(primitive);
	}
	colors::Color& getColor() {
		return color;
	}
	void setLineWidth(const double lineWidth) {
		this->lineWidth = lineWidth;
	}
protected:
	std::list<Drawable*> primitives;
	colors::Color color;
	double lineWidth;
};
}
#endif /* NXDRAWLAYER_H_ */
