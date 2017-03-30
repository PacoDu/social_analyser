/*
 * SocialSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "SocialSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
SocialSpace::SocialSpace(double x, double y, int id):
		IdentifiedObject(id), DrawnObject(x,y) {
}

SocialSpace::~SocialSpace() {
}
