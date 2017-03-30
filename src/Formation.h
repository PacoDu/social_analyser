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

class Formation: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Formation(GroupSocialSpace * sp, std::vector<Agent*>& a, double x=0, double y=0, double theta = 0, int id=0);
	Formation(GroupSocialSpace * sp, double x=0, double y=0, double theta = 0, int id=0);

	~Formation();

	// --- METHOD
	void draw(double x, double y);
	void computeSocialSpace();

	// Getters & Setters


protected:
	GroupSocialSpace* _socialSpace;
};


#endif /* SRC_FORMATION_H_ */
