/*
 * SocialSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "SocialSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
SocialSpace::SocialSpace(Point p, int id):
		IdentifiedObject(id), DrawnObject(p) {
}

SocialSpace::~SocialSpace() {
}
