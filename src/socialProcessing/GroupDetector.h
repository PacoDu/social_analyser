/*
 * GroupDetector.h
 *
 *  Created on: Apr 10, 2017
 *      Author: paco
 */

#ifndef SRC_GROUPDETECTOR_H_
#define SRC_GROUPDETECTOR_H_

#include "Population.h"
#include "Agent.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

using namespace Eigen;

class GroupDetector {
public:
	GroupDetector(Population* pop);
	virtual ~GroupDetector();

	void detect();
	void checkExistingFormation();

protected:
	Population* _population;
	double maxDistanceThreshold = 2;
	//dirty
	int formationId = 0;
};

#endif /* SRC_GROUPDETECTOR_H_ */
