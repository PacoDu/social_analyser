/*
 * PersonnalSocialSpace.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "PersonnalSocialSpace.h"
#include "Agent.h"

PersonnalSocialSpace::PersonnalSocialSpace(Agent* a, Point p, double theta, int id):
		SocialSpace(p,id), _agent(a) {
//	this->getNode()->setParent(*a->getNode());
}

PersonnalSocialSpace::~PersonnalSocialSpace() {
	// TODO Auto-generated destructor stub
}

