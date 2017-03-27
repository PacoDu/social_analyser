/*
 * IdentifiedObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "IdentifiedObject.h"

IdentifiedObject::IdentifiedObject(unsigned int id): id(id) {
}

IdentifiedObject::IdentifiedObject() {
	this->id = 0;
}

IdentifiedObject::~IdentifiedObject() {
}
