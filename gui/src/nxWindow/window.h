/*
 * nxwindow.h
 *
 *  Created on: Mar 21, 2012
 *      Author: Dominik Kaaser
 */

#ifndef NXWINDOW_H_
#define NXWINDOW_H_

#define KEY_LEFT 0x0064
#define KEY_UP 0x0065
#define KEY_RIGHT 0x0066
#define KEY_DOWN 0x0067

#include "layer.h"
#include "vector.h"
namespace nx {

class Window: public Layer {
public:
	Window() :
			Window("", NULL, NULL) {
	}
	Window(const char* title) :
			Window(title, NULL, NULL) {
	}
	Window(const char* title, int* argc, char** argv);
	virtual ~Window() {
		for (std::list<Layer*>::iterator it = layers.begin(); it != layers.end(); ++it)
			delete *it;
		layers.clear();
	}

	void show();
	void close();

	static Window* get() {
		return Window::instance;
	}
	const vector getMousePosition() const {
		return mousePosition;
	}
	const vector unproject(int x, int y) const;
	const double getPixelLength() const {
		return (right - left) / (double) windowWidth;
	}
	const vector getOffset() const {
		return vector(left, bottom);
	}
	void setZoomBounds(const double max, const double min) {
		maxZoom = max;
		minZoom = min;
	}
	void enableAntiAliasing();
	void disableAntiAliasing();

	vector getCenter() {
		return 0.5 * vector(left + right, top + bottom);
	}
	void setCenter(vector center) {
		double h = top - bottom;
		double w = right - left;
		top = center.y + 0.5 * h;
		bottom = center.y - 0.5 * h;
		left = center.x - 0.5 * w;
		right = center.x + 0.5 * w;
		updateDisplay();
	}
private:

	static Window* instance;

	static void __callback_draw();
	static void __callback_key(unsigned char, int, int);
	static void __callback_specialKey(int, int, int);
	static void __callback_reshape(int, int);
	static void __callback_click(int, int, int, int);
	static void __callback_mouseDown(int, int);
	static void __callback_mouseMove(int, int);

	const char* title;

	vector mousePosition;

	int windowWidth;
	int windowHeight;
	int windowLeft;
	int windowTop;

	int restoreWidth;
	int restoreHeight;

	double top;
	double right;
	double bottom;
	double left;

	bool fullscreen;

	int clickX;
	int clickY;
	int oldX;
	int oldY;
	int beginDragX;
	int beginDragY;

	double maxZoom;
	double minZoom;

	bool skipClick;

	void setPosition(int x, int y) {
		clickX = x;
		clickY = y;
	}
	void storePosition() {
		oldX = clickX;
		oldY = clickY;
	}

	void key(int key) {

		switch (key) {
		case 'Q':
		case 'q':
		case 27: // escape key
			close();
			break;
		case 'F':
		case 'f':
			toggleFullscreen();
			break;
		case '+':
			zoom(windowWidth / 2, windowHeight / 2, 2.0);
			break;
		case '-':
			zoom(windowWidth / 2, windowHeight / 2, 0.5);
			break;
		default:
			Layer::key(key);
			break;
		}
		postRedisplay();
	}
	void specialKey(int key) {
		const double scrollx = 0.125 * (left - right);
		const double scrolly = 0.125 * (top - bottom);
		switch (key) {
		case KEY_LEFT:
			left += scrollx;
			right += scrollx;
			break;
		case KEY_UP:
			top += scrolly;
			bottom += scrolly;
			break;
		case KEY_RIGHT:
			left -= scrollx;
			right -= scrollx;
			break;
		case KEY_DOWN:
			top -= scrolly;
			bottom -= scrolly;
			break;
		}
		updateDisplay();
	}
	void reshape(int x, int y) {
		windowWidth = x;
		windowHeight = y;
		updateDisplay();
	}
	void click(int button, int state) {
		if (button == 3 && state == 1)
			zoom(clickX, clickY, 2.0);
		if (button == 4 && state == 1)
			zoom(clickX, clickY, 0.5);

		if (state == 0) {
			beginDragX = clickX;
			beginDragY = clickY;
			return;
		}
		if (std::abs(beginDragX - clickX) + std::abs(beginDragY - clickY) > 5)
			return;
		Layer::click(button);
	}
	void mouseDown() {
		double movex = -((double) (oldX - clickX) / (double) windowWidth) * (left - right);
		double movey = -((double) (oldY - clickY) / (double) windowHeight) * (top - bottom);
		left += movex;
		right += movex;
		top += movey;
		bottom += movey;
		skipClick = true;
		updateDisplay();
		Layer::mouseDown();
	}
	void mouseMove() {
		mousePosition = unproject(clickX, windowHeight - clickY);
		postRedisplay();
		Layer::mouseMove();
	}

	void updateDisplay();
	void postRedisplay();

	void initDraw();

	void toggleFullscreen();

	void zoom(const int x, const int y, const double factor) {
		if (factor > 1.0 && (right - left) < minZoom)
			return;
		if (factor < 1.0 && (right - left) > maxZoom)
			return;
		const double cX = left + (double) x / (double) windowWidth * (right - left);
		const double cY = bottom + (1.0 - (double) y / (double) windowHeight) * (top - bottom);
		left = cX - (cX - left) / factor;
		right = cX - (cX - right) / factor;
		top = cY - (cY - top) / factor;
		bottom = cY - (cY - bottom) / factor;
		updateDisplay();
	}

};

}
#endif /* NXWINDOW_H_ */
