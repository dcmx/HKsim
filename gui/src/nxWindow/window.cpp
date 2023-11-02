/*
 * nxwindow.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: Dominik Kaaser
 */
#include "window.h"

#include "vector.h"
#include "gl.h"
#include "color.h"
#include <list>

#include "layer.h"

namespace nx {

Window* Window::instance = 0;

void Window::__callback_draw() {
	get()->initDraw();
}
void Window::__callback_key(unsigned char key, int x, int y) {
	get()->setPosition(x, y);
	get()->key((int) key);
}
void Window::__callback_specialKey(int key, int x, int y) {
	get()->setPosition(x, y);
	get()->specialKey(key);
}
void Window::__callback_reshape(int x, int y) {
	get()->reshape(x, y);
}
void Window::__callback_click(int button, int state, int x, int y) {
	get()->setPosition(x, y);
	get()->click(button, state);
	get()->storePosition();
}
void Window::__callback_mouseDown(int x, int y) {
	get()->setPosition(x, y);
	get()->mouseDown();
	get()->storePosition();
}
void Window::__callback_mouseMove(int x, int y) {
	get()->setPosition(x, y);
	get()->mouseMove();
	get()->storePosition();
}

const vector Window::unproject(int x, int y) const {
	double projectionMatrix[16];

	glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);

	const double A = projectionMatrix[0];
	const double B = projectionMatrix[5];
	const double D = projectionMatrix[12];
	const double E = projectionMatrix[13];

	const double p1 = 2.0 * ((double) x / (double) windowWidth) - 1.0;
	const double p2 = 2.0 * ((double) y / (double) windowHeight) - 1.0;

	return vector((p1 - D) / A, (p2 - E) / B);

}

Window::Window(const char* title, int* argc, char** argv) :
		title(title), windowWidth(800), windowHeight(600), windowLeft(0), windowTop(0), restoreWidth(800), restoreHeight(600), top(1.25), right(1.5), bottom(
				-0.25), left(-0.5), fullscreen(false), clickX(0), clickY(0), oldX(0), oldY(0), beginDragX(0), beginDragY(0), maxZoom(1e10), minZoom(1e-10), skipClick(
				false) {

	int dummyArgc = 0;
	char** dummyArgv = NULL;

	if (argc)
		glutInit(argc, argv);
	else
		glutInit(&dummyArgc, dummyArgv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);

	glutCreateWindow(title);
	glutSetIconTitle(title);

	instance = this;

	windowWidth = glutGet((GLenum) GLUT_WINDOW_WIDTH);
	windowHeight = glutGet((GLenum) GLUT_WINDOW_HEIGHT);

	glViewport(0, 0, windowWidth, windowHeight);

	colors::white.setAsBackground();

	glLineWidth(1.0);
	glPointSize(4.0);

	glutDisplayFunc(__callback_draw);
	glutKeyboardFunc(__callback_key);
	glutSpecialFunc(__callback_specialKey);
	glutReshapeFunc(__callback_reshape);
	glutMouseFunc(__callback_click);
	glutMotionFunc(__callback_mouseDown);
	glutPassiveMotionFunc(__callback_mouseMove);

#ifdef FREEGLUT
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

	enableAntiAliasing();

}
void Window::enableAntiAliasing() {
	glEnable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
#ifdef FREEGLUT
	glutSetOption(GLUT_MULTISAMPLE, 8);
#endif
}
void Window::disableAntiAliasing() {
	glDisable(GL_MULTISAMPLE);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);

}

void Window::show() {
	glutMainLoop();
}

void Window::close() {
#ifdef FREEGLUT
	glutLeaveMainLoop();
#else
	exit(0);
#endif
}
void Window::updateDisplay() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double addWidth = 0.5 * ((right - left) - (top - bottom) * (double) windowWidth / (double) windowHeight);
	right -= addWidth;
	left += addWidth;
	gluOrtho2D(left, right, bottom, top);
	glViewport(0, 0, windowWidth, windowHeight);
	postRedisplay();
}
void Window::postRedisplay() {
	glutPostRedisplay();
}

void Window::initDraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	glFlush();
	glutSwapBuffers();
	updateDisplay();
}

void Window::toggleFullscreen() {
	fullscreen = !fullscreen;
	if (fullscreen) {
		windowLeft = glutGet(GLUT_WINDOW_X);
		windowTop = glutGet(GLUT_WINDOW_Y);
		restoreWidth = glutGet(GLUT_WINDOW_WIDTH);
		restoreHeight = glutGet(GLUT_WINDOW_HEIGHT);
		glutFullScreen();
		windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	} else {
		glutReshapeWindow(restoreWidth, restoreHeight);
		glutPositionWindow(windowLeft, windowTop);
		windowWidth = restoreWidth;
		windowHeight = restoreHeight;
	}
	glViewport(0, 0, windowWidth, windowHeight);
}

}

