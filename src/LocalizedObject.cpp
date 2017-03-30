/*
 * LocalizedObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "LocalizedObject.h"

// --- CONSTRUCTOR & DESTRUCTOR
LocalizedObject::LocalizedObject(Point p, double theta): position(p), theta(theta) {
}

LocalizedObject::~LocalizedObject() {
}

// --- Getter & Setter
const Point& LocalizedObject::getPosition() const {
	return position;
}

void LocalizedObject::setPosition(const Point& position) {
	this->position = position;
}

double LocalizedObject::getTheta() const {
	return theta;
}

void LocalizedObject::setTheta(double theta) {
	this->theta = theta;
}
