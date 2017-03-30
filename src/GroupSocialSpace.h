/*
 * GroupSocialSpace.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef GROUPSOCIALSPACE_H_
#define GROUPSOCIALSPACE_H_

#include "SocialSpace.h"
#include "Point.h"

class GroupSocialSpace: public SocialSpace, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	GroupSocialSpace(Point p = Point(), int id = 0);
	GroupSocialSpace(std::vector<Agent*>& a, Point p = Point(), int id = 0);
	virtual ~GroupSocialSpace();

	virtual void draw(World* world, Point p = Point()) = 0;
};

#endif /* GROUPSOCIALSPACE_H_ */
