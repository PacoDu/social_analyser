/*
 * PersonnalSocialSpace.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef PERSONNALSOCIALSPACE_H_
#define PERSONNALSOCIALSPACE_H_

#include "SocialSpace.h"
#include "World.h"

class Agent;

class PersonnalSocialSpace: public SocialSpace {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	PersonnalSocialSpace(Agent * a, Point p = Point(), double theta = 0, int id = 0);
	virtual ~PersonnalSocialSpace();

	virtual void compute(World * world) = 0;

protected:
	Agent * _agent;
};

#endif /* PERSONNALSOCIALSPACE_H_ */
