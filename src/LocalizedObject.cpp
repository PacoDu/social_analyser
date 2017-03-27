/*
 * LocalizedObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "LocalizedObject.h"

LocalizedObject::LocalizedObject(double x, double y): x(x), y(y) {
}

LocalizedObject::LocalizedObject() {
	this->x = 0;
	this->y = 0;
}

LocalizedObject::~LocalizedObject() {
}
