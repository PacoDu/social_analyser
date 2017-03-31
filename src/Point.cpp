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


int Point::planSide(ofVec3f planeNormalA, ofVec3f a){
	ofVec3f AB = ofVec3f(this->x, this->y, this->z) - a;
	double dot = AB.dot(planeNormalA);
	return (dot > 0 ? 1 : -1);
}

double Point::distance(Point p) {
	return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
}

double Point::getX() const {
	return x;
}

void Point::setX(double x) {
	this->x = x;
}

double Point::getY() const {
	return y;
}

void Point::setY(double y) {
	this->y = y;
}

double Point::getZ() const {
	return z;
}

void Point::setZ(double z) {
	this->z = z;
}
