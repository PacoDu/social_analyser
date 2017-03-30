/*
 * LocalizedObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "LocalizedObject.h"

// --- CONSTRUCTOR & DESTRUCTOR
LocalizedObject::LocalizedObject(double x, double y, double theta): x(x), y(y), theta(theta) {
}

LocalizedObject::~LocalizedObject() {
}

// --- Getter & Setter
double LocalizedObject::getX() const {
	return x;
}

void LocalizedObject::setX(double x) {
	this->x = x;
}

double LocalizedObject::getY() const {
	return y;
}

void LocalizedObject::setY(double y) {
	this->y = y;
}

double LocalizedObject::getTheta() const {
	return theta;
}

void LocalizedObject::setTheta(double theta) {
	this->theta = theta;
}
