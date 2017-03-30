/*
 * Point.cpp
 *
 *  Created on: Mar 30, 2017
 *      Author: paco
 */

#include "Point.h"

Point::Point(): x(0), y(0), z(0) {
}

Point::Point(double x, double y, double z): x(x), y(y), z(z) {
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}


int Point::planSide(ofVec3f planeNormal, float planeDistance){
	ofVec3f directionToPlane = planeDistance * planeNormal - ofVec3f(this->x, this->y, this->z);
	float dot = directionToPlane.dot(planeNormal);
	return (dot < 0 ? 1 : -1);
}
