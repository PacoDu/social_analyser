/*
 * GroupDetector.h
 *
 *  Created on: Apr 10, 2017
 *      Author: paco
 */

#ifndef SRC_GROUPDETECTOR_H_
#define SRC_GROUPDETECTOR_H_

#include "Point.h"
#include "Population.h"
#include "Agent.h"

class GroupDetector {
public:
	GroupDetector(Population* pop);
	virtual ~GroupDetector();

	void detect();
	int rayIntersectionPoint(Point as, Point ad, Point bs, Point bd, Point* intersection);
	void checkExistingFormation();

protected:
	Population* _population;
	double maxDistanceThreshold = 2;
	//dirty
	int formationId = 0;
};

#endif /* SRC_GROUPDETECTOR_H_ */
