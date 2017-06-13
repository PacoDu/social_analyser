/**
 * @file IdentifiedObject.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#include "IdentifiedObject.h"

// --- CONSTRUCTOR & DESTRUCTOR
IdentifiedObject::IdentifiedObject(unsigned int id): id(id) {
}

IdentifiedObject::~IdentifiedObject() {
}

// --- Getter & Setter
unsigned int IdentifiedObject::getId() const {
	return this->id;
}

void IdentifiedObject::setId(unsigned int id) {
	this->id = id;
}
