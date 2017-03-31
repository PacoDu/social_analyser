/*
 * GaussianSpace.h
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#ifndef SRC_GAUSSIANSPACE_H_
#define SRC_GAUSSIANSPACE_H_

#include "PersonnalSocialSpace.h"
#include "World.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

class GaussianSpace: public PersonnalSocialSpace {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
//	GaussianSpace(Agent * a, Point p = Point(), double theta=0);
	GaussianSpace(World* world, Agent * a, double theta=0);
	virtual ~GaussianSpace();

	// --- METHOD
	void compute(World* world);
	double phi(Point testedSpace);
	void draw(World* world);

protected:
	int width = 300;
	int height = 300;
	ofImage frame;
	std::vector<std::vector<double>> buffer;
};

#endif /* SRC_GAUSSIANSPACE_H_ */
