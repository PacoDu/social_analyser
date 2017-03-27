/*
 * DrawnObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "DrawnObject.h"

DrawnObject::DrawnObject(double x, double y):
		LocalizedObject(x,y) {
}

DrawnObject::~DrawnObject() {
}

void DrawnObject::draw() {
	this->draw(0,0);
}

DrawnObject::DrawnObject():
		LocalizedObject() {
}
