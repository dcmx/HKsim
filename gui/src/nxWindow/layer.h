/*
 * nxlayer.h
 *
 *  Created on: Mar 21, 2012
 *      Author: dkaaser
 */

#ifndef NXLAYER_H_
#define NXLAYER_H_

#include <list>
#include "color.h"
#include "drawable.h"
namespace nx {


class Window;
class Layer: public Drawable {
public:
	Layer(const bool enabled = true) :
			toggleKey(-1), enabled(enabled) {
	}
	virtual ~Layer() {
		for (std::list<Layer*>::iterator it = layers.begin(); it != layers.end(); ++it)
			delete *it;
		layers.clear();
	}
	virtual void draw() {
		if (enabled)
			for (std::list<Layer*>::iterator it = layers.begin(); it != layers.end(); ++it)
				(*it)->draw();
	}
	void addLayer(Layer* layer) {
		layers.push_back(layer);
	}

	virtual void key(int key) {
		for (std::list<Layer*>::iterator it = layers.begin(); it != layers.end(); ++it)
			(*it)->key(key);
		if (key == toggleKey)
			enabled = !enabled;
	}
	virtual void click(int button) {
		for (std::list<Layer*>::iterator it = layers.begin(); it != layers.end(); ++it)
			(*it)->click(button);
	}
	virtual void mouseMove() {
		for (std::list<Layer*>::iterator it = layers.begin(); it != layers.end(); ++it)
			(*it)->mouseMove();
	}
	virtual void mouseDown() {
		for (std::list<Layer*>::iterator it = layers.begin(); it != layers.end(); ++it)
			(*it)->mouseDown();
	}
	virtual void setToggleKey(int key) {
		toggleKey = key;
	}
	virtual void enable() {
		enabled = true;
	}
	virtual void disable() {
		enabled = false;
	}

protected:
	std::list<Layer*> layers;
	int toggleKey;
	bool enabled;
};
}
#endif /* NXLAYER_H_ */

