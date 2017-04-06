/*
 * Formation.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_FORMATION_H_
#define SRC_FORMATION_H_

#include "Agent.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "AgentContainer.h"
#include "OSpace.h"
#include "PSpace.h"
#include "Point.h"
#include "World.h"

class Formation: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Formation(std::vector<Agent*>& a, Point p = Point(), double theta = 0, int id=0);
	Formation(GroupSocialSpace * sp, Point p = Point(), double theta = 0, int id=0);
	Formation(Point p = Point(), double theta = 0, int id=0);

	~Formation();

	// --- METHOD
	void draw(World* world);
	void computeSocialSpace(World* world);

	// Getters & Setters
	GroupSocialSpace* getSocialSpace() const;
	void setSocialSpace(GroupSocialSpace* socialSpace);


protected:
	GroupSocialSpace* _socialSpace;
};


#endif /* SRC_FORMATION_H_ */
