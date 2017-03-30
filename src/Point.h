/*
 * Point.h
 *
 *  Created on: Mar 30, 2017
 *      Author: paco
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include "ofMain.h"

class Point {
public:
	Point();
	Point(double x, double y, double z = 0);
	virtual ~Point();

	double x;
	double y;
	double z;

	int planSide(ofVec3f planeNormal, float planeDistance);
};

#endif /* SRC_POINT_H_ */
