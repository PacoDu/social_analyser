/*
 * PersonnalSocialSpace.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "PersonnalSocialSpace.h"
#include "Agent.h"

PersonnalSocialSpace::PersonnalSocialSpace(Agent* a, double x, double y, double theta,
		int id): SocialSpace(x,y,id), _agent(a) {
	this->getNode()->setParent(*a->getNode());
}

PersonnalSocialSpace::~PersonnalSocialSpace() {
	// TODO Auto-generated destructor stub
}

