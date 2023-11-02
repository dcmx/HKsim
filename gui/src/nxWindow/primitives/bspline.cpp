/*
 * bspline.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: dkaaser
 */

#include "bspline.h"
#include "../gl.h"
#include "../window.h"

namespace nx {

BSpline::BSpline(const std::list<vector>& controlPoints) {
	numPoints = controlPoints.size();
	this->controlPoints = new float[numPoints * 3];
	unsigned int i = 0;
	for (std::list<vector>::const_iterator it = controlPoints.begin(); it != controlPoints.end(); ++it) {
		this->controlPoints[i++] = (float) (*it).x;
		this->controlPoints[i++] = (float) (*it).y;
		this->controlPoints[i++] = (float) 0.0;
	}
	knots = new float[numPoints + 4];

	for (i = 0; (int) i < numPoints + 4; i++)
		knots[i] = (float) i;
}

BSpline::~BSpline() {
	delete[] controlPoints;
	delete[] knots;
}

void BSpline::draw() {
	GLUnurbsObj *theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 4.0);
	gluNurbsProperty(theNurb, GLU_CULLING, GL_TRUE);
	gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD, GLU_PATH_LENGTH);

	gluBeginCurve(theNurb);

	gluNurbsCurve(theNurb, numPoints + 4, knots, 3, controlPoints, 4, GL_MAP1_VERTEX_3);
	gluEndCurve(theNurb);
	gluDeleteNurbsRenderer(theNurb);
}

} /* namespace nx */
