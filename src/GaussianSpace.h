/*
 * GaussianSpace.h
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#ifndef SRC_GAUSSIANSPACE_H_
#define SRC_GAUSSIANSPACE_H_

#include "SocialSpace.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

class GaussianSpace: public SocialSpace {
public:
	GaussianSpace();
	GaussianSpace(double x, double y);
	virtual ~GaussianSpace();

	void compute();
	double phi(double x, double y);
	void draw(double x, double y);

protected:
	ofImage frame;
	double buffer[400][400];
};

#endif /* SRC_GAUSSIANSPACE_H_ */
